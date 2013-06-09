//
// Generated file, do not edit! Created by opp_msgc 4.2 from overlay/myoverlay/MyOverlay.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MyOverlay_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("MessageType");
    if (!e) enums.getInstance()->add(e = new cEnum("MessageType"));
    e->insert(MSG_JOIN, "MSG_JOIN");
    e->insert(MSG_JOIN_ACCEPT, "MSG_JOIN_ACCEPT");
    e->insert(MSG_JOIN_DECLINE, "MSG_JOIN_DECLINE");
    e->insert(MSG_KEY_RESERVED, "MSG_KEY_RESERVED");
    e->insert(MSG_KEY_RESERVED_ACK, "MSG_KEY_RESERVED_ACK");
    e->insert(MSG_KEY_RESERVED_DECLINE, "MSG_KEY_RESERVED_DECLINE");
    e->insert(MSG_UNKNOWN_HOST, "MSG_UNKNOWN_HOST");
    e->insert(MSG_FIND_AVAI_KEY, "MSG_FIND_AVAI_KEY");
    e->insert(MSG_AVAI_KEY, "MSG_AVAI_KEY");
    e->insert(MSG_NEXT_CHAIN, "MSG_NEXT_CHAIN");
    e->insert(MSG_NONE, "MSG_NONE");
    e->insert(MSG_JOINED, "MSG_JOINED");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("NodeColor");
    if (!e) enums.getInstance()->add(e = new cEnum("NodeColor"));
    e->insert(WHITE_NODE, "WHITE_NODE");
    e->insert(BLACK_NODE, "BLACK_NODE");
    e->insert(UNKNOWN_COLOR, "UNKNOWN_COLOR");
);

Register_Class(MyNeighborCall);

MyNeighborCall::MyNeighborCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
}

MyNeighborCall::MyNeighborCall(const MyNeighborCall& other) : BaseCallMessage(other)
{
    copy(other);
}

MyNeighborCall::~MyNeighborCall()
{
}

MyNeighborCall& MyNeighborCall::operator=(const MyNeighborCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void MyNeighborCall::copy(const MyNeighborCall& other)
{
    this->destinationKey_var = other.destinationKey_var;
}

void MyNeighborCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->destinationKey_var);
}

void MyNeighborCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->destinationKey_var);
}

OverlayKey& MyNeighborCall::getDestinationKey()
{
    return destinationKey_var;
}

void MyNeighborCall::setDestinationKey(const OverlayKey& destinationKey)
{
    this->destinationKey_var = destinationKey;
}

class MyNeighborCallDescriptor : public cClassDescriptor
{
  public:
    MyNeighborCallDescriptor();
    virtual ~MyNeighborCallDescriptor();

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

Register_ClassDescriptor(MyNeighborCallDescriptor);

MyNeighborCallDescriptor::MyNeighborCallDescriptor() : cClassDescriptor("MyNeighborCall", "BaseCallMessage")
{
}

MyNeighborCallDescriptor::~MyNeighborCallDescriptor()
{
}

bool MyNeighborCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MyNeighborCall *>(obj)!=NULL;
}

const char *MyNeighborCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MyNeighborCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int MyNeighborCallDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *MyNeighborCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destinationKey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int MyNeighborCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationKey")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MyNeighborCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *MyNeighborCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MyNeighborCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborCall *pp = (MyNeighborCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MyNeighborCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborCall *pp = (MyNeighborCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestinationKey(); return out.str();}
        default: return "";
    }
}

bool MyNeighborCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborCall *pp = (MyNeighborCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *MyNeighborCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *MyNeighborCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborCall *pp = (MyNeighborCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestinationKey()); break;
        default: return NULL;
    }
}

Register_Class(P2PMessageCall);

P2PMessageCall::P2PMessageCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
    this->msgType_var = 0;
    this->rspTo_var = 0;
    this->nodeColor_var = 0;
    this->timestamp_var = 0;
    this->numRing_var = 0;
}

P2PMessageCall::P2PMessageCall(const P2PMessageCall& other) : BaseCallMessage(other)
{
    copy(other);
}

P2PMessageCall::~P2PMessageCall()
{
}

