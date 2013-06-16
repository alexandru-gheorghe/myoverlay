/*
 * OverlayInfo.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: alex
 */

#include "BaseOverlay.h"
#include "MyOverlay_m.h"
#include "OverlayInfo.h"
#include "HoneyCombKey.h"
#include <vector>
#include <math.h>
#include "OverlayInfo.h"
#include "MyOverlay.h"
#include "MyOverlay_m.h"
#include "HandleMessage.h"

std::vector<OverlayInfo *> OverlayInfo::getSameChainNeighbours() {
    std::vector<OverlayInfo *> nodes;
    if(sign(key.xKey) == sign(key.yKey)) {
        nodes.push_back(xNeigh);
        nodes.push_back(yNeigh);
    }
    if(sign(key.xKey) == sign(key.zKey)) {
        nodes.push_back(xNeigh);
        nodes.push_back(zNeigh);
    }
    if(sign(key.yKey) == sign(key.zKey)) {
        nodes.push_back(yNeigh);
        nodes.push_back(zNeigh);
    }
    return nodes;
}

OverlayInfo* OverlayInfo::getDiffChainNeighbour() {
    if(sign(key.xKey) == sign(key.yKey)) {
        return zNeigh;
    }
    if(sign(key.xKey) == sign(key.zKey)) {
        return zNeigh;
    }
    if(sign(key.yKey) == sign(key.zKey)) {
        return zNeigh;
    }
    return NULL;
}

int OverlayInfo::sign(int x) {
    if(x > 0)   return POZ;
    return NEG;
}

int OverlayInfo::getAvailableKey(int &x, int &y, int &z) {
    if(nodeColor == UNKNOWN_COLOR)
        return KEY_ERROR;
    if(nodeColor == BLACK_NODE) {
        if(key.xKey < numRing && xNeigh == NULL) {
            x = key.xKey + 1;
            y = key.yKey;
            z = key.zKey;
            return X_KEY;
        }
        if(key.yKey < numRing && yNeigh == NULL) {
            x = key.xKey;
            y = key.yKey + 1;
            z = key.zKey;
            return Y_KEY;
        }
        if(key.zKey < numRing && zNeigh == NULL) {
            x = key.xKey;
            y = key.yKey;
            z = key.zKey + 1;
            return Z_KEY;
        }
    }
    if(nodeColor == WHITE_NODE) {
        if(key.xKey > -numRing + 1 && xNeigh == NULL) {
            x = key.xKey - 1;
            y = key.yKey;
            z = key.zKey;
            return X_KEY;
        }
        if(key.yKey > -numRing + 1 && yNeigh == NULL) {
            x = key.xKey;
            y = key.yKey - 1;
            z = key.zKey;
            return Y_KEY;
        }
        if(key.zKey > -numRing + 1 && zNeigh == NULL) {
            x = key.xKey;
            y = key.yKey;
            z = key.zKey -1;
            return Z_KEY;
        }
    }
    return KEY_ERROR;
}

int OverlayInfo::getAvailableKey(HoneyCombKey &key) {
    int x = 0, y = 0, z = 0;
    int res = getAvailableKey(x, y, z);
    key = generateKey(x, y, z);
    return res;
}

NodeColor OverlayInfo::getNeighbourColor() {
    if(nodeColor == BLACK_NODE)
        return WHITE_NODE;
    if(nodeColor == WHITE_NODE)
        return BLACK_NODE;
    return UNKNOWN_COLOR;
}

bool OverlayInfo::isOnLastChain() {
    /*
    if(getMaxKey() == numRing)
        return true;
    if(getMinKey() - 1 == -numRing)
        return true;
    */
    int x, y, z;
    return (getNumNeigh() != MAX_NEIGH) && (getAvailableKey(x, y, z) == KEY_ERROR);
}



int OverlayInfo::getNumNeigh() {
    int numNeigh = 0;
    if(xNeigh != NULL)
        numNeigh++;
    if(yNeigh != NULL)
        numNeigh++;
    if(yNeigh != NULL)
        numNeigh++;
    return numNeigh;
}
OverlayInfo* OverlayInfo::getExtNeigh() {
    int xDist = 0, yDist = 0, zDist = 0;
    if(xNeigh)
        xDist = xNeigh->key.getDist();
    if(yNeigh)
        yDist = yNeigh->key.getDist();
    if(zNeigh)
        zDist = zNeigh->key.getDist();
    if(xDist >= yDist && xDist >= zDist)
        return xNeigh;
    if(yDist >= xDist && yDist >= zDist)
        return yNeigh;
    if(zDist >= xDist && zDist >= yDist)
        return zNeigh;
    return NULL;
}

