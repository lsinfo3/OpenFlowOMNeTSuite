

#ifndef KN_MONITORINGAPP_H_
#define KN_MONITORINGAPP_H_

#include <omnetpp.h>
#include "MonitoringApp.h"
#include "KandooAgent.h"
#include "StatsRequest_Wrapper.h"

class KN_MonitoringApp: public MonitoringApp {
public:
    KN_MonitoringApp();
    ~KN_MonitoringApp();
private:
    simsignal_t switches_signal;
    simsignal_t tableLengths_signal;
    simsignal_t avgNrOfPacketsMatched_signal;
    simsignal_t avgBytesOfPacketsMatched_signal;
    simsignal_t timeDiff_signal;
protected:
    void initialize();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void handleReply(OFP_Stats_Reply * castMsg);

    KandooAgent * kandooAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;
};




#endif /* KN_MONITORINGAPP_H_ */