P2PMessageCall& P2PMessageCall::operator=(const P2PMessageCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void P2PMessageCall::copy(const P2PMessageCall& other)
{
    this->msgType_var = other.msgType_var;
    this->rspTo_var = other.rspTo_var;
    this->nodeColor_var = other.nodeColor_var;
    this->timestamp_var = other.timestamp_var;
    this->senderKey_var = other.senderKey_var;
    this->destKey_var = other.destKey_var;
    this->lastHop_var = other.lastHop_var;
    this->bootstrapKey_var = other.bootstrapKey_var;
    this->propKey_var = other.propKey_var;
    this->numRing_var = other.numRing_var;
}

void P2PMessageCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->msgType_var);
    doPacking(b,this->rspTo_var);
    doPacking(b,this->nodeColor_var);
    doPacking(b,this->timestamp_var);
    doPacking(b,this->senderKey_var);
    doPacking(b,this->destKey_var);
    doPacking(b,this->lastHop_var);
    doPacking(b,this->bootstrapKey_var);
    doPacking(b,this->propKey_var);
    doPacking(b,this->numRing_var);
}

void P2PMessageCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->msgType_var);
    doUnpacking(b,this->rspTo_var);
    doUnpacking(b,this->nodeColor_var);
    doUnpacking(b,this->timestamp_var);
    doUnpacking(b,this->senderKey_var);
    doUnpacking(b,this->destKey_var);
    doUnpacking(b,this->lastHop_var);
    doUnpacking(b,this->bootstrapKey_var);
    doUnpacking(b,this->propKey_var);
    doUnpacking(b,this->numRing_var);
}

int P2PMessageCall::getMsgType() const
{
    return msgType_var;
}

void P2PMessageCall::setMsgType(int msgType)
{
    this->msgType_var = msgType;
}

int P2PMessageCall::getRspTo() const
{
    return rspTo_var;
}

void P2PMessageCall::setRspTo(int rspTo)
{
    this->rspTo_var = rspTo;
}

int P2PMessageCall::getNodeColor() const
{
    return nodeColor_var;
}

void P2PMessageCall::setNodeColor(int nodeColor)
{
    this->nodeColor_var = nodeColor;
}

int P2PMessageCall::getTimestamp() const
{
    return timestamp_var;
}

void P2PMessageCall::setTimestamp(int timestamp)
{
    this->timestamp_var = timestamp;
}

HoneyCombKey& P2PMessageCall::getSenderKey()
{
    return senderKey_var;
}

void P2PMessageCall::setSenderKey(const HoneyCombKey& senderKey)
{
    this->senderKey_var = senderKey;
}

HoneyCombKey& P2PMessageCall::getDestKey()
{
    return destKey_var;
}

void P2PMessageCall::setDestKey(const HoneyCombKey& destKey)
{
    this->destKey_var = destKey;
}

HoneyCombKey& P2PMessageCall::getLastHop()
{
    return lastHop_var;
}

void P2PMessageCall::setLastHop(const HoneyCombKey& lastHop)
{
    this->lastHop_var = lastHop;
}

HoneyCombKey& P2PMessageCall::getBootstrapKey()
{
    return bootstrapKey_var;
}

void P2PMessageCall::setBootstrapKey(const HoneyCombKey& bootstrapKey)
{
    this->bootstrapKey_var = bootstrapKey;
}

HoneyCombKey& P2PMessageCall::getPropKey()
{
    return propKey_var;
}

void P2PMessageCall::setPropKey(const HoneyCombKey& propKey)
{
    this->propKey_var = propKey;
}

int P2PMessageCall::getNumRing() const
{
    return numRing_var;
}

void P2PMessageCall::setNumRing(int numRing)
{
    this->numRing_var = numRing;
}

class P2PMessageCallDescriptor : public cClassDescriptor
{
  public:
    P2PMessageCallDescriptor();
    virtual ~P2PMessageCallDescriptor();

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

Register_ClassDescriptor(P2PMessageCallDescriptor);

P2PMessageCallDescriptor::P2PMessageCallDescriptor() : cClassDescriptor("P2PMessageCall", "BaseCallMessage")
{
}

P2PMessageCallDescriptor::~P2PMessageCallDescriptor()
{
}

bool P2PMessageCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2PMessageCall *>(obj)!=NULL;
}

