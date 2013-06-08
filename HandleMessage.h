/*
 * HandleMessage.h
 *
 *  Created on: Jun 4, 2013
 *      Author: alex
 */
#include <queue>
#include "MyOverlay.h"
#include "MyOverlay_m.h"
#ifndef HANDLEMESSAGE_H_
#define HANDLEMESSAGE_H_

enum STAGE_TYPES {
    STAGE_JOINING,
    STAGE_WAIT_MESSAGE,
    STAGE_WAIT_KEY_RESERVED_RPY,
    STAGE_WAIT_FIND_KEY_RPY
};
class HandleMessage {
private:
    MyOverlay *node;
    std::queue<P2PMessageCall *> msgQueue;
    STAGE_TYPES stage;
    HoneyCombKey reservedKey;
    P2PMessageCall *currJoinMessage;
public:
    HandleMessage(MyOverlay *node);

    void addKeyReservedAck();
    void addKeyReservedDecline();
    bool allNeighResponded();
    bool allNeighRespondedAck();

    void handleMessageCall(P2PMessageCall *msgCall);
    void handleJoin(P2PMessageCall *msgCall);
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

    void sendKeyReserved(int xKey, int yKey, int zKey);
    void sendKeyReservedDecline(P2PMessageCall *msgCall);
    void sendKeyReservedAccept(P2PMessageCall *msgCall);
    void sendJoinDecline(OverlayInfo *neigh);
    void sendJoinAccept();
    void sendFindAvaiKey(OverlayInfo *neigh);
    void sendJoin(OverlayKey key);
    void sendDiscoverNeighbours();
    void routeMsg(P2PMessageCall *msgCall);
    virtual ~HandleMessage();
};

#endif /* HANDLEMESSAGE_H_ */
