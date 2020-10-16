//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Stats_Request.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Stats_Request_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(OFP_Stats_Request);

OFP_Stats_Request::OFP_Stats_Request(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->type_var = 0;
    this->flags_var = 0;
    for (unsigned int i=0; i<4; i++)
        this->pad_var[i] = 0;
    body_arraysize = 0;
    this->body_var = 0;
}

OFP_Stats_Request::OFP_Stats_Request(const OFP_Stats_Request& other) : ::Open_Flow_Message(other)
{
    body_arraysize = 0;
    this->body_var = 0;
    copy(other);
}

OFP_Stats_Request::~OFP_Stats_Request()
{
    delete [] body_var;
}

OFP_Stats_Request& OFP_Stats_Request::operator=(const OFP_Stats_Request& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Stats_Request::copy(const OFP_Stats_Request& other)
{
    this->type_var = other.type_var;
    this->flags_var = other.flags_var;
    for (unsigned int i=0; i<4; i++)
        this->pad_var[i] = other.pad_var[i];
    delete [] this->body_var;
    this->body_var = (other.body_arraysize==0) ? NULL : new uint8_t[other.body_arraysize];
    body_arraysize = other.body_arraysize;
    for (unsigned int i=0; i<body_arraysize; i++)
        this->body_var[i] = other.body_var[i];
}

void OFP_Stats_Request::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->pad_var,4);
    b->pack(body_arraysize);
    doPacking(b,this->body_var,body_arraysize);
}

void OFP_Stats_Request::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->pad_var,4);
    delete [] this->body_var;
    b->unpack(body_arraysize);
    if (body_arraysize==0) {
        this->body_var = 0;
    } else {
        this->body_var = new uint8_t[body_arraysize];
        doUnpacking(b,this->body_var,body_arraysize);
    }
}

uint16_t OFP_Stats_Request::getType() const
{
    return type_var;
}

void OFP_Stats_Request::setType(uint16_t type)
{
    this->type_var = type;
}

uint16_t OFP_Stats_Request::getFlags() const
{
    return flags_var;
}

void OFP_Stats_Request::setFlags(uint16_t flags)
{
    this->flags_var = flags;
}

unsigned int OFP_Stats_Request::getPadArraySize() const
{
    return 4;
}

uint8_t OFP_Stats_Request::getPad(unsigned int k) const
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    return pad_var[k];
}

void OFP_Stats_Request::setPad(unsigned int k, uint8_t pad)
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    this->pad_var[k] = pad;
}

void OFP_Stats_Request::setBodyArraySize(unsigned int size)
{
    uint8_t *body_var2 = (size==0) ? NULL : new uint8_t[size];
    unsigned int sz = body_arraysize < size ? body_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        body_var2[i] = this->body_var[i];
    for (unsigned int i=sz; i<size; i++)
        body_var2[i] = 0;
    body_arraysize = size;
    delete [] this->body_var;
    this->body_var = body_var2;
}

unsigned int OFP_Stats_Request::getBodyArraySize() const
{
    return body_arraysize;
}

uint8_t OFP_Stats_Request::getBody(unsigned int k) const
{
    if (k>=body_arraysize) throw cRuntimeError("Array of size %d indexed by %d", body_arraysize, k);
    return body_var[k];
}

void OFP_Stats_Request::setBody(unsigned int k, uint8_t body)
{
    if (k>=body_arraysize) throw cRuntimeError("Array of size %d indexed by %d", body_arraysize, k);
    this->body_var[k] = body;
}

class OFP_Stats_RequestDescriptor : public cClassDescriptor
{
  public:
    OFP_Stats_RequestDescriptor();
    virtual ~OFP_Stats_RequestDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OFP_Stats_RequestDescriptor);

OFP_Stats_RequestDescriptor::OFP_Stats_RequestDescriptor() : cClassDescriptor("OFP_Stats_Request", "Open_Flow_Message")
{
}

OFP_Stats_RequestDescriptor::~OFP_Stats_RequestDescriptor()
{
}

bool OFP_Stats_RequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Stats_Request *>(obj)!=NULL;
}

const char *OFP_Stats_RequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Stats_RequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int OFP_Stats_RequestDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Stats_RequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "flags",
        "pad",
        "body",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int OFP_Stats_RequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "pad")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "body")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Stats_RequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",
        "uint16_t",
        "uint8_t",
        "uint8_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Stats_RequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OFP_Stats_RequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Stats_Request *pp = (OFP_Stats_Request *)object; (void)pp;
    switch (field) {
        case 2: return 4;
        case 3: return pp->getBodyArraySize();
        default: return 0;
    }
}

std::string OFP_Stats_RequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Stats_Request *pp = (OFP_Stats_Request *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getType());
        case 1: return ulong2string(pp->getFlags());
        case 2: return ulong2string(pp->getPad(i));
        case 3: return ulong2string(pp->getBody(i));
        default: return "";
    }
}

bool OFP_Stats_RequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Stats_Request *pp = (OFP_Stats_Request *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2ulong(value)); return true;
        case 1: pp->setFlags(string2ulong(value)); return true;
        case 2: pp->setPad(i,string2ulong(value)); return true;
        case 3: pp->setBody(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Stats_RequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OFP_Stats_RequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Stats_Request *pp = (OFP_Stats_Request *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


