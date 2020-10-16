

#ifndef HF_REFIRE_WRAPPER_H_
#define HF_REFIRE_WRAPPER_H_

#include "cobject.h"
#include "MACAddress.h"
#include "HyperFlowStructs.h"

using namespace std;

class HF_ReFire_Wrapper: public cObject {

public:
    HF_ReFire_Wrapper();
    ~HF_ReFire_Wrapper();


    const DataChannelEntry& getDataChannelEntry() const;
    void setDataChannelEntry(const DataChannelEntry& dataEntry);


protected:
    DataChannelEntry dataChannelEntry;
};




#endif /* BUFFER_H_ */
