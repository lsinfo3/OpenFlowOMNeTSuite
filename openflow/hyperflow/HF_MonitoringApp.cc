#include "HF_MonitoringApp.h"

Define_Module(HF_MonitoringApp);


HF_MonitoringApp::HF_MonitoringApp() {

}

HF_MonitoringApp::~HF_MonitoringApp() {

}

void HF_MonitoringApp::initialize() {
    MonitoringApp::initialize();
    hfAgent = NULL;

    //register signals
    HyperFlowReFireSignalId =registerSignal("HyperFlowReFire");
    getParentModule()->subscribe("HyperFlowReFire",this);

    switches_signal = registerSignal("switches");
    tableLengths_signal = registerSignal("tableLengths");
    avgNrOfPacketsMatched_signal = registerSignal("avgNrOfPacketsMatched");
    avgBytesOfPacketsMatched_signal = registerSignal("avgBytesOfPacketsMatched");
    timeDiff_signal = registerSignal("timeDiff");
}

void HF_MonitoringApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    //set hfagent link
      if(hfAgent == NULL && controller != NULL){
          auto appList = controller->getAppList();

          for(auto iterApp=appList->begin();iterApp!=appList->end();++iterApp){
              if(dynamic_cast<HyperFlowAgent *>(*iterApp) != NULL) {
                  HyperFlowAgent *hf = (HyperFlowAgent *) *iterApp;
                  hfAgent = hf;
                  break;
              }
          }
      }

      MonitoringApp::receiveSignal(src,id,obj);

      //check for hf messages to refire
      if(id == HyperFlowReFireSignalId){
          if(dynamic_cast<HF_ReFire_Wrapper *>(obj) != NULL) {
              HF_ReFire_Wrapper *hfRefire = (HF_ReFire_Wrapper *) obj;
              if(strcmp(hfRefire->getDataChannelEntry().trgSwitch.c_str(),"") == 0){
                  if (dynamic_cast<StatsRequest_Wrapper *>(hfRefire->getDataChannelEntry().payload) != NULL) {
                      StatsRequest_Wrapper *wrapper = (StatsRequest_Wrapper *) hfRefire->getDataChannelEntry().payload;
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

void HF_MonitoringApp::handleReply(OFP_Stats_Reply * castMsg) {
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

       emit(switches_signal, swID);
       emit(tableLengths_signal, tableLength);
       emit(avgBytesOfPacketsMatched_signal, avgBytesMatched);
       emit(avgNrOfPacketsMatched_signal, avgNrMatched);
       emit(timeDiff_signal, 0);

       //inform hyperflow
       StatsRequest_Wrapper *wrapper = new StatsRequest_Wrapper();
       wrapper->setSwitchId(swID);
       wrapper->setTableLength(tableLength);
       wrapper->setBytesOfPacketsMatched(avgBytesMatched);
       wrapper->setNrOfPacketsMatched(avgNrMatched);
       wrapper->setTimestamp(simTime().dbl());

       DataChannelEntry entry = DataChannelEntry();
       entry.eventId = 0;
       entry.trgSwitch = "";
       entry.srcController = controller->getFullPath();
       entry.payload = wrapper;

       hfAgent->synchronizeDataChannelEntry(entry);
}

