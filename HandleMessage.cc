/*
 * HandleMessage.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: alex
 */

#include "HandleMessage.h"
#include "MyOverlay.h"
#include "MyOverlay_m.h"
#include "OverlayInfo.h"

HandleMessage::HandleMessage(MyOverlay *node) {
    // TODO Auto-generated constructor stub
    this->node = node;
}
void HandleMessage::handleMessageCall(P2PMessageCall *msgCall) {
    if(!node->nodeInfo.hasTheSameKey(msgCall->getDestKey())) {
           routeMsg(msgCall);
           return;
    }
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

void HandleMessage::handleJoin(P2PMessageCall *msgCall) {
    int xKey, yKey, zKey;
    if(stage != STAGE_TYPES::STAGE_WAIT_MESSAGE) {
        msgQueue.push(msgCall);
        return;
    }
    currJoinMessage = msgCall;
    int result = node->nodeInfo.getAvailableKey(xKey, yKey, zKey);
    stage = STAGE_TYPES::STAGE_JOINING;
    if(result != KEY_ERROR) {
        sendKeyReserved(xKey, yKey, zKey);
    } else {
        if(!node->nodeInfo.isOnLastChain()) {
            sendJoinDecline(node->nodeInfo.getExtNeigh());
        } else {
            std::vector<OverlayInfo *> neighs = node->nodeInfo.getSameChainNeighbours();
            for(int i = 0; i < neighs.size(); i++)
                sendFindAvaiKey(neighs[i]);
        }
    }

}

void HandleMessage::handleJoinDecline(P2PMessageCall *msgCall) {
    sendJoin(msgCall->getBootstrapKey());
}

void HandleMessage::handleJoinAccept(P2PMessageCall *msgCall) {
    node->nodeInfo.setOverlayKey(msgCall->getPropKey());
    node->nodeInfo.nodeColor = msgCall->getNodeColor();
    node->nodeInfo.numRing = msgCall->getNumRing();
    sendDiscoverNeighbours();
}

void HandleMessage::handleKeyReserved(P2PMessageCall *msgCall) {

    if(node->nodeInfo.isKeyTaken(msgCall->getPropKey()))
        sendKeyReservedDecline(msgCall);
    else
        if(reservedKey.isTheSameKey(msgCall->getPropKey())) {
            if(node->nodeInfo.key.compareTo(msgCall->getSenderKey()) < 0)
                sendKeyReservedAccept(msgCall);
            else
                sendKeyReservedDecline(msgCall);
        }
        else
            sendKeyReservedAccept(msgCall);

}

void HandleMessage::handleKeyReservedAck(P2PMessageCall *msgCall) {
    addKeyReservedAck();
    if(allNeighResponded()) {
        node->nodeInfo.addNewNode(reservedKey);
        if(allNeighRespondedAck())
            sendJoinAccept();
        else {
            stage = STAGE_TYPES::STAGE_WAIT_MESSAGE;
            handleJoin(currJoinMessage);
        }
    }
}

void HandleMessage::handleUnkownHost(P2PMessageCall *msgCall) {
    if(msgCall->getRspTo() == MSG_KEY_RESERVED)
        handleKeyReservedAck(msgCall);
}
void HandleMessage::handleKeyReservedDecline(P2PMessageCall *msgCall) {
    addKeyReservedDecline();
    if(allNeighResponded()) {
        node->nodeInfo.addNewNode(reservedKey);
        stage = STAGE_TYPES::STAGE_WAIT_MESSAGE;
        handleJoin(currJoinMessage);
    }
}

HandleMessage::~HandleMessage() {
    // TODO Auto-generated destructor stub
}