const char *P2PMessageCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2PMessageCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int P2PMessageCallDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *P2PMessageCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msgType",
        "rspTo",
        "nodeColor",
        "timestamp",
        "senderKey",
        "destKey",
        "lastHop",
        "bootstrapKey",
        "propKey",
        "numRing",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int P2PMessageCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgType")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "rspTo")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeColor")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderKey")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "destKey")==0) return base+5;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastHop")==0) return base+6;
    if (fieldName[0]=='b' && strcmp(fieldName, "bootstrapKey")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "propKey")==0) return base+8;
    if (fieldName[0]=='n' && strcmp(fieldName, "numRing")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2PMessageCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *P2PMessageCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MessageType";
            return NULL;
        case 1:
            if (!strcmp(propertyname,"enum")) return "MessageType";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "NodeColor";
            return NULL;
        default: return NULL;
    }
}

int P2PMessageCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageCall *pp = (P2PMessageCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2PMessageCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageCall *pp = (P2PMessageCall *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMsgType());
        case 1: return long2string(pp->getRspTo());
        case 2: return long2string(pp->getNodeColor());
        case 3: return long2string(pp->getTimestamp());
        case 4: {std::stringstream out; out << pp->getSenderKey(); return out.str();}
        case 5: {std::stringstream out; out << pp->getDestKey(); return out.str();}
        case 6: {std::stringstream out; out << pp->getLastHop(); return out.str();}
        case 7: {std::stringstream out; out << pp->getBootstrapKey(); return out.str();}
        case 8: {std::stringstream out; out << pp->getPropKey(); return out.str();}
        case 9: return long2string(pp->getNumRing());
        default: return "";
    }
}

bool P2PMessageCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageCall *pp = (P2PMessageCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsgType(string2long(value)); return true;
        case 1: pp->setRspTo(string2long(value)); return true;
        case 2: pp->setNodeColor(string2long(value)); return true;
        case 3: pp->setTimestamp(string2long(value)); return true;
        case 9: pp->setNumRing(string2long(value)); return true;
        default: return false;
    }
}

const char *P2PMessageCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        "HoneyCombKey",
        NULL,
    };
    return (field>=0 && field<10) ? fieldStructNames[field] : NULL;
}

void *P2PMessageCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageCall *pp = (P2PMessageCall *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getSenderKey()); break;
        case 5: return (void *)(&pp->getDestKey()); break;
        case 6: return (void *)(&pp->getLastHop()); break;
        case 7: return (void *)(&pp->getBootstrapKey()); break;
        case 8: return (void *)(&pp->getPropKey()); break;
        default: return NULL;
    }
}

Register_Class(P2PMessageResponse);

P2PMessageResponse::P2PMessageResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
    this->msgType_var = 0;
    this->nodeColor_var = 0;
    this->propX_var = 0;
    this->propY_var = 0;
    this->propZ_var = 0;
}

P2PMessageResponse::P2PMessageResponse(const P2PMessageResponse& other) : BaseResponseMessage(other)
{
    copy(other);
}

P2PMessageResponse::~P2PMessageResponse()
{
}

P2PMessageResponse& P2PMessageResponse::operator=(const P2PMessageResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void P2PMessageResponse::copy(const P2PMessageResponse& other)
{
    this->msgType_var = other.msgType_var;
    this->nodeColor_var = other.nodeColor_var;
    this->senderAddress_var = other.senderAddress_var;
    this->senderKey_var = other.senderKey_var;
    this->propKey_var = other.propKey_var;
    this->propX_var = other.propX_var;
    this->propY_var = other.propY_var;
    this->propZ_var = other.propZ_var;
}

void P2PMessageResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->msgType_var);
    doPacking(b,this->nodeColor_var);
    doPacking(b,this->senderAddress_var);
    doPacking(b,this->senderKey_var);
    doPacking(b,this->propKey_var);
    doPacking(b,this->propX_var);
    doPacking(b,this->propY_var);
    doPacking(b,this->propZ_var);
}

