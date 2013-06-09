/*
 * OverlayInfo.h
 *
 *  Created on: Jun 5, 2013
 *      Author: alex
 */

#ifndef OVERLAYINFO_H_
#define OVERLAYINFO_H_

#include "BaseOverlay.h"
#include "MyOverlay_m.h"
#include "HoneyCombKey.h"
#include <vector>

#define MAX_NEIGH   3

class OverlayInfo {
public:
    NodeHandle nodeHandle;
    NodeHandle bootstrapNode;
    int nodeColor;
    HoneyCombKey key;
    int numRing;
    OverlayInfo *xNeigh;
    OverlayInfo *yNeigh;
    OverlayInfo *zNeigh;
public:
    OverlayInfo();
    int sign(int x);
    void addNewNode(HoneyCombKey key);
    OverlayInfo* getDiffChainNeighbour();
    std::vector<OverlayInfo *> getSameChainNeighbours();
    std::vector<HoneyCombKey> getNeighOfKey();
    std::vector<HoneyCombKey> getNeighOfKey(HoneyCombKey key);
    std::vector<HoneyCombKey> getNeighOfKey(HoneyCombKey key, NodeColor nodeColor);
    OverlayInfo* getExtNeigh();
    int getAvailableKey(int &x, int &y, int &z);
    int getAvailableKey(HoneyCombKey &key);
    bool isOnLastChain();
    int getNumNeigh();
    void setOverlayKey(HoneyCombKey key);
    bool isKeyTaken(int xKey, int yKey, int zKey);
    bool isKeyTaken(HoneyCombKey key);
    bool hasTheSameKey(int xKey, int yKey, int zKey);
    bool hasTheSameKey(HoneyCombKey key);
    NodeColor getNeighbourColor();
    virtual ~OverlayInfo();
};

#endif /* OVERLAYINFO_H_ */
