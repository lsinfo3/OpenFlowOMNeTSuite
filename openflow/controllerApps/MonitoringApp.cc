#include <MonitoringApp.h>
#include <algorithm>

#define MSGKIND_TRIGGERMULTIPARTREQUEST 101

Define_Module(MonitoringApp);

MonitoringApp::MonitoringApp() {

}

MonitoringApp::~MonitoringApp() {

}

void MonitoringApp::initialize() {
    AbstractControllerApp::initialize();
    pollInterval = par("pollInterval");
    switches_signal = registerSignal("switches");
    tableLengths_signal = registerSignal("tableLengths");
    avgNrOfPacketsMatched_signal = registerSignal("avgNrOfPacketsMatched");
    avgBytesOfPacketsMatched_signal = registerSignal("avgBytesOfPacketsMatched");
}

void MonitoringApp::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    AbstractControllerApp::receiveSignal(src, id, obj);
    if (id == PacketStatsReplySignalId) {

        if (dynamic_cast<OFP_Stats_Reply *>(obj) != NULL) {
            OFP_Stats_Reply * castMsg = (OFP_Stats_Reply *) obj;
            handleReply(castMsg);
        }
    } else if (id == BootedSignalId) {
        Enter_Method_Silent();
        cMessage *triggerMultipartRequest = new cMessage("triggerMultipartRequest");
        triggerMultipartRequest->setKind(MSGKIND_TRIGGERMULTIPARTREQUEST);
        scheduleAt(simTime() + pollInterval, triggerMultipartRequest);
    }
}

void MonitoringApp::handleReply(OFP_Stats_Reply * castMsg) {
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
    // Außerdem werden die MatchedPackets gleich mitgezählt
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

}

void MonitoringApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg->getKind() == MSGKIND_TRIGGERMULTIPARTREQUEST) {
            sendMultipartRequest();
            cMessage *triggerMultipartRequest = new cMessage(
                    "triggerMultipartRequest");
            triggerMultipartRequest->setKind(MSGKIND_TRIGGERMULTIPARTREQUEST);
            scheduleAt(simTime() + pollInterval, triggerMultipartRequest);
        }
    }
    delete msg;
}

void MonitoringApp::sendMultipartRequest() {
    //iterate over all switches controlled by the controller
    auto list = controller->getSwitchesList();
    for (auto i = list->begin(); i != list->end(); ++i) {
        if (strcmp((*i).getMacAddress().c_str(), "") == 0) {
            //only use full connections
            continue;
        }
        TCPSocket *socket = (*i).getSocket();
        controller->sendStatsRequest(createMultipartRequest(), socket);
    }
}

OFP_Stats_Request * MonitoringApp::createMultipartRequest() {
    OFP_Stats_Request * req = new OFP_Stats_Request("statsReq");
    req->getHeader().type = OFPT_STATS_REQUEST;
    req->getHeader().version = OFP_VERSION;
    req->setType(OFPST_FLOW);

    ofp_flow_stats_request reqBody = ofp_flow_stats_request();

    // Wildcards für alle Felder gesetzt = alles wird gematched
    oxm_basic_match match = oxm_basic_match();
    match.wildcards = 0;
    match.wildcards |= OFPFW_DL_TYPE;
    match.wildcards |= OFPFW_IN_PORT;
    match.wildcards |= OFPFW_DL_SRC;
    match.wildcards |= OFPFW_DL_DST;

    reqBody.match = match;
    reqBody.table_id = 0;

    // Struct umwandeln
    int size_reqBody = static_cast<int>(sizeof(reqBody));
    req->setBodyArraySize(size_reqBody);

    for (int i = 0; i < size_reqBody; i++) {
        req->setBody(i, *((uint8_t *) (&reqBody) + i));
    }
        req->setByteLength(40);
        req->setKind(TCP_C_SEND);
        return req;

}

void MonitoringApp::finish() {
    AbstractControllerApp::finish();
 }

