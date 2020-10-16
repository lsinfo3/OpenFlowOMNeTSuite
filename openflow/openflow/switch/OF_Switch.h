

#ifndef OF_SWITCH_H_
#define OF_SWITCH_H_

#include <omnetpp.h>
#include "TCPSocket.h"

#include "Buffer.h"
#include "Open_Flow_Message_m.h"
#include "Flow_Table.h"
#include <vector>

class OF_Switch: public cSimpleModule
{
public:
    OF_Switch();
    ~OF_Switch();
    void disablePorts(std::vector<int> ports);
    virtual void finish();
    std::vector<ofp_port> portVector;

protected:
    double flowTimeoutPollInterval;
    double serviceTime;
    bool busy;
    bool sendCompletePacket;

    long controlPlanePacket;
    long dataPlanePacket;
    long flowTableHit;
    long flowTableMiss;

    //stats
    simsignal_t dpPingPacketHash;
    simsignal_t cpPingPacketHash;
    simsignal_t queueSize;
    simsignal_t bufferSize;
    simsignal_t waitingTime;

    std::list<cMessage *> msgList;
    //std::vector<ofp_port> portVector;


    Buffer buffer;
    Flow_Table flowTable;
    TCPSocket socket;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void connect(const char *connectToAddress);

    void processQueuedMsg(cMessage *data_msg);
    void handleStatsRequestMessage(Open_Flow_Message *of_msg);
    void handleFeaturesRequestMessage(Open_Flow_Message *of_msg);
    void handleFlowModMessage(Open_Flow_Message *of_msg);
    void handlePacketOutMessage(Open_Flow_Message *of_msg);
    void executePacketOutAction(ofp_action_header *action, EthernetIIFrame *frame, uint32_t inport);
    void processFrame(EthernetIIFrame *frame);
    void handleMissMatchedPacket(EthernetIIFrame *frame);
};


#endif /* OF_SWITCH_H_ */
