#include <OF_Switch.h>
#include "openflow.h"

#include "Open_Flow_Message_m.h"
#include "OFP_Initialize_Handshake_m.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Hello_m.h"
#include "OFP_Stats_Reply_m.h"
#include "OFP_Stats_Request_m.h"

#include "OFP_Packet_In_m.h"
#include "OFP_Packet_Out_m.h"
#include "OFP_Flow_Mod_m.h"
#include "EtherMAC.h"

#include "IPv4Datagram.h"
#include "ARPPacket_m.h"
#include "IPvXAddressResolver.h"

#include "InterfaceTableAccess.h"
#include "InterfaceTable.h"

#include "PingPayload_m.h"
#include "ICMPMessage.h"


#define MSGKIND_CONNECT                     1
#define MSGKIND_SERVICETIME                 3


Define_Module(OF_Switch);

OF_Switch::OF_Switch(){

}

OF_Switch::~OF_Switch(){

}

void OF_Switch::initialize(){


    //read ned file parameters
    flowTimeoutPollInterval = par("flowTimeoutPollInterval");
    serviceTime = par("serviceTime");
    busy = false;
    sendCompletePacket = par("sendCompletePacket");



    //stats
    dpPingPacketHash = registerSignal("dpPingPacketHash");
    cpPingPacketHash = registerSignal("cpPingPacketHash");
    queueSize = registerSignal("queueSize");
    bufferSize = registerSignal("bufferSize");
    waitingTime = registerSignal("waitingTime");
    dataPlanePacket=0l;
    controlPlanePacket=0l;
    flowTableHit=0l;
    flowTableMiss=0l;


    // Init all ports
    portVector.resize(gateSize("dataPlaneIn"));
    for(unsigned int i=0;i<portVector.size();i++){
        portVector[i].port_no = i+1;
        cModule *ethernetModule = gate("dataPlaneOut",i)->getNextGate()->getOwnerModule()->getSubmodule("mac");
        if(dynamic_cast<EtherMAC *>(ethernetModule) != NULL) {
            EtherMAC *nic = (EtherMAC *)ethernetModule;
            uint64_t tmpHw = nic->getMACAddress().getInt();
            memcpy(portVector[i].hw_addr,&tmpHw, sizeof tmpHw);
        }


        sprintf(portVector[i].name,"Port: %d",i);
        portVector[i].config =0;
        portVector[i].state =0;
        portVector[i].curr =0;
        portVector[i].advertised =0;
        portVector[i].supported =0;
        portVector[i].peer =0;
        portVector[i].curr_speed =0;
        portVector[i].max_speed =0;
    }

    //init helper classes
    buffer = Buffer((int)par("bufferCapacity"));

    //init socket to controller
    const char *localAddress = par("localAddress");
    int localPort = par("localPort");

    socket.bind(*localAddress ? IPvXAddress(localAddress) : IPvXAddress(), localPort);
    socket.setOutputGate(gate("controlPlaneOut"));
    socket.setDataTransferMode(TCP_TRANSFER_OBJECT);



    //schedule connection setup
    cMessage *initiateConnection = new cMessage("initiateConnection");
    initiateConnection->setKind(MSGKIND_CONNECT);
    scheduleAt(par("connectAt"), initiateConnection);

    //remove unused nics from ift
    IInterfaceTable* interfaceTable = InterfaceTableAccess().get();
    for(int i=0; i< interfaceTable->getNumInterfaces() ;i++){
        if(interfaceTable->getInterface(i) != interfaceTable->getInterfaceByName("eth0")){
            interfaceTable->deleteInterface(interfaceTable->getInterface(i));
            i--;
        }
    }


}


