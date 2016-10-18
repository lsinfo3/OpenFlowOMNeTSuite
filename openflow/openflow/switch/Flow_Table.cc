#include <omnetpp.h>
#include <EtherFrame_m.h>
#include <MACAddress.h>
#include <ARPPacket_m.h>
#include <Flow_Table.h>

using namespace std;


Flow_Table::Flow_Table() {

}


static inline int flow_fields_match(oxm_basic_match *m1, oxm_basic_match *m2, uint32_t w){
    return (((w & OFPFW_IN_PORT) || m1->OFB_IN_PORT == m2->OFB_IN_PORT)
            && ((w & OFPFW_DL_TYPE) || m1->OFB_ETH_TYPE == m2->OFB_ETH_TYPE )
            && ((w & OFPFW_DL_SRC) || !m1->OFB_ETH_SRC.compareTo(m2->OFB_ETH_SRC))
            && ((w & OFPFW_DL_DST) || !m1->OFB_ETH_DST.compareTo(m2->OFB_ETH_DST)));
}

void Flow_Table::addEntry(Flow_Table_Entry* entry) {
    entryList.push_front(entry);
}



Flow_Table_Entry *Flow_Table::lookup(oxm_basic_match *match){
    list<Flow_Table_Entry*>::iterator iter = entryList.begin();
    EV << "Looking through " << entryList.size() << " Flow Entries!" << endl;

    for(iter =entryList.begin();iter != entryList.end();iter++){

        //check if flow has expired
        if ((*iter)->getExpiresAt() < simTime()){
            entryList.erase(iter);
            delete *iter;
            iter--;
            continue;
        }

        oxm_basic_match *m = const_cast<oxm_basic_match*> ((*iter)->getMatch());
        if (flow_fields_match(match, m, m->wildcards)){
            //adapt idle timer filed if neccessary
            if ((*iter)->getIdleTimeout() != 0){
                (*iter)->setExpiresAt((*iter)->getIdleTimeout()+simTime());
            }
            return *iter;
        }
    }
    return NULL;
}


