#include <omnetpp.h>
#include <EtherFrame_m.h>
#include <MACAddress.h>
#include <ARPPacket_m.h>
#include <Flow_Table_Entry.h>

using namespace std;

Flow_Table_Entry::Flow_Table_Entry(){
    idleTimeout = 0.;
    hardTimeout = 0.;
}

flow_table_cookie Flow_Table_Entry::getCookie(){
    return cookie;
}

flow_table_counters Flow_Table_Entry::getCounters(){
    return counters;
}

flow_table_flags Flow_Table_Entry::getFlags(){
    return flags;
}

double Flow_Table_Entry::getHardTimeout(){
    return hardTimeout;
}

double Flow_Table_Entry::getIdleTimeout(){
    return idleTimeout;
}

SimTime Flow_Table_Entry::getExpiresAt(){
    return expiresAt;
}

ofp_action_output Flow_Table_Entry::getInstructions(){
    return instructions[0];
}

oxm_basic_match* Flow_Table_Entry::getMatch(){
    return match;
}

int Flow_Table_Entry::getPriority(){
    return priority;
}

void Flow_Table_Entry::setCookie(flow_table_cookie cookie){
    this->cookie = cookie;
}

void Flow_Table_Entry::setCounters(flow_table_counters counters){
    this->counters = counters;
}

void Flow_Table_Entry::setFlags(flow_table_flags flags){
    this->flags = flags;
}

void Flow_Table_Entry::setHardTimeout(double hardTimeout){
    this->hardTimeout = hardTimeout;
}

void Flow_Table_Entry::setIdleTimeout(double idleTimeout){
    this->idleTimeout = idleTimeout;
}

void Flow_Table_Entry::setExpiresAt(SimTime expiresAt){
    this->expiresAt = expiresAt;
}

void Flow_Table_Entry::setInstructions(ofp_action_output instructions[1]){
    this->instructions[0] = instructions[0];
}

void Flow_Table_Entry::setMatch(oxm_basic_match* match){
    this->match = match;
}

void Flow_Table_Entry::setPriority(int priority){
    this->priority = priority;
}
