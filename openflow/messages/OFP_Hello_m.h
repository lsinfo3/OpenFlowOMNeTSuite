//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Hello.msg.
//

#ifndef _OFP_HELLO_M_H_
#define _OFP_HELLO_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
    #include "openflow.h"
    #include "Open_Flow_Message_m.h"    
    
// }}

/**
 * Class generated from <tt>messages/OFP_Hello.msg:13</tt> by nedtool.
 * <pre>
 * packet OFP_Hello extends Open_Flow_Message
 * {
 * }
 * </pre>
 */
class OFP_Hello : public ::Open_Flow_Message
{
  protected:

  private:
    void copy(const OFP_Hello& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OFP_Hello&);

  public:
    OFP_Hello(const char *name=NULL, int kind=0);
    OFP_Hello(const OFP_Hello& other);
    virtual ~OFP_Hello();
    OFP_Hello& operator=(const OFP_Hello& other);
    virtual OFP_Hello *dup() const {return new OFP_Hello(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
};

inline void doPacking(cCommBuffer *b, OFP_Hello& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OFP_Hello& obj) {obj.parsimUnpack(b);}


#endif // ifndef _OFP_HELLO_M_H_

