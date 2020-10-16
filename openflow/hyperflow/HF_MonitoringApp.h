

#ifndef HF_MONITORINGAPP_H_
#define HF_MONITORINGAPP_H_

#include <omnetpp.h>
#include "MonitoringApp.h"
#include "StatsRequest_Wrapper.h"
#include "HyperFlowAgent.h"

class HF_MonitoringApp: public MonitoringApp {
public:
    HF_MonitoringApp();
    ~HF_MonitoringApp();
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

    HyperFlowAgent * hfAgent;
    simsignal_t HyperFlowReFireSignalId;
};



#endif /* HF_MONITORINGAPP_H_ */
