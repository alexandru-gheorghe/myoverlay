//
// Generated file, do not edit! Created by opp_msgc 4.2 from overlay/myoverlay/MyOverlay.msg.
//

#ifndef _MYOVERLAY_M_H_
#define _MYOVERLAY_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include <NodeHandle.h>
#include <OverlayKey.h>
#include <CommonMessages_m.h>
#include <TransportAddress.h>
#include "HoneyCombKey.h"
// }}



/**
 * Enum generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * enum MessageType 
 * {
 * 	MSG_JOIN = 1;
 * 	MSG_JOIN_ACCEPT  = 2;
 * 	MSG_JOIN_DECLINE = 3;
 * 	MSG_KEY_RESERVED = 4;
 * 	MSG_KEY_RESERVED_ACK = 5;
 * 	MSG_KEY_RESERVED_DECLINE = 6;
 * 	MSG_UNKNOWN_HOST = 7;
 * 	MSG_FIND_AVAI_KEY = 8;
 * 	MSG_AVAI_KEY = 9;
 * 	MSG_NEXT_CHAIN = 10;
 * 	MSG_NONE	= 11;
 * 	MSG_JOINED  = 12;
 * }
 * </pre>
 */
enum MessageType {
    MSG_JOIN = 1,
    MSG_JOIN_ACCEPT = 2,
    MSG_JOIN_DECLINE = 3,
    MSG_KEY_RESERVED = 4,
    MSG_KEY_RESERVED_ACK = 5,
    MSG_KEY_RESERVED_DECLINE = 6,
    MSG_UNKNOWN_HOST = 7,
    MSG_FIND_AVAI_KEY = 8,
    MSG_AVAI_KEY = 9,
    MSG_NEXT_CHAIN = 10,
    MSG_NONE = 11,
    MSG_JOINED = 12
};

/**
 * Enum generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * enum NodeColor 
 * {
 * 	WHITE_NODE = 1;
 * 	BLACK_NODE = 2;
 * 	UNKNOWN_COLOR = 3;
 * }
 * </pre>
 */
enum NodeColor {
    WHITE_NODE = 1,
    BLACK_NODE = 2,
    UNKNOWN_COLOR = 3
};

/**
 * Class generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * packet MyNeighborCall extends BaseCallMessage
 * {
 *     OverlayKey destinationKey;
 * };
 * </pre>
 */
class MyNeighborCall : public ::BaseCallMessage
{
  protected:
    OverlayKey destinationKey_var;

  private:
    void copy(const MyNeighborCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MyNeighborCall&);

