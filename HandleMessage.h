/*
 * HandleMessage.h
 *
 *  Created on: Jun 4, 2013
 *      Author: alex
 */
#include <queue>
#include "MyOverlay.h"
#include "MyOverlay_m.h"
#include "OverlayInfo.h"
#ifndef HANDLEMESSAGE_H_
#define HANDLEMESSAGE_H_

#define    STAGE_JOINING  1
#define    STAGE_WAIT_MESSAGE  2
#define    STAGE_WAIT_KEY_RESERVED_RPY  3
#define    STAGE_WAIT_FIND_KEY_RPY  4

class HandleMessage {
private:
    MyOverlay *node;
    std::queue<P2PMessageCall *> msgQueue;
    std::vector<int> resMessages;
    int numResWait;
    std::vector<P2PMessageCall*> routMessages;
    std::vector<P2PMessageCall*> findMessages;
    int stage;
    HoneyCombKey reservedKey;
    P2PMessageCall *currJoinMessage;
public:
    HandleMessage(MyOverlay *node);

    void addKeyReservedAck();
    void addKeyReservedDecline();
    void addMessageRouted(P2PMessageCall *msgCall);
    void addFindAvaiKey(P2PMessageCall *msgCall);
    bool alreadyReceivedFindAvaiKey(P2PMessageCall *msgCall);
    bool alreadyRoutedMessage(P2PMessageCall *msgCall);
    bool allNeighResponded();
    bool allNeighRespondedAck();

    void handleMessageCall(P2PMessageCall *msgCall);
    void handleJoin(P2PMessageCall *msgCall);
    void handleJoined(P2PMessageCall *msgCall);
    void handleWelcome(P2PMessageCall *msgCall);
    void handleJoinAccept(P2PMessageCall *msgCall);
    void handleJoinDecline(P2PMessageCall *msgCall);
    void handleKeyReserved(P2PMessageCall *msgCall);
    void handleKeyReservedAck(P2PMessageCall *msgCall);
    void handleKeyReservedDecline(P2PMessageCall *msgCall);
    void handleUnkownHost(P2PMessageCall *msgCall);
    void handleFindAvaiKey(P2PMessageCall *msgCall);
    void handleAvaiKey(P2PMessageCall *msgCall);
    void handleNextChain(P2PMessageCall *msgCall);
    void handleMessageResponse(P2PMessageResponse *msgResponse);
    void handleNextJoinMessage();

    void sendKeyReserved(HoneyCombKey key);
    void sendKeyReservedDecline(P2PMessageCall *msgCall);
    void sendKeyReservedAccept(P2PMessageCall *msgCall);
    void sendJoinDecline(HoneyCombKey neighKey);
    void sendJoinAccept();
    void sendFindAvaiKey(OverlayInfo *neigh);
    void sendAvaiKey(P2PMessageCall *msgCall, HoneyCombKey key);
    void sendJoin(HoneyCombKey key);
    void sendDiscoverNeighbours();
    void sendNextChain(HoneyCombKey key);
    void sendAvaiKeyToNextNode(P2PMessageCall *msgCall);
    void sendMessage(HoneyCombKey destKey, P2PMessageCall *msgCall);
    void sendMessageAsResponse(P2PMessageCall *origMsg, P2PMessageCall *resp);

    NodeHandle* routeMsg(P2PMessageCall *msgCall);
    virtual ~HandleMessage();
};

#endif /* HANDLEMESSAGE_H_ */
