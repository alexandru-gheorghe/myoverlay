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
    stage = STAGE_WAIT_MESSAGE;
}
void HandleMessage::handleMessageCall(P2PMessageCall *msgCall) {
    /*
    if(!node->nodeInfo.hasTheSameKey(msgCall->getDestKey())) {
           routeMsg(msgCall);
           return;
    }
    */
    if(msgCall->getMsgType() == MSG_JOIN)
        handleJoin(msgCall);
    if(msgCall->getMsgType() == MSG_JOINED)
        handleJoined(msgCall);
    if(msgCall->getMsgType() == MSG_JOIN_ACCEPT)
        handleJoinAccept(msgCall);
    if(msgCall->getMsgType() == MSG_WELCOME)
        handleWelcome(msgCall);
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
    HoneyCombKey key;
    if(stage != STAGE_WAIT_MESSAGE) {
        msgQueue.push(msgCall);
        return;
    }
    currJoinMessage = msgCall;
    int result = node->nodeInfo.getAvailableKey(key);
    stage = STAGE_JOINING;
    if(result != KEY_ERROR) {
        sendKeyReserved(key);
    } else {
        if(!node->nodeInfo.isOnLastChain()) {
            sendJoinDecline(node->nodeInfo.getExtNeigh()->nodeHandle);
        } else {
            std::vector<OverlayInfo *> neighs = node->nodeInfo.getSameChainNeighbours();
            for(unsigned int i = 0; i < neighs.size(); i++)
                sendFindAvaiKey(neighs[i]);
        }
    }

}

void HandleMessage::handleJoined(P2PMessageCall *msgCall) {
    node->nodeInfo.addNeigh(msgCall->getSenderKey(), msgCall->getSrcNode());
    P2PMessageCall *rsp = new P2PMessageCall();
    rsp->setMsgType(MSG_WELCOME);
    rsp->setDestKey(msgCall->getSenderKey());
    sendMessageAsResponse(msgCall, rsp);
}
void HandleMessage::handleJoinDecline(P2PMessageCall *msgCall) {
    sendJoin(msgCall->getBootstrapNode());
}

void HandleMessage::handleWelcome(P2PMessageCall *msgCall) {
    node->nodeInfo.addNeigh(msgCall->getSenderKey(), msgCall->getSrcNode());
}
void HandleMessage::handleJoinAccept(P2PMessageCall *msgCall) {
    node->nodeInfo.setOverlayKey(msgCall->getPropKey());
    node->nodeInfo.nodeColor = msgCall->getNodeColor();
    node->nodeInfo.numRing = msgCall->getNumRing();
    sendDiscoverNeighbours();
    node->setReady(true);
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
        if(allNeighRespondedAck()) {
            sendJoinAccept();
        }
       else {
            stage =  STAGE_WAIT_MESSAGE;
            handleJoin(currJoinMessage);
        }
        resMessages.clear();
    }
}

void HandleMessage::handleUnkownHost(P2PMessageCall *msgCall) {
    if(msgCall->getRspTo() == MSG_KEY_RESERVED)
        handleKeyReservedAck(msgCall);
}

void HandleMessage::handleKeyReservedDecline(P2PMessageCall *msgCall) {
    addKeyReservedDecline();
    if(allNeighResponded()) {
        stage =  STAGE_WAIT_MESSAGE;
        handleJoin(currJoinMessage);
    }
}

void HandleMessage::handleFindAvaiKey(P2PMessageCall *msgCall) {
    if(alreadyReceivedFindAvaiKey(msgCall)) {
        node->nodeInfo.numRing ++;
        std::vector<HoneyCombKey> keys = node->nodeInfo.getNeighOfKey();
        for(unsigned int i = 0; i < keys.size(); i++)
            sendNextChain(keys[i]);
    } else {
        HoneyCombKey key;
        if(node->nodeInfo.getAvailableKey(key) != KEY_ERROR) {
            sendAvaiKey(msgCall, key);
        } else {
            addFindAvaiKey(msgCall);
            sendAvaiKeyToNextNode(msgCall);
        }
    }
}