void OF_Switch::handleMessage(cMessage *msg){
    if (msg->isSelfMessage()){
        if (msg->getKind()==MSGKIND_CONNECT) {
            EV << "starting session" << '\n';
            connect(""); // active OPEN
        } else if(msg->getKind()==MSGKIND_SERVICETIME){
            //This is message which has been scheduled due to service time

            //Get the Original message
            cMessage *data_msg = (cMessage *) msg->getContextPointer();
            emit(waitingTime,(simTime()-data_msg->getArrivalTime()-serviceTime));

            processQueuedMsg(data_msg);

            //delete the processed msg
            delete data_msg;



            //Trigger next service time
            if (msgList.empty()){
                busy = false;
            } else {
                cMessage *msgFromList = msgList.front();
                msgList.pop_front();
                cMessage *event = new cMessage("event");
                event->setKind(MSGKIND_SERVICETIME);
                event->setContextPointer(msgFromList);
                scheduleAt(simTime()+serviceTime, event);
            }
        }
        //delete the msg for efficiency
        delete msg;
    } else {
        if(msg->getKind() == TCP_I_ESTABLISHED){
            socket.processMessage(msg);
        }else{
            //imlement service time

            if (busy) {
                msgList.push_back(msg);
            } else {
                busy = true;
                cMessage *event = new cMessage("event");
                event->setKind(MSGKIND_SERVICETIME);
                event->setContextPointer(msg);
                scheduleAt(simTime()+serviceTime, event);
            }
            emit(queueSize,msgList.size());
            emit(bufferSize,buffer.size());
        }
    }
}

void OF_Switch::connect(const char *addressToConnect){
    socket.renewSocket();
    const char *connectAddress;

    int connectPort = par("connectPort");

    if(strlen(addressToConnect) == 0){
        connectAddress = par("connectAddress");
    } else {
        connectAddress = addressToConnect;
    }


    EV << "Sending Hello to" << connectAddress <<" \n";

    socket.connect(IPvXAddressResolver().resolve(connectAddress), connectPort);
    OFP_Hello *msg = new OFP_Hello("Hello");
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_HELLO;
    msg->setByteLength(8);
    msg->setKind(TCP_C_SEND);
    socket.send(msg);
}

void OF_Switch::processQueuedMsg(cMessage *data_msg){
    if(data_msg->arrivedOn("dataPlaneIn")){
        dataPlanePacket++;
        if(socket.getState() != TCPSocket::CONNECTED){
            //no yet connected to controller
            //drop packet by returning
            return;
        }
        if (dynamic_cast<EthernetIIFrame *>(data_msg) != NULL){ //msg from dataplane
            EthernetIIFrame *frame = (EthernetIIFrame *)data_msg;
            //copy the frame as the original will be deleted
            EthernetIIFrame *copy = frame->dup();
            processFrame(copy);
        }
    } else {
        controlPlanePacket++;
       if (dynamic_cast<Open_Flow_Message *>(data_msg) != NULL) { //msg from controller
            Open_Flow_Message *of_msg = (Open_Flow_Message *)data_msg;
            ofp_type type = (ofp_type)of_msg->getHeader().type;
            switch (type){
                case OFPT_FEATURES_REQUEST:
                    handleFeaturesRequestMessage(of_msg);
                    break;
                case OFPT_FLOW_MOD:
                    handleFlowModMessage(of_msg);
                    break;
                case OFPT_PACKET_OUT:
                    handlePacketOutMessage(of_msg);
                    break;
                case OFPT_STATS_REQUEST:
                    handleStatsRequestMessage(of_msg);
                    break;
                }
        }

    }

}

