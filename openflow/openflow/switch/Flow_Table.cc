#include <omnetpp.h>
#include <EtherFrame_m.h>
#include <MACAddress.h>
#include <ARPPacket_m.h>
#include <Flow_Table.h>

using namespace std;


Flow_Table::Flow_Table() {

}


static inline int flow_fields_match(const oxm_basic_match &m1, const oxm_basic_match &m2, const uint32_t w){
    return (((w & OFPFW_IN_PORT) || m1.OFB_IN_PORT == m2.OFB_IN_PORT)
            && ((w & OFPFW_DL_TYPE) || m1.OFB_ETH_TYPE == m2.OFB_ETH_TYPE )
            && ((w & OFPFW_DL_SRC) || !m1.OFB_ETH_SRC.compareTo(m2.OFB_ETH_SRC))
            && ((w & OFPFW_DL_DST) || !m1.OFB_ETH_DST.compareTo(m2.OFB_ETH_DST)));
}

void Flow_Table::addEntry(Flow_Table_Entry entry) {
    entryList.push_front(entry);
}



Flow_Table_Entry* Flow_Table::lookup(oxm_basic_match &match) {
    EV << "Looking through " << entryList.size() << " Flow Entries!" << '\n';
    for(auto iter =entryList.begin();iter != entryList.end();++iter){

        //check if flow has expired
        if ((*iter).getExpiresAt() < simTime()){
            iter = entryList.erase(iter);
            continue;
        }


        if (flow_fields_match(match, (*iter).getMatch(), (*iter).getMatch().wildcards)){
            //adapt idle timer filed if neccessary
            if ((*iter).getIdleTimeout() != 0){
                (*iter).setExpiresAt((*iter).getIdleTimeout()+simTime());
            }
            return &(*iter);
        }
    }
    return NULL;
}

std::list<Flow_Table_Entry*> Flow_Table::lookupAll(oxm_basic_match &match) {
    EV << "Looking through " << entryList.size() << " Flow Entries!" << '\n';

    std::list<Flow_Table_Entry*> list;
    for(auto iter =entryList.begin();iter != entryList.end();++iter){
        if (flow_fields_match(match, (*iter).getMatch(), match.wildcards)){
            list.push_back(&(*iter));
        }
    }
    return list;
}

std::list<Flow_Table_Entry*> Flow_Table::getEntryList() {
    std::list<Flow_Table_Entry*> list;
    for(auto iter =entryList.begin();iter != entryList.end();++iter){
        list.push_back(&(*iter));

    }
    return list;
}

