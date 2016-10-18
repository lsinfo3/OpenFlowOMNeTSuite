
#ifndef LEARNINGSWITCH_H_
#define LEARNINGSWITCH_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "LearningSwitchMapping.h"
#include "MACAddress.h"

class LearningSwitch:public AbstractControllerApp {


public:
    LearningSwitch();
    ~LearningSwitch();

protected:
    std::list<LearningSwitchMapping *> mappingList;
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void doSwitching(OFP_Packet_In *packet_in_msg);
    LearningSwitchMapping * lookUpMacAddress(MACAddress address,Switch_Info * swInfo);



};


#endif