  public:
    MyNeighborCall(const char *name=NULL, int kind=0);
    MyNeighborCall(const MyNeighborCall& other);
    virtual ~MyNeighborCall();
    MyNeighborCall& operator=(const MyNeighborCall& other);
    virtual MyNeighborCall *dup() const {return new MyNeighborCall(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual OverlayKey& getDestinationKey();
    virtual const OverlayKey& getDestinationKey() const {return const_cast<MyNeighborCall*>(this)->getDestinationKey();}
    virtual void setDestinationKey(const OverlayKey& destinationKey);
};

inline void doPacking(cCommBuffer *b, MyNeighborCall& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MyNeighborCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * packet P2PMessageCall extends BaseCallMessage 
 * {
 * 	int msgType enum (MessageType);
 * 	int rspTo	 enum (MessageType);
 * 	int nodeColor enum (NodeColor);
 * 	int timestamp;
 * 	HoneyCombKey senderKey;
 * 	HoneyCombKey destKey;
 * 	HoneyCombKey lastHop;
 * 	HoneyCombKey bootstrapKey;
 * 	HoneyCombKey propKey;
 * 	int numRing;
 * };
 * </pre>
 */
class P2PMessageCall : public ::BaseCallMessage
{
  protected:
    int msgType_var;
    int rspTo_var;
    int nodeColor_var;
    int timestamp_var;
    HoneyCombKey senderKey_var;
    HoneyCombKey destKey_var;
    HoneyCombKey lastHop_var;
    HoneyCombKey bootstrapKey_var;
    HoneyCombKey propKey_var;
    int numRing_var;

  private:
    void copy(const P2PMessageCall& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const P2PMessageCall&);

  public:
    P2PMessageCall(const char *name=NULL, int kind=0);
    P2PMessageCall(const P2PMessageCall& other);
    virtual ~P2PMessageCall();
    P2PMessageCall& operator=(const P2PMessageCall& other);
    virtual P2PMessageCall *dup() const {return new P2PMessageCall(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getMsgType() const;
    virtual void setMsgType(int msgType);
    virtual int getRspTo() const;
    virtual void setRspTo(int rspTo);
    virtual int getNodeColor() const;
    virtual void setNodeColor(int nodeColor);
    virtual int getTimestamp() const;
    virtual void setTimestamp(int timestamp);
    virtual HoneyCombKey& getSenderKey();
    virtual const HoneyCombKey& getSenderKey() const {return const_cast<P2PMessageCall*>(this)->getSenderKey();}
    virtual void setSenderKey(const HoneyCombKey& senderKey);
    virtual HoneyCombKey& getDestKey();
    virtual const HoneyCombKey& getDestKey() const {return const_cast<P2PMessageCall*>(this)->getDestKey();}
    virtual void setDestKey(const HoneyCombKey& destKey);
    virtual HoneyCombKey& getLastHop();
    virtual const HoneyCombKey& getLastHop() const {return const_cast<P2PMessageCall*>(this)->getLastHop();}
    virtual void setLastHop(const HoneyCombKey& lastHop);
    virtual HoneyCombKey& getBootstrapKey();
    virtual const HoneyCombKey& getBootstrapKey() const {return const_cast<P2PMessageCall*>(this)->getBootstrapKey();}
    virtual void setBootstrapKey(const HoneyCombKey& bootstrapKey);
    virtual HoneyCombKey& getPropKey();
    virtual const HoneyCombKey& getPropKey() const {return const_cast<P2PMessageCall*>(this)->getPropKey();}
    virtual void setPropKey(const HoneyCombKey& propKey);
    virtual int getNumRing() const;
    virtual void setNumRing(int numRing);
};

inline void doPacking(cCommBuffer *b, P2PMessageCall& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, P2PMessageCall& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * packet P2PMessageResponse extends BaseResponseMessage 
 * {
 * 	int msgType enum (MessageType);
 * 	int nodeColor enum (NodeColor);
 * 	TransportAddress senderAddress;
 * 	OverlayKey senderKey;
 * 	OverlayKey propKey;
 * 	int propX;
 * 	int propY;
 * 	int propZ;
 * };
 * </pre>
 */
class P2PMessageResponse : public ::BaseResponseMessage
{
  protected:
    int msgType_var;
    int nodeColor_var;
    TransportAddress senderAddress_var;
    OverlayKey senderKey_var;
    OverlayKey propKey_var;
    int propX_var;
    int propY_var;
    int propZ_var;

  private:
    void copy(const P2PMessageResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const P2PMessageResponse&);

  public:
    P2PMessageResponse(const char *name=NULL, int kind=0);
    P2PMessageResponse(const P2PMessageResponse& other);
    virtual ~P2PMessageResponse();
    P2PMessageResponse& operator=(const P2PMessageResponse& other);
    virtual P2PMessageResponse *dup() const {return new P2PMessageResponse(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getMsgType() const;
    virtual void setMsgType(int msgType);
    virtual int getNodeColor() const;
    virtual void setNodeColor(int nodeColor);
    virtual TransportAddress& getSenderAddress();
    virtual const TransportAddress& getSenderAddress() const {return const_cast<P2PMessageResponse*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const TransportAddress& senderAddress);
    virtual OverlayKey& getSenderKey();
    virtual const OverlayKey& getSenderKey() const {return const_cast<P2PMessageResponse*>(this)->getSenderKey();}
    virtual void setSenderKey(const OverlayKey& senderKey);
    virtual OverlayKey& getPropKey();
    virtual const OverlayKey& getPropKey() const {return const_cast<P2PMessageResponse*>(this)->getPropKey();}
    virtual void setPropKey(const OverlayKey& propKey);
    virtual int getPropX() const;
    virtual void setPropX(int propX);
    virtual int getPropY() const;
    virtual void setPropY(int propY);
    virtual int getPropZ() const;
    virtual void setPropZ(int propZ);
};

inline void doPacking(cCommBuffer *b, P2PMessageResponse& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, P2PMessageResponse& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>overlay/myoverlay/MyOverlay.msg</tt> by opp_msgc.
 * <pre>
 * packet MyNeighborResponse extends BaseResponseMessage
 * {
 *     NodeHandle respondingNode;
 *     NodeHandle prevNeighbor;
 *     NodeHandle nextNeighbor;
 * };
 * </pre>
 */
class MyNeighborResponse : public ::BaseResponseMessage
{
  protected:
    NodeHandle respondingNode_var;
    NodeHandle prevNeighbor_var;
    NodeHandle nextNeighbor_var;

  private:
    void copy(const MyNeighborResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MyNeighborResponse&);

  public:
    MyNeighborResponse(const char *name=NULL, int kind=0);
    MyNeighborResponse(const MyNeighborResponse& other);
    virtual ~MyNeighborResponse();
    MyNeighborResponse& operator=(const MyNeighborResponse& other);
    virtual MyNeighborResponse *dup() const {return new MyNeighborResponse(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual NodeHandle& getRespondingNode();
    virtual const NodeHandle& getRespondingNode() const {return const_cast<MyNeighborResponse*>(this)->getRespondingNode();}
    virtual void setRespondingNode(const NodeHandle& respondingNode);
    virtual NodeHandle& getPrevNeighbor();
    virtual const NodeHandle& getPrevNeighbor() const {return const_cast<MyNeighborResponse*>(this)->getPrevNeighbor();}
    virtual void setPrevNeighbor(const NodeHandle& prevNeighbor);
    virtual NodeHandle& getNextNeighbor();
    virtual const NodeHandle& getNextNeighbor() const {return const_cast<MyNeighborResponse*>(this)->getNextNeighbor();}
    virtual void setNextNeighbor(const NodeHandle& nextNeighbor);
};

inline void doPacking(cCommBuffer *b, MyNeighborResponse& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MyNeighborResponse& obj) {obj.parsimUnpack(b);}


#endif // _MYOVERLAY_M_H_