void P2PMessageResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->msgType_var);
    doUnpacking(b,this->nodeColor_var);
    doUnpacking(b,this->senderAddress_var);
    doUnpacking(b,this->senderKey_var);
    doUnpacking(b,this->propKey_var);
    doUnpacking(b,this->propX_var);
    doUnpacking(b,this->propY_var);
    doUnpacking(b,this->propZ_var);
}

int P2PMessageResponse::getMsgType() const
{
    return msgType_var;
}

void P2PMessageResponse::setMsgType(int msgType)
{
    this->msgType_var = msgType;
}

int P2PMessageResponse::getNodeColor() const
{
    return nodeColor_var;
}

void P2PMessageResponse::setNodeColor(int nodeColor)
{
    this->nodeColor_var = nodeColor;
}

TransportAddress& P2PMessageResponse::getSenderAddress()
{
    return senderAddress_var;
}

void P2PMessageResponse::setSenderAddress(const TransportAddress& senderAddress)
{
    this->senderAddress_var = senderAddress;
}

OverlayKey& P2PMessageResponse::getSenderKey()
{
    return senderKey_var;
}

void P2PMessageResponse::setSenderKey(const OverlayKey& senderKey)
{
    this->senderKey_var = senderKey;
}

OverlayKey& P2PMessageResponse::getPropKey()
{
    return propKey_var;
}

void P2PMessageResponse::setPropKey(const OverlayKey& propKey)
{
    this->propKey_var = propKey;
}

int P2PMessageResponse::getPropX() const
{
    return propX_var;
}

void P2PMessageResponse::setPropX(int propX)
{
    this->propX_var = propX;
}

int P2PMessageResponse::getPropY() const
{
    return propY_var;
}

void P2PMessageResponse::setPropY(int propY)
{
    this->propY_var = propY;
}

int P2PMessageResponse::getPropZ() const
{
    return propZ_var;
}

void P2PMessageResponse::setPropZ(int propZ)
{
    this->propZ_var = propZ;
}

class P2PMessageResponseDescriptor : public cClassDescriptor
{
  public:
    P2PMessageResponseDescriptor();
    virtual ~P2PMessageResponseDescriptor();

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

Register_ClassDescriptor(P2PMessageResponseDescriptor);

P2PMessageResponseDescriptor::P2PMessageResponseDescriptor() : cClassDescriptor("P2PMessageResponse", "BaseResponseMessage")
{
}

P2PMessageResponseDescriptor::~P2PMessageResponseDescriptor()
{
}

bool P2PMessageResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2PMessageResponse *>(obj)!=NULL;
}

const char *P2PMessageResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2PMessageResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int P2PMessageResponseDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *P2PMessageResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msgType",
        "nodeColor",
        "senderAddress",
        "senderKey",
        "propKey",
        "propX",
        "propY",
        "propZ",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int P2PMessageResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgType")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeColor")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderKey")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "propKey")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "propX")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "propY")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "propZ")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2PMessageResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "TransportAddress",
        "OverlayKey",
        "OverlayKey",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *P2PMessageResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MessageType";
            return NULL;
        case 1:
            if (!strcmp(propertyname,"enum")) return "NodeColor";
            return NULL;
        default: return NULL;
    }
}

int P2PMessageResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageResponse *pp = (P2PMessageResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2PMessageResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageResponse *pp = (P2PMessageResponse *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMsgType());
        case 1: return long2string(pp->getNodeColor());
        case 2: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        case 3: {std::stringstream out; out << pp->getSenderKey(); return out.str();}
        case 4: {std::stringstream out; out << pp->getPropKey(); return out.str();}
        case 5: return long2string(pp->getPropX());
        case 6: return long2string(pp->getPropY());
        case 7: return long2string(pp->getPropZ());
        default: return "";
    }
}

bool P2PMessageResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageResponse *pp = (P2PMessageResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsgType(string2long(value)); return true;
        case 1: pp->setNodeColor(string2long(value)); return true;
        case 5: pp->setPropX(string2long(value)); return true;
        case 6: pp->setPropY(string2long(value)); return true;
        case 7: pp->setPropZ(string2long(value)); return true;
        default: return false;
    }
}