void OF_Switch::handleStatsRequestMessage(Open_Flow_Message *of_msg){
    // Antwort erstellen
    OFP_Stats_Reply *statsReply = new OFP_Stats_Reply("StatsReply");

    // Typ der Antwort setzen
    statsReply->getHeader().type = OFPT_STATS_REPLY;
    OFP_Stats_Request *statsReqMsg = (OFP_Stats_Request *) of_msg;
    ofp_stats_types type = (ofp_stats_types)statsReqMsg->getType();
    statsReply->setType(type);

    // Body der Request kopieren
    int bodysize = statsReqMsg->getBodyArraySize();
    uint8_t body[bodysize];
    for (int i = 0; i < bodysize; i++) {
        body[i] = statsReqMsg->getBody(i);
    }

    switch (type) {
    case OFPST_FLOW: {

        // Typ auf Zeiger vom kopierten Array casten
        ofp_flow_stats_request request_body = ofp_flow_stats_request();

        memcpy(&request_body, body, bodysize);
        //request_body = (ofp_flow_stats_request *) body;

        // Tabelleneintr�ge...
        oxm_basic_match match = request_body.match;
        auto lookupAll = flowTable.lookupAll(match);

        // Array aus Bodies der Reply
        ofp_flow_stats reply_bodies[lookupAll.size()];

        //  Die einzelnen Bodies bef�llen
        ofp_flow_stats reply_body = ofp_flow_stats();
        int size_reply_body = static_cast<int>(sizeof(reply_body));
        int size_array_reply_body = lookupAll.size() * size_reply_body;
        statsReply->setBodyArraySize(size_array_reply_body);

       int j = 0;
       int i = 0;
        for(auto iter = lookupAll.begin(); iter != lookupAll.end(); ++iter){
            reply_bodies[j].match = (*iter)->getMatch();
            reply_bodies[j].byte_count = (*iter)->getCounters().bytesReceived;
            reply_bodies[j].packet_count = (*iter)->getCounters().packetsReceived;


            reply_bodies[j].hard_timeout = (*iter)->getHardTimeout();
            reply_bodies[j].idle_timeout = (*iter)->getIdleTimeout();

            int k = 0;
            while (k < size_reply_body && i < size_array_reply_body) {
                  statsReply->setBody(i,  *((uint8_t *)(&reply_bodies[0]) + i));
                  i++;
                  k++;
            }
            j++;
        }
        break;
    }
    case OFPST_AGGREGATE:
        break;
    case OFPST_DESC:
        break;
    }


    statsReply->setByteLength(56);
    statsReply->setKind(TCP_C_SEND);
    socket.send(statsReply);
}

void OF_Switch::processFrame(EthernetIIFrame *frame){
    oxm_basic_match match = oxm_basic_match();
    //extract match fields
    match.OFB_IN_PORT = frame->getArrivalGate()->getIndex();
    match.OFB_ETH_SRC = frame->getSrc();
    match.OFB_ETH_DST = frame->getDest();
    match.OFB_ETH_TYPE = frame->getEtherType();

    //extract ARP specific match fields if present
    if(frame->getEtherType()==ETHERTYPE_ARP){
        ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
        match.OFB_ARP_OP = arpPacket->getOpcode();
        match.OFB_ARP_SHA = arpPacket->getSrcMACAddress();
        match.OFB_ARP_THA = arpPacket->getDestMACAddress();
        match.OFB_ARP_SPA = arpPacket->getSrcIPAddress();
        match.OFB_ARP_TPA = arpPacket->getDestIPAddress();
    }

    unsigned long hash =0;

    //emit id of ping packet to indicate where it was processed
    if(dynamic_cast<ICMPMessage *>(frame->getEncapsulatedPacket()->getEncapsulatedPacket()) != NULL){
        ICMPMessage *icmpMessage = (ICMPMessage *)frame->getEncapsulatedPacket()->getEncapsulatedPacket();

        PingPayload * pingMsg =  (PingPayload * )icmpMessage->getEncapsulatedPacket();
        //generate and emit hash
        std::stringstream hashString;
        hashString << "SeqNo-" << pingMsg->getSeqNo() << "-Pid-" << pingMsg->getOriginatorId();
        hash = std::hash<std::string>()(hashString.str().c_str());
    }


   Flow_Table_Entry *lookup = flowTable.lookup(match);
   if (lookup != NULL){
       //lookup successful
       flowTableHit++;
       EV << "Found entry in flow table." << '\n';

       int bytesReceived = lookup->getCounters().bytesReceived + frame->getByteLength();
       int packetsReceived = lookup->getCounters().packetsReceived + 1;
       flow_table_counters counters;
       counters.bytesReceived = bytesReceived;
       counters.packetsReceived = packetsReceived;
       lookup->setCounters(counters);

       ofp_action_output action_output = lookup->getInstructions();
       uint32_t outport = action_output.port;
       if(outport == OFPP_CONTROLLER){
           //send it to the controller
           OFP_Packet_In *packetIn = new OFP_Packet_In("packetIn");
           packetIn->getHeader().version = OFP_VERSION;
           packetIn->getHeader().type = OFPT_PACKET_IN;
           packetIn->setReason(OFPR_ACTION);
           packetIn->setByteLength(32);
           packetIn->encapsulate(frame);
           packetIn->setBuffer_id(OFP_NO_BUFFER);
           socket.send(packetIn);
           if(hash !=0){
               emit(cpPingPacketHash,hash);
           }
       } else {
           if(hash !=0){
               emit(dpPingPacketHash,hash);
           }
           //send it out the dataplane on the specific port
           send(frame, "dataPlaneOut", outport);
       }
   } else {
       if(hash !=0){
           emit(cpPingPacketHash,hash);
       }
       // lookup failed
       flowTableMiss++;
       EV << "No Entry Found contacting controller" << '\n';
       handleMissMatchedPacket(frame);
   }
}

