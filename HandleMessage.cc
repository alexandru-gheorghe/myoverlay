/*
 * HandleMessage.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: alex
 */

#include "HandleMessage.h"
#include "MyOverlay.h"
#include "MyOverlay_m.h"
namespace oversim {

HandleMessage::HandleMessage(MyOverlay *node) {
    // TODO Auto-generated constructor stub
    this->node = node;
}
void HandleMessage::handleMessageCall(P2PMessageCall *msgCall) {
    if(msgCall->getMsgType() == MSG_JOIN)
        handleJoin(msgCall);
    if(msgCall->getMsgType() == MSG_JOIN_ACCEPT)
        handleJoinAccept(msgCall);
    if(msgCall->getMsgType() == MSG_JOIN_DECLINE)
        handleJoinDecline(msgCall);
    if(msgCall->getMsgType() == MSG_KEY_RESERVED)
        handleKeyReserved(msgCall);
    if(msgCall->getMsgType() == MSG_KEY_RESERVED_ACK)
        handleKeyReservedAck(msgCall);
    if(msgCall->getMsgType() == MSG_KEY_RESERVED_DECLINE)
        handleKeyReservedDecline(msgCall);
    if(msgCall->getMsgType() == MSG_UNKNOWN_HOST)
        handleUnkownHost(msgCall);
    if(msgCall->getMsgType() == MSG_FIND_AVAI_KEY)
        handleFindAvaiKey(msgCall);
    if(msgCall->getMsgType() == MSG_AVAI_KEY)
        handleAvaiKey(msgCall);
    if(msgCall->getMsgType() == MSG_NEXT_CHAIN)
        handleNextChain(msgCall);
}
HandleMessage::~HandleMessage() {
    // TODO Auto-generated destructor stub
}

} /* namespace oversim */
