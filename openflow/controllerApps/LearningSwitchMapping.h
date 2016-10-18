

#ifndef LEARNINGSWITCHMAPPING_H_
#define LEARNINGSWITCHMAPPING_H_

#include <openflow.h>
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "MACAddress.h"

using namespace __gnu_cxx;

class LearningSwitchMapping {
    public:
        LearningSwitchMapping();
        
        int getInPort();
        void setInPort(int inPort);
        MACAddress getAddress();
        void setAddress(MACAddress& address);
        Switch_Info* getSwInfo();
        void setSwInfo(Switch_Info* swInfo);

    protected:
        Switch_Info *swInfo;
        MACAddress address;
        int inPort;

};

#endif /* FLOW_TABLE_H_ */