void HandleMessage::handleAvaiKey(P2PMessageCall *msgCall) {
    if(stage ==  STAGE_WAIT_FIND_KEY_RPY) {
        sendJoinDecline(msgCall->getSrcNode());
    }
}

void HandleMessage::handleNextChain(P2PMessageCall *msgCall) {
    if(node->nodeInfo.numRing < msgCall->getNumRing()) {
        node->nodeInfo.numRing = msgCall->getNumRing();
        std::vector<HoneyCombKey> keys = node->nodeInfo.getNeighOfKey();
        for(unsigned int i = 0; i < keys.size(); i++)
            if(!keys[i].isTheSameKey(msgCall->getSenderKey()))
                sendNextChain(keys[i]);
        if(stage ==  STAGE_WAIT_FIND_KEY_RPY) {
            HoneyCombKey key;
            if(node->nodeInfo.getAvailableKey(key) != KEY_ERROR) {
                reservedKey = key;
                sendJoinAccept();
            }
        }
    }
}

void HandleMessage::sendKeyReserved(HoneyCombKey key) {
    numResWait = 0;
    std::vector<HoneyCombKey> neighsOfKey = node->nodeInfo.getNeighOfKey(key);
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setType(MSG_KEY_RESERVED);
    msg->setPropKey(key);
    msg->setSenderKey(node->nodeInfo.key);
    msg->setRspTo(MSG_NONE);
    stage =  STAGE_WAIT_KEY_RESERVED_RPY;
    for(unsigned int i = 0; i < neighsOfKey.size(); i++) {
        sendMessage(neighsOfKey[i], msg);
        numResWait++;
    }
}

void HandleMessage::sendKeyReservedDecline(P2PMessageCall *msgCall) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_KEY_RESERVED_DECLINE);
    msg->setPropKey(msgCall->getPropKey());
    sendMessage(msgCall->getSenderKey(), msg);
}

void HandleMessage::sendKeyReservedAccept(P2PMessageCall *msgCall) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_KEY_RESERVED_ACK);
    msg->setPropKey(msgCall->getPropKey());
    sendMessage(msgCall->getSenderKey(), msg);
}

void HandleMessage::sendJoinDecline(NodeHandle node) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_JOIN_DECLINE);
    msg->setBootstrapNode(node);
    sendMessageAsResponse(currJoinMessage, msg);
    stage =  STAGE_WAIT_MESSAGE;
    handleNextJoinMessage();
}
void HandleMessage::sendJoinAccept() {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_JOIN_ACCEPT);
    msg->setPropKey(reservedKey);
    node->nodeInfo.addNeigh(reservedKey, currJoinMessage->getSrcNode());

    sendMessageAsResponse(currJoinMessage, msg);
    stage =  STAGE_WAIT_MESSAGE;
    handleNextJoinMessage();
}

void HandleMessage::handleNextJoinMessage() {
    P2PMessageCall *msg = msgQueue.front();
    msgQueue.pop();
    handleJoin(msg);
}

void HandleMessage::sendFindAvaiKey(OverlayInfo *neigh) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_FIND_AVAI_KEY);
    stage =  STAGE_WAIT_FIND_KEY_RPY;
    sendMessage(neigh->key, msg);
}

void HandleMessage::sendAvaiKey(P2PMessageCall *msgCall, HoneyCombKey key) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_AVAI_KEY);
    sendMessage(msgCall->getSenderKey(), msg);
}

void HandleMessage::sendJoin(NodeHandle node) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_JOIN);
    sendMessage(node, msg);
}

void HandleMessage::sendDiscoverNeighbours() {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    std::vector<HoneyCombKey> keys = node->nodeInfo.getNeighOfKey();
    msg->setMsgType(MSG_JOINED);
    for(unsigned int i = 0; i < keys.size(); i++) {
        sendMessage(keys[i], msg);
    }
}

