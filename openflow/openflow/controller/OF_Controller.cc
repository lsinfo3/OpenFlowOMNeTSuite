#include <omnetpp.h>
#include <OF_Controller.h>

#include "GenericAppMsg_m.h"
#include "openflow.h"
#include "Open_Flow_Message_m.h"
#include "OFP_Packet_Out_m.h"
#include "TCPCommand_m.h"
#include "OFP_Flow_Mod_m.h"
#include "OFP_Features_Request_m.h"
#include "OFP_Features_Reply_m.h"
#include "TCPConnection.h"
#include "OFP_Initialize_Handshake_m.h"
#include "AbstractControllerApp.h"
#include "OFP_Stats_Request_m.h"
#include "OFP_Stats_Reply_m.h"

#define MSGKIND_BOOTED 100

using namespace std;

Define_Module(OF_Controller);



OF_Controller::OF_Controller(){

}

OF_Controller::~OF_Controller(){

}

void OF_Controller::initialize(){
    //register signals
    PacketInSignalId =registerSignal("PacketIn");
    PacketOutSignalId =registerSignal("PacketOut");
    PacketHelloSignalId =registerSignal("PacketHello");
    PacketFeatureRequestSignalId = registerSignal("PacketFeatureRequest");
    PacketFeatureReplySignalId = registerSignal("PacketFeatureReply");
    BootedSignalId = registerSignal("Booted");
    PacketStatsReplySignalId = registerSignal("PacketStatsReply");
    PacketStatsRequestSignalId = registerSignal("PacketStatsRequest");

    //stats
    queueSize = registerSignal("queueSize");
    waitingTime = registerSignal("waitingTime");

    numPacketIn=0;

    lastQueueSize =0;
    lastChangeTime=0.0;

    //parameters
    serviceTime = par("serviceTime");
    busy = false;

    // TCP socket; listen on incoming connections
    const char *address = par("address");
    int port = par("port");
    socket.setOutputGate(gate("tcpOut"));
    socket.setDataTransferMode(TCP_TRANSFER_OBJECT);
    socket.bind(address[0] ? IPvXAddress(address) : IPvXAddress(), port);
    socket.listen();

    //schedule booted message
    cMessage *booted = new cMessage("Booted");
    booted->setKind(MSGKIND_BOOTED);
    scheduleAt(0, booted);
}


void OF_Controller::handleMessage(cMessage *msg){

    if (msg->isSelfMessage()) {
        if (msg->getKind()==MSGKIND_BOOTED){
            emit(BootedSignalId,this);
        }else{
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
                cMessage *msgfromlist = msgList.front();
                msgList.pop_front();
                cMessage *event = new cMessage("event");
                event->setContextPointer(msgfromlist);
                scheduleAt(simTime()+serviceTime, event);
            }
            calcAvgQueueSize(msgList.size());
        }
        //delete the msg for efficiency
        delete msg;
    }else{
        //imlement service time
        if (busy) {
            msgList.push_back(msg);
        }else{
            busy = true;
            cMessage *event = new cMessage("event");
            event->setContextPointer(msg);
            scheduleAt(simTime()+serviceTime, event);
        }

        if(bytesPerSecond.count(floor(simTime().dbl())) <=0){
            if (msg->isPacket()){
                int byteLength = dynamic_cast<cPacket*>(msg)->getByteLength();
                bytesPerSecond.insert(pair<int,int>(floor(simTime().dbl()),byteLength));
            }

        } else {
            if (msg->isPacket()){
                int byteLength = dynamic_cast<cPacket*>(msg)->getByteLength();
                bytesPerSecond[floor(simTime().dbl())] = bytesPerSecond[floor(simTime().dbl())] + byteLength;
            }
        }

        if(packetsPerSecond.count(floor(simTime().dbl())) <=0){
            packetsPerSecond.insert(pair<int,int>(floor(simTime().dbl()),1));
        } else {
            packetsPerSecond[floor(simTime().dbl())]++;
        }

        calcAvgQueueSize(msgList.size());
        emit(queueSize,msgList.size());
    }
}

void OF_Controller::calcAvgQueueSize(int size){
    if(lastQueueSize != size){
        double timeDiff = simTime().dbl() - lastChangeTime;
        if(avgQueueSize.count(floor(simTime().dbl())) <=0){
            avgQueueSize.insert(pair<int,double>(floor(simTime().dbl()),lastQueueSize*timeDiff));
        } else {
            avgQueueSize[floor(simTime().dbl())] += lastQueueSize*timeDiff;
        }
            lastChangeTime = simTime().dbl();
            lastQueueSize = size;
        }
}


void OF_Controller::processQueuedMsg(cMessage *data_msg){
    if (dynamic_cast<Open_Flow_Message *>(data_msg) != NULL) {
        Open_Flow_Message *of_msg = (Open_Flow_Message *)data_msg;
        ofp_type type = (ofp_type)of_msg->getHeader().type;

        switch (type) {
            case OFPT_FEATURES_REPLY:
                handleFeaturesReply(of_msg);
                break;
            case OFPT_HELLO:
                registerConnection(of_msg);
                sendHello(of_msg);
                sendFeatureRequest(data_msg);
                break;
            case OFPT_PACKET_IN:
                EV << "packet-in message from switch\n";
                handlePacketIn(of_msg);
                break;
            case OFPT_STATS_REPLY:
                handleStatsReply(of_msg);
                break;
            default:
                break;
        }
    }
}

void OF_Controller::handleStatsReply(Open_Flow_Message *of_msg){
    EV << "OFA_controller::handleStatsReply" << endl;
      if(dynamic_cast<OFP_Stats_Reply *>(of_msg) != NULL){
          OFP_Stats_Reply * castMsg = (OFP_Stats_Reply *)of_msg;
          emit(PacketStatsReplySignalId,castMsg);
      }
}

