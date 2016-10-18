#include <omnetpp.h>
#include "Switch_Info.h"

using namespace std;

Switch_Info::Switch_Info(){

}


int Switch_Info::getConnId() {
        return connID;
}

void Switch_Info::setConnId(int connId) {
        connID = connId;
}

int Switch_Info::getVersion() {
        return connID;
}

void Switch_Info::setVersion(int version) {
        version = version;
}


string Switch_Info::getMacAddress() {
        return macAddress;
}

void Switch_Info::setMacAddress(string macAddress) {
        this->macAddress = macAddress;
}

int Switch_Info::getNumOfPorts() {
        return numOfPorts;
}

void Switch_Info::setNumOfPorts(int numOfPorts) {
        this->numOfPorts = numOfPorts;
}

TCPSocket* Switch_Info::getSocket() {
        return socket;
}

void Switch_Info::setSocket(TCPSocket* socket) {
        this->socket = socket;
}