void OF_Switch::handleFeaturesRequestMessage(Open_Flow_Message *of_msg){
    OFP_Features_Reply *featuresReply = new OFP_Features_Reply("FeaturesReply");
    featuresReply->getHeader().version = OFP_VERSION;
    featuresReply->getHeader().type = OFPT_FEATURES_REPLY;

    IInterfaceTable *inet_ift = InterfaceTableAccess().get();

    MACAddress mac = inet_ift->getInterface(0)->getMacAddress();


    //output address
    EV <<"SwitchID:" << mac.str().c_str() << " SwitchPath:" << this->getFullPath() << '\n';


    featuresReply->setDatapath_id(mac.str().c_str());
    featuresReply->setN_buffers(buffer.getCapacity());
    featuresReply->setN_tables(1);
    featuresReply->setPortsArraySize(gateSize("dataPlaneOut"));

    featuresReply->setByteLength(32);
    featuresReply->setKind(TCP_C_SEND);
    socket.send(featuresReply);
}

void OF_Switch::handleFlowModMessage(Open_Flow_Message *of_msg){
    EV << "OFA_switch::handleFlowModMessage" << '\n';
    OFP_Flow_Mod *flowModMsg = (OFP_Flow_Mod *) of_msg;

    flowTable.addEntry(Flow_Table_Entry(flowModMsg));
}




void OF_Switch::handleMissMatchedPacket(EthernetIIFrame *frame){
    OFP_Packet_In *packetIn = new OFP_Packet_In("packetIn");
    packetIn->getHeader().version = OFP_VERSION;
    packetIn->getHeader().type = OFPT_PACKET_IN;
    packetIn->setReason(OFPR_NO_MATCH);

    packetIn->setByteLength(32);

    if (sendCompletePacket || buffer.isfull()){
        // send full packet with packet-in message
        packetIn->encapsulate(frame);
        packetIn->setBuffer_id(OFP_NO_BUFFER);

    } else{
        // store packet in buffer and only send header fields
        oxm_basic_match match = oxm_basic_match();
        match.OFB_IN_PORT = frame->getArrivalGate()->getIndex();

        match.OFB_ETH_SRC = frame->getSrc();
        match.OFB_ETH_DST = frame->getDest();
        match.OFB_ETH_TYPE = frame->getEtherType();
        //extract ARP specific match fields if present
        if(frame->getEtherType()==ETHERTYPE_ARP){
            ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
            match.OFB_ARP_OP = arpPacket->getOpcode();
            match.OFB_ARP_SHA = arpPacket->getSrcMACAddress();
            match.OFB_ARP_THA = arpPacket->getDestMACAddress();
            match.OFB_ARP_SPA = arpPacket->getSrcIPAddress();
            match.OFB_ARP_TPA = arpPacket->getDestIPAddress();
        }
        packetIn->setMatch(match);
        packetIn->setBuffer_id(buffer.storeMessage(frame));
    }
    socket.send(packetIn);
}


