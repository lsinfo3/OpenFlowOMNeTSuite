#include <LearningSwitch.h>
#include "Switch_Info.h"

Define_Module(LearningSwitch);

LearningSwitch::LearningSwitch(){

}

LearningSwitch::~LearningSwitch(){

}

void LearningSwitch::initialize(){
    AbstractControllerApp::initialize();
}

void LearningSwitch::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    AbstractControllerApp::receiveSignal(src,id,obj);

    if(id == PacketInSignalId){
        EV << "LearningSwitch::PacketIn" << endl;
        if (dynamic_cast<OFP_Packet_In *>(obj) != NULL) {
            OFP_Packet_In *packet_in = (OFP_Packet_In *) obj;
            doSwitching(packet_in);
        }
    }
}


void LearningSwitch::doSwitching(OFP_Packet_In *packet_in_msg){

    CommonHeaderFields headerFields = extractCommonHeaderFields(packet_in_msg);

    //search map for source mac address and enter
    if(lookUpMacAddress(headerFields.src_mac, headerFields.swInfo) == NULL){
        LearningSwitchMapping * mapping = new LearningSwitchMapping();
        mapping->setSwInfo(headerFields.swInfo);
        mapping->setAddress(headerFields.src_mac);
        mapping->setInPort(headerFields.inport);
        mappingList.push_front(mapping);
    }

    //search map for dest mac address and switch
    LearningSwitchMapping * destMapping= lookUpMacAddress(headerFields.dst_mac, headerFields.swInfo);
    if(destMapping == NULL){
        //Destination not found -> flood
        floodPacket(packet_in_msg);
    } else {
        uint32_t outport = destMapping->getInPort();

        oxm_basic_match *match = new oxm_basic_match();
        match->OFB_ETH_DST = headerFields.dst_mac;
        match->OFB_ETH_TYPE = headerFields.eth_type;
        match->OFB_ETH_SRC = headerFields.src_mac;
        match->OFB_IN_PORT = headerFields.inport;

        match->wildcards= 0;
        match->wildcards |= OFPFW_IN_PORT;
        match->wildcards |=  OFPFW_DL_SRC;
        match->wildcards |= OFPFW_DL_TYPE;


        TCPSocket * socket = controller->findSocketFor(packet_in_msg);
        sendFlowModMessage(OFPFC_ADD, match, outport, socket,par("flowModIdleTimeOut"),par("flowModHardTimeOut"));
        sendPacket(packet_in_msg, outport);
    }
}


LearningSwitchMapping * LearningSwitch::lookUpMacAddress(MACAddress address,Switch_Info * swInfo){
    LearningSwitchMapping *result = NULL;
    std::list<LearningSwitchMapping *>::iterator i = mappingList.begin();
    while (i!=mappingList.end()){
        if (address.compareTo((*i)->getAddress())==0 && swInfo == (*i)->getSwInfo()){
            return (*i);
            break;
        }
        i++;
    }
    return result;
}





