#include "StatsRequest_Wrapper.h"

StatsRequest_Wrapper::StatsRequest_Wrapper(){

}


StatsRequest_Wrapper::~StatsRequest_Wrapper(){

}

int StatsRequest_Wrapper::getSwitchId() const {
    return this->switchId;
}

void StatsRequest_Wrapper::setSwitchId(int switchId){
    this->switchId = switchId;
}

int StatsRequest_Wrapper::getTableLength() const {
    return this->tableLength;
}

void StatsRequest_Wrapper::setTableLength(int tableLength){
    this->tableLength = tableLength;
}

double StatsRequest_Wrapper::getBytesOfPacketsMatched() const {
    return this->avgBytesOfPacketsMatched;
}

void StatsRequest_Wrapper::setBytesOfPacketsMatched(double avgBytesOfPacketsMatched){
    this->avgBytesOfPacketsMatched = avgBytesOfPacketsMatched;
}

double StatsRequest_Wrapper::getNrOfPacketsMatched() const {
    return this->avgNrOfPacketsMatched;
}

void StatsRequest_Wrapper::setNrOfPacketsMatched(double avgNrOfPacketsMatched){
    this->avgNrOfPacketsMatched = avgNrOfPacketsMatched;
}

double StatsRequest_Wrapper::getTimestamp() const {
    return this->timestamp;
}

void StatsRequest_Wrapper::setTimestamp(double timestamp){
    this->timestamp = timestamp;
}
