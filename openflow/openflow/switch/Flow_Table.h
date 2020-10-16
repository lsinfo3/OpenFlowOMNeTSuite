
#ifndef FLOW_TABLE_H_
#define FLOW_TABLE_H_

#include <vector>
#include <openflow.h>
#include <Flow_Table_Entry.h>

using namespace __gnu_cxx;




class Flow_Table {
public:
    Flow_Table();
    void addEntry(Flow_Table_Entry entry);
    Flow_Table_Entry * lookup(oxm_basic_match &match);
    std::list<Flow_Table_Entry*> lookupAll(oxm_basic_match &match);
    void removeExpiredEntries();
    std::list<Flow_Table_Entry*> getEntryList();


private:
    std::list<Flow_Table_Entry> entryList;

};





#endif /* FLOW_TABLE_H_ */