void OF_Switch::handlePacketOutMessage(Open_Flow_Message *of_msg){

    //cast message
    OFP_Packet_Out *packet_out_msg = (OFP_Packet_Out *) of_msg;

    //return variables
    uint32_t bufferId = packet_out_msg->getBuffer_id();
    uint32_t inPort = packet_out_msg->getIn_port();
    unsigned int actions_size = packet_out_msg->getActionsArraySize();

    //get the frame
    EthernetIIFrame *frame;
    if(bufferId != OFP_NO_BUFFER){
        frame = buffer.returnMessage(bufferId);
    } else {
        frame = dynamic_cast<EthernetIIFrame *>(packet_out_msg->getEncapsulatedPacket());
        frame = frame->dup();
    }

    //execute
    for (unsigned int i = 0; i < actions_size; ++i){
        executePacketOutAction(&(packet_out_msg->getActions(i)), frame, inPort);
    }
}


// packet encapsulated and not stored in buffer
void OF_Switch::executePacketOutAction(ofp_action_header *action, EthernetIIFrame *frame, uint32_t inport){
    ofp_action_output *action_output = (ofp_action_output *) action;
    uint32_t outport = action_output->port;
    take(frame);
    if(outport == OFPP_ANY){
           EV << "Dropping packet" << '\n';
    } else if (outport == OFPP_FLOOD){
        EV << "Flood Packet\n" << '\n';

        unsigned int n = gateSize("dataPlaneOut");
        for (unsigned int i=0; i<n; ++i) {
            if(i != inport && !(portVector[i].state & OFPPS_BLOCKED)){
                send(frame->dup(), "dataPlaneOut", i);
            }
        }
    } else {

            //if(!((portVector[outport].state & OFPPS_BLOCKED))){ //NEUE ADDIERT FUER LINKREMOVER
            if(!(portVector[outport].state  == (OFPPS_BLOCKED | OFPPS_LINK_DOWN))){ //NEUE ADDIERT FUER LINKREMOVER
            EV << "Send Packet\n" << '\n';
                send(frame->dup(), "dataPlaneOut", outport);
            }
            /*else{
                delete frame;
            }
            */

    }
    delete frame;
}


// invoked by Spanning Tree module disable ports for broadcast packets
void OF_Switch::disablePorts(vector<int> ports) {
    EV << "disablePorts method at " << this->getParentModule()->getFullPath() << '\n';

    for (unsigned int i = 0; i<ports.size(); ++i){
        portVector[ports[i]].state |= OFPPS_BLOCKED;
    }

    for(unsigned int i=0;i<portVector.size();++i){
        EV << "Port: " << i << " Value: " << portVector[i].state << '\n';
    }

    if(par("highlightActivePorts")){
        // Highlight links that belong to spanning tree
        for (unsigned int i = 0; i < portVector.size(); ++i){
            if (!(portVector[i].state & OFPPS_BLOCKED)){
                cGate *gateOut = getParentModule()->gate("gateDataPlane$o", i);
                do {
                    cDisplayString& connDispStrOut = gateOut->getDisplayString();
                    connDispStrOut.parse("ls=green,3,dashed");
                    gateOut=gateOut->getNextGate();
                } while (!gateOut->getOwnerModule()->getModuleType()->isSimple());

                cGate *gateIn = getParentModule()->gate("gateDataPlane$i", i);
                do {
                    cDisplayString& connDispStrIn = gateIn->getDisplayString();
                    connDispStrIn.parse("ls=green,3,dashed");
                    gateIn=gateIn->getPreviousGate();
                } while (!gateIn->getOwnerModule()->getModuleType()->isSimple());
            }
        }
    }

}


void OF_Switch::finish(){
    // record statistics
    recordScalar("packetsDataPlane", dataPlanePacket);
    recordScalar("packetsControlPlane", controlPlanePacket);
    recordScalar("flowTableHit", flowTableHit);
    recordScalar("flowTableMiss", flowTableMiss);
}

