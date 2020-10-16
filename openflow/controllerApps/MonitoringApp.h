
#ifndef MONITORINGAPP_H_
#define MONITORINGAPP_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "Switch_Info.h"
#include "OFP_Stats_Reply_m.h"
#include "OFP_Stats_Request_m.h"
#include "OFP_Features_Reply_m.h"
#include "TCPSocket.h"


class MonitoringApp: public AbstractControllerApp {
public:
    MonitoringApp();
    ~MonitoringApp();
    virtual void finish();
private:
    simsignal_t switches_signal;
    simsignal_t tableLengths_signal;
    simsignal_t avgNrOfPacketsMatched_signal;
    simsignal_t avgBytesOfPacketsMatched_signal;
protected:
    double pollInterval;
    void initialize();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    OFP_Stats_Request * createMultipartRequest();
    virtual void handleMessage(cMessage *msg);
    virtual void handleReply(OFP_Stats_Reply * castMsg);
    void sendMultipartRequest();
};

#endif
