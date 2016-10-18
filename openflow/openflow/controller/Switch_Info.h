
#ifndef SWITCH_INFO_H_
#define SWITCH_INFO_H_

#include <openflow.h>
#include "TCPSocket.h"

using namespace __gnu_cxx;

class Switch_Info {
    public:
        Switch_Info();

        int getConnId();
        void setConnId(int connId);
        int getVersion();
        void setVersion(int version);
        std::string getMacAddress();
        void setMacAddress(std::string macAddress);
        int getNumOfPorts();
        void setNumOfPorts(int numOfPorts);
        TCPSocket* getSocket();
        void setSocket(TCPSocket* socket);


    protected:
        int connID;
        int numOfPorts;
        std::string macAddress;
        TCPSocket *socket;
        int version;

};

#endif /* FLOW_TABLE_H_ */