void HandleMessage::sendNextChain(HoneyCombKey key) {
    P2PMessageCall *msg;
    msg = new P2PMessageCall();
    msg->setMsgType(MSG_NEXT_CHAIN);
    msg->setNumRing(node->nodeInfo.numRing);
    sendMessage(key, msg);
}

void HandleMessage::sendAvaiKeyToNextNode(P2PMessageCall *msgCall) {
    std::vector<OverlayInfo *> neighs = node->nodeInfo.getSameChainNeighbours();
    for(unsigned int i = 0; i < neighs.size(); i++) {
        if(!neighs[i]->key.isTheSameKey(msgCall->getLastHop())) {
            msgCall->setDestKey(neighs[i]->key);
            routeMsg(msgCall);
        }
    }
}

void HandleMessage::sendMessage(HoneyCombKey dest, P2PMessageCall *msgCall) {
    msgCall->setDestKey(dest);
    msgCall->setSenderKey(node->nodeInfo.key);
    node->sendMessage(dest, msgCall);
}
void HandleMessage::sendMessage(NodeHandle node, P2PMessageCall *msgCall) {
    msgCall->setSenderKey(this->node->nodeInfo.key);
    this->node->sendMessage(node, msgCall);
}

void HandleMessage::sendMessageAsResponse(P2PMessageCall *origMsg, P2PMessageCall *resp) {
    NodeHandle node = origMsg->getSrcNode();
    resp->setSenderKey(this->node->nodeInfo.key);
    this->node->sendMessage(node, resp);

}

NodeHandle* HandleMessage::routeMsg(P2PMessageCall *msgCall) {
    if(alreadyRoutedMessage(msgCall)) {
        P2PMessageCall *msg = new P2PMessageCall();
        msg->setMsgType(MSG_UNKNOWN_HOST);
        msg->setRspTo(msgCall->getMsgType());
        sendMessage(msgCall->getDestKey(), msg);
        return NULL;
    } else {
        addMessageRouted(msgCall);
        OverlayInfo *neighInfo = node->nodeInfo.getNextHop(msgCall->getDestKey());
        NodeHandle *pNode = new NodeHandle();
        *pNode = neighInfo->nodeHandle;
        return pNode;

    }

}

void HandleMessage::addKeyReservedAck() {
    resMessages.push_back(MSG_KEY_RESERVED_ACK);
    numResWait--;
}

void HandleMessage::addKeyReservedDecline() {
    resMessages.push_back(MSG_KEY_RESERVED_DECLINE);
    numResWait--;
}

bool HandleMessage::allNeighRespondedAck() {
    for(int i = 0; i < resMessages.size(); i++)
        if(resMessages[i] != MSG_KEY_RESERVED_ACK)
            return false;
    return true;
}
bool HandleMessage::allNeighResponded() {
    if(numResWait == 0)
        return true;
    return false;
}


void HandleMessage::addFindAvaiKey(P2PMessageCall *msgCall) {
    findMessages.push_back(msgCall);
}

bool HandleMessage::alreadyReceivedFindAvaiKey(P2PMessageCall *msgCall) {
    for(int i = 0; i < findMessages.size(); i++)
        if(findMessages[i]->getSenderKey().isTheSameKey(msgCall->getSenderKey()) &&
            findMessages[i]->getTimestamp() == msgCall->getTimestamp())
            return true;
    return false;
}

void HandleMessage::addMessageRouted(P2PMessageCall *msgCall) {
    routMessages.push_back(msgCall);
}

bool HandleMessage::alreadyRoutedMessage(P2PMessageCall *msgCall) {
    for(int i = 0; i < routMessages.size(); i++)
           if(routMessages[i]->getSenderKey().isTheSameKey(msgCall->getSenderKey()) &&
               routMessages[i]->getTimestamp() == msgCall->getTimestamp())
               return true;
       return false;
}
HandleMessage::~HandleMessage() {
    // TODO Auto-generated destructor stub
}