void OverlayInfo::setOverlayKey(HoneyCombKey key) {
    this->key = generateKey(key.xKey, key.yKey, key.zKey);
}

OverlayInfo::OverlayInfo() {
    nodeHandle = NodeHandle::UNSPECIFIED_NODE;
    nodeColor = UNKNOWN_COLOR;
    xNeigh = NULL;
    yNeigh = NULL;
    zNeigh = NULL;
    // TODO Auto-generated constructor stub
}

bool OverlayInfo::hasTheSameKey(int xKey, int yKey, int zKey) {
    return key.isTheSameKey(xKey, yKey, zKey);
}

bool OverlayInfo::hasTheSameKey(HoneyCombKey key) {
    return hasTheSameKey(key.xKey, key.yKey, key.zKey);
}

bool OverlayInfo::isKeyTaken(int xKey, int yKey, int zKey) {
    if(xNeigh && xNeigh->hasTheSameKey(xKey, yKey, zKey))
        return true;
    if(yNeigh && yNeigh->hasTheSameKey(xKey, yKey, zKey))
        return true;
    if(zNeigh && zNeigh->hasTheSameKey(xKey, yKey, zKey))
        return true;
    return false;
}

bool OverlayInfo::isKeyTaken(HoneyCombKey key) {
    return isKeyTaken(key.xKey, key.yKey, key.zKey);
}

std::vector<HoneyCombKey> OverlayInfo::getNeighOfKey() {
    return getNeighOfKey(key, (NodeColor)nodeColor);
}
std::vector<HoneyCombKey> OverlayInfo::getNeighOfKey(HoneyCombKey key) {
    if(nodeColor == WHITE_NODE)
        return getNeighOfKey(key, BLACK_NODE);
    if(nodeColor == BLACK_NODE)
        return getNeighOfKey(key, WHITE_NODE);
    return getNeighOfKey(key, UNKNOWN_COLOR);
}

std::vector<HoneyCombKey> OverlayInfo::getNeighOfKey(HoneyCombKey key, NodeColor nodeColor) {
    std::vector<HoneyCombKey> keys;
    HoneyCombKey genKey;
    int sign;
    if(nodeColor == WHITE_NODE)
        sign = -1;
    else {
        if(nodeColor == BLACK_NODE)
            sign = 1;
        else
            sign = 0;
    }

    genKey = generateKey(key.xKey + sign, key.yKey, key.zKey);
    if(!genKey.isTheSameKey(this->key) && genKey.isInteriorToChain(numRing))
        keys.push_back(genKey);

    genKey = generateKey(key.xKey, key.yKey + sign, key.zKey);
    if(!genKey.isTheSameKey(this->key) && genKey.isInteriorToChain(numRing))
        keys.push_back(genKey);

    genKey = generateKey(key.xKey, key.yKey, key.zKey + sign);
    if(!genKey.isTheSameKey(this->key) && genKey.isInteriorToChain(numRing))
        keys.push_back(genKey);

    return keys;
}

OverlayInfo* OverlayInfo::getNextHop(HoneyCombKey key) {
    int xDist = 99999, yDist = 99999, zDist = 99999; // Magic Number
    if(xNeigh == NULL && yNeigh == NULL && zNeigh == NULL)
        return NULL;
    if(xNeigh)
        xDist = xNeigh->key.getDist();
    if(yNeigh)
        yDist = yNeigh->key.getDist();
    if(zNeigh)
        zDist = zNeigh->key.getDist();
    if(xDist <= yDist && xDist <= zDist)
        return xNeigh;
    if(yDist <= xDist && yDist <= zDist)
        return yNeigh;
    if(zDist <= xDist && zDist <= yDist)
        return zNeigh;
    return NULL;
}

void OverlayInfo::addNeigh(HoneyCombKey key, NodeHandle node) {
    OverlayInfo *neigh = new OverlayInfo();
    neigh->nodeColor = getNeighbourColor();
    neigh->nodeHandle = node;
    neigh->numRing = numRing;
    neigh->key = key;
    if(this->key.isXNeigh(key))
        xNeigh = neigh;
    if(this->key.isYNeigh(key))
        yNeigh = neigh;
    if(this->key.isZNeigh(key))
        zNeigh = neigh;
}

void OverlayInfo::addFirstNode() {
    key = generateKey(1, 0, 0);
    this->nodeColor = BLACK_NODE;
    numRing = 1;
}

OverlayInfo::~OverlayInfo() {
    // TODO Auto-generated destructor stub
}

