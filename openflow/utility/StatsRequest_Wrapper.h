

#ifndef STATSREQUEST_WRAPPER_H_
#define STATSREQUEST_WRAPPER_H_

#include "cobject.h"
#include <coutvector.h>

using namespace std;

class StatsRequest_Wrapper: public cObject {

public:
    StatsRequest_Wrapper();
    ~StatsRequest_Wrapper();

    int getSwitchId() const;
    void setSwitchId(int switchId);

    int getTableLength() const;
    void setTableLength(int tableLength);

    double getBytesOfPacketsMatched() const;
    void setBytesOfPacketsMatched(double avgBytesOfPacketsMatched);

    double getNrOfPacketsMatched() const;
    void setNrOfPacketsMatched(double avgNrOfPacketsMatched);

    double getTimestamp() const;
    void setTimestamp(double timestamp);

protected:
    int switchId;
    int tableLength;
    double avgBytesOfPacketsMatched;
    double avgNrOfPacketsMatched;
    double timestamp;
};



#endif /* STATSREQUEST_WRAPPER_H_ */
