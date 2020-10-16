//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Stats_Reply.msg.
//

#ifndef _OFP_STATS_REPLY_M_H_
#define _OFP_STATS_REPLY_M_H_

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
 * Class generated from <tt>messages/OFP_Stats_Reply.msg:14</tt> by nedtool.
 * <pre>
 * packet OFP_Stats_Reply extends Open_Flow_Message
 * {
 *     uint16_t type;  //* One of the OFPMP_* constants.   
 *     uint16_t flags; //* OFPMPF_REPLY_* flags.   
 *     uint8_t pad[4];
 *     uint8_t body[]; //* Body of the reply.   
 * }
 * </pre>
 */
class OFP_Stats_Reply : public ::Open_Flow_Message
{
  protected:
    uint16_t type_var;
    uint16_t flags_var;
    uint8_t pad_var[4];
    uint8_t *body_var; // array ptr
    unsigned int body_arraysize;

  private:
    void copy(const OFP_Stats_Reply& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OFP_Stats_Reply&);

  public:
    OFP_Stats_Reply(const char *name=NULL, int kind=0);
    OFP_Stats_Reply(const OFP_Stats_Reply& other);
    virtual ~OFP_Stats_Reply();
    OFP_Stats_Reply& operator=(const OFP_Stats_Reply& other);
    virtual OFP_Stats_Reply *dup() const {return new OFP_Stats_Reply(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint16_t getType() const;
    virtual void setType(uint16_t type);
    virtual uint16_t getFlags() const;
    virtual void setFlags(uint16_t flags);
    virtual unsigned int getPadArraySize() const;
    virtual uint8_t getPad(unsigned int k) const;
    virtual void setPad(unsigned int k, uint8_t pad);
    virtual void setBodyArraySize(unsigned int size);
    virtual unsigned int getBodyArraySize() const;
    virtual uint8_t getBody(unsigned int k) const;
    virtual void setBody(unsigned int k, uint8_t body);
};

inline void doPacking(cCommBuffer *b, OFP_Stats_Reply& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OFP_Stats_Reply& obj) {obj.parsimUnpack(b);}


#endif // ifndef _OFP_STATS_REPLY_M_H_

