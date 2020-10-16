#include "KN_MonitoringApp.h"

Define_Module(KN_MonitoringApp);


KN_MonitoringApp::KN_MonitoringApp() {

}

KN_MonitoringApp::~KN_MonitoringApp() {

}

void KN_MonitoringApp::initialize() {
    MonitoringApp::initialize();
    kandooAgent = NULL;

    appName = "KN_MonitoringApp";

    //register signals
    kandooEventSignalId =registerSignal("KandooEvent");
    getParentModule()->subscribe("KandooEvent",this);

    switches_signal = registerSignal("switches");
    tableLengths_signal = registerSignal("tableLengths");
    avgNrOfPacketsMatched_signal = registerSignal("avgNrOfPacketsMatched");
    avgBytesOfPacketsMatched_signal = registerSignal("avgBytesOfPacketsMatched");
    timeDiff_signal = registerSignal("timeDiff");
}

void KN_MonitoringApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    //set knagent link
    if(kandooAgent == NULL && controller != NULL){
        auto appList = controller->getAppList();

        for(auto iterApp=appList->begin();iterApp!=appList->end();++iterApp){
            if(dynamic_cast<KandooAgent *>(*iterApp) != NULL) {
                KandooAgent *kn = (KandooAgent *) *iterApp;
                kandooAgent = kn;
                break;
            }
        }
    }

    MonitoringApp::receiveSignal(src,id,obj);

    //check for kandoo events
    if(id == kandooEventSignalId){
        if(dynamic_cast<KN_Packet *>(obj) != NULL) {
            KN_Packet *knpck = (KN_Packet *) obj;
            if(strcmp(knpck->getKnEntry().trgApp.c_str(),appName.c_str())==0){
                if(knpck->getKnEntry().type==0){
                    if (dynamic_cast<StatsRequest_Wrapper *>(knpck->getKnEntry().payload) != NULL) {
                        StatsRequest_Wrapper *wrapper = (StatsRequest_Wrapper *) knpck->getKnEntry().payload;
                        emit(switches_signal, wrapper->getSwitchId());
                        emit(tableLengths_signal, wrapper->getTableLength());
                        emit(avgBytesOfPacketsMatched_signal, wrapper->getBytesOfPacketsMatched());
                        emit(avgNrOfPacketsMatched_signal, wrapper->getNrOfPacketsMatched());
                        double timeDifference =  simTime().dbl() - wrapper->getTimestamp();
                        emit(timeDiff_signal, timeDifference);
                    }
                }
            }
        }
    }
}

void KN_MonitoringApp::handleReply(OFP_Stats_Reply * castMsg) {
    // Body der Reply wieder in das Struct-Format bringen
    int body_array_size = castMsg->getBodyArraySize();

    ofp_flow_stats reply_body = ofp_flow_stats();
    int body_size = static_cast<int>(sizeof(reply_body));

    uint8_t body[body_array_size];
    ofp_flow_stats reply_bodies[body_array_size / body_size];

    for (int i = 0; i < body_array_size; i++) {
        body[i] = castMsg->getBody(i);
    }

    // Hier wird der Body der Reply in ein Array von Structs umgewandelt
    // Auﬂerdem werden die MatchedPackets gleich mitgez‰hlt
    double nrOfPacketsMatched = 0;
    double nrOfBytesMatched = 0;
    for (int i = 0; i < body_array_size / body_size; i++) {
        memcpy(&reply_bodies[i], (&body[i*body_size]), body_size);
        //reply_bodies[i] = *((ofp_flow_stats *) (&body[0]) + i);
        nrOfPacketsMatched = nrOfPacketsMatched + reply_bodies[i].packet_count;
        nrOfBytesMatched = nrOfBytesMatched + reply_bodies[i].byte_count;
    }
    // Statistiken
    int swID = controller->findSwitchInfoFor(castMsg)->getConnId();
    int tableLength = body_array_size/body_size;
    double avgBytesMatched = nrOfBytesMatched/tableLength;
    double avgNrMatched = nrOfPacketsMatched/tableLength;

    if(!kandooAgent->getIsRootController()){
        //inform kandoo root
        StatsRequest_Wrapper *wrapper = new StatsRequest_Wrapper();
        wrapper->setSwitchId(swID);
        wrapper->setTableLength(tableLength);
        wrapper->setBytesOfPacketsMatched(avgBytesMatched);
        wrapper->setNrOfPacketsMatched(avgNrMatched);
        wrapper->setTimestamp(simTime().dbl());

        KandooEntry entry = KandooEntry();
        entry.srcApp = "KN_MonitoringApp";
        entry.srcSwitch = controller->findSwitchInfoFor(castMsg)->getMacAddress();
        entry.trgSwitch = "";
        entry.trgApp = "KN_MonitoringApp";
        entry.type =0;
        entry.srcController = controller->getFullPath();
        entry.trgController = "RootController";
        entry.payload = wrapper;

        kandooAgent->sendRequest(entry);
    }
}