void OF_Controller::sendStatsRequest(Open_Flow_Message *of_msg, TCPSocket *socket) {
    Enter_Method_Silent();
    take(of_msg);
    EV << "OFA_controller::sendStatsRequest" << endl;
    emit(PacketStatsRequestSignalId, of_msg);
    socket->send(of_msg);
}

void OF_Controller::sendHello(Open_Flow_Message *msg){
    OFP_Hello *hello = new OFP_Hello("Hello");
    hello->getHeader().version = OFP_VERSION;
    hello->getHeader().type = OFPT_HELLO;
    hello->setByteLength(8);
    hello->setKind(TCP_C_SEND);

    emit(PacketHelloSignalId,hello);
    TCPSocket *socket = findSocketFor(msg);
    socket->send(hello);
}

void OF_Controller::sendFeatureRequest(cMessage *msg){
    OFP_Features_Request *featuresRequest = new OFP_Features_Request("FeaturesRequest");
    featuresRequest->getHeader().version = OFP_VERSION;
    featuresRequest->getHeader().type = OFPT_FEATURES_REQUEST;
    featuresRequest->setByteLength(8);
    featuresRequest->setKind(TCP_C_SEND);

    emit(PacketFeatureRequestSignalId,featuresRequest);
    TCPSocket *socket = findSocketFor(msg);
    socket->send(featuresRequest);
}

void OF_Controller::handleFeaturesReply(Open_Flow_Message *of_msg){
    EV << "OFA_controller::handleFeaturesReply" << endl;
    Switch_Info *swInfo= findSwitchInfoFor(of_msg);
    if(dynamic_cast<OFP_Features_Reply *>(of_msg) != NULL){
        OFP_Features_Reply * castMsg = (OFP_Features_Reply *)of_msg;
        swInfo->setMacAddress(castMsg->getDatapath_id());
        swInfo->setNumOfPorts(castMsg->getPortsArraySize());
        emit(PacketFeatureReplySignalId,castMsg);
    }

}

void OF_Controller::handlePacketIn(Open_Flow_Message *of_msg){
    EV << "OFA_controller::handlePacketIn" << endl;
    numPacketIn++;
    emit(PacketInSignalId,of_msg);
}


void OF_Controller::sendPacketOut(Open_Flow_Message *of_msg, TCPSocket *socket){
    Enter_Method_Silent();
    take(of_msg);
    EV << "OFA_controller::sendPacketOut" << endl;
    emit(PacketOutSignalId,of_msg);
    socket->send(of_msg);
}



void OF_Controller::registerConnection(Open_Flow_Message *msg){
    TCPSocket *socket = findSocketFor(msg);
    if(!socket){
        socket = new TCPSocket(msg);
        socket->setOutputGate(gate("tcpOut"));
        Switch_Info swInfo = Switch_Info();
        swInfo.setSocket(socket);
        swInfo.setConnId(socket->getConnectionId());
        swInfo.setMacAddress("");
        swInfo.setNumOfPorts(-1);
        swInfo.setVersion(msg->getHeader().version);
        switchesList.push_back(swInfo);
    }
}


TCPSocket *OF_Controller::findSocketFor(cMessage *msg) const{
    TCPCommand *ind = dynamic_cast<TCPCommand *>(msg->getControlInfo());
    if (!ind)
        opp_error("TCPSocketMap: findSocketFor(): no TCPCommand control info in message (not from TCP?)");

    int connId = ind->getConnId();
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if((*i).getConnId() == connId){
            return (*i).getSocket();
        }
    }
    return NULL;
}


Switch_Info *OF_Controller::findSwitchInfoFor(cMessage *msg) {
    TCPCommand *ind = dynamic_cast<TCPCommand *>(msg->getControlInfo());
    if (!ind)
        return NULL;

    int connId = ind->getConnId();
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if((*i).getConnId() == connId){
            return &(*i);
        }
    }
    return NULL;
}

TCPSocket *OF_Controller::findSocketForChassisId(std::string chassisId) const{
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if(strcmp((*i).getMacAddress().c_str(),chassisId.c_str())==0){
            return (*i).getSocket();
        }
    }
    return NULL;
}

void OF_Controller::registerApp(AbstractControllerApp *app){
    apps.push_back(app);
}

std::vector<Switch_Info >* OF_Controller::getSwitchesList() {
    return &switchesList;
}

std::vector<AbstractControllerApp *>* OF_Controller::getAppList() {
    return &apps;
}

void OF_Controller::finish(){
    // record statistics
    recordScalar("numPacketIn", numPacketIn);

    std::map<int,int>::iterator iterMap;
    for(iterMap = packetsPerSecond.begin(); iterMap != packetsPerSecond.end(); iterMap++){
        stringstream name;
        name << "packetsPerSecondAt-" << iterMap->first;
        recordScalar(name.str().c_str(),iterMap->second);
    }

    std::map<int,double>::iterator iterMap2;
    for(iterMap2 = avgQueueSize.begin(); iterMap2 != avgQueueSize.end(); iterMap2++){
        stringstream name;
        name << "avgQueueSizeAt-" << iterMap2->first;
        recordScalar(name.str().c_str(),(iterMap2->second/1.0));
    }

    std::map<int,int>::iterator iterMap3;
    for(iterMap3 = bytesPerSecond.begin(); iterMap3 != bytesPerSecond.end(); iterMap3++){
        stringstream name;
        name << "bytesPerSecondAt-" << iterMap3->first;
        recordScalar(name.str().c_str(),iterMap3->second);
    }
}