const char *P2PMessageResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        "TransportAddress",
        "OverlayKey",
        "OverlayKey",
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *P2PMessageResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2PMessageResponse *pp = (P2PMessageResponse *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getSenderAddress()); break;
        case 3: return (void *)(&pp->getSenderKey()); break;
        case 4: return (void *)(&pp->getPropKey()); break;
        default: return NULL;
    }
}

Register_Class(MyNeighborResponse);

MyNeighborResponse::MyNeighborResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
}

MyNeighborResponse::MyNeighborResponse(const MyNeighborResponse& other) : BaseResponseMessage(other)
{
    copy(other);
}

MyNeighborResponse::~MyNeighborResponse()
{
}

MyNeighborResponse& MyNeighborResponse::operator=(const MyNeighborResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void MyNeighborResponse::copy(const MyNeighborResponse& other)
{
    this->respondingNode_var = other.respondingNode_var;
    this->prevNeighbor_var = other.prevNeighbor_var;
    this->nextNeighbor_var = other.nextNeighbor_var;
}

void MyNeighborResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->respondingNode_var);
    doPacking(b,this->prevNeighbor_var);
    doPacking(b,this->nextNeighbor_var);
}

void MyNeighborResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->respondingNode_var);
    doUnpacking(b,this->prevNeighbor_var);
    doUnpacking(b,this->nextNeighbor_var);
}

NodeHandle& MyNeighborResponse::getRespondingNode()
{
    return respondingNode_var;
}

void MyNeighborResponse::setRespondingNode(const NodeHandle& respondingNode)
{
    this->respondingNode_var = respondingNode;
}

NodeHandle& MyNeighborResponse::getPrevNeighbor()
{
    return prevNeighbor_var;
}

void MyNeighborResponse::setPrevNeighbor(const NodeHandle& prevNeighbor)
{
    this->prevNeighbor_var = prevNeighbor;
}

NodeHandle& MyNeighborResponse::getNextNeighbor()
{
    return nextNeighbor_var;
}

void MyNeighborResponse::setNextNeighbor(const NodeHandle& nextNeighbor)
{
    this->nextNeighbor_var = nextNeighbor;
}

class MyNeighborResponseDescriptor : public cClassDescriptor
{
  public:
    MyNeighborResponseDescriptor();
    virtual ~MyNeighborResponseDescriptor();

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

Register_ClassDescriptor(MyNeighborResponseDescriptor);

MyNeighborResponseDescriptor::MyNeighborResponseDescriptor() : cClassDescriptor("MyNeighborResponse", "BaseResponseMessage")
{
}

MyNeighborResponseDescriptor::~MyNeighborResponseDescriptor()
{
}

bool MyNeighborResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MyNeighborResponse *>(obj)!=NULL;
}

const char *MyNeighborResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MyNeighborResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int MyNeighborResponseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *MyNeighborResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "respondingNode",
        "prevNeighbor",
        "nextNeighbor",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int MyNeighborResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "respondingNode")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "prevNeighbor")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextNeighbor")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MyNeighborResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "NodeHandle",
        "NodeHandle",
        "NodeHandle",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *MyNeighborResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MyNeighborResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborResponse *pp = (MyNeighborResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MyNeighborResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborResponse *pp = (MyNeighborResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRespondingNode(); return out.str();}
        case 1: {std::stringstream out; out << pp->getPrevNeighbor(); return out.str();}
        case 2: {std::stringstream out; out << pp->getNextNeighbor(); return out.str();}
        default: return "";
    }
}

bool MyNeighborResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborResponse *pp = (MyNeighborResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *MyNeighborResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "NodeHandle",
        "NodeHandle",
        "NodeHandle",
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *MyNeighborResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MyNeighborResponse *pp = (MyNeighborResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRespondingNode()); break;
        case 1: return (void *)(&pp->getPrevNeighbor()); break;
        case 2: return (void *)(&pp->getNextNeighbor()); break;
        default: return NULL;
    }
}


