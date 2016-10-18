#include <omnetpp.h>
#include "LearningSwitchMapping.h"

using namespace std;

LearningSwitchMapping::LearningSwitchMapping(){

}

int LearningSwitchMapping::getInPort(){
    return this->inPort;
}

void LearningSwitchMapping::setInPort(int inPort){
    this->inPort = inPort;
}

MACAddress LearningSwitchMapping::getAddress(){
    return this->address;
}

void LearningSwitchMapping::setAddress(MACAddress& address){
    this->address = address;
}

Switch_Info* LearningSwitchMapping::getSwInfo(){
    return this->swInfo;
}

void LearningSwitchMapping::setSwInfo(Switch_Info* swInfo){
    this->swInfo = swInfo;
}
