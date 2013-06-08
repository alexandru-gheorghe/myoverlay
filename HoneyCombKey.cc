/*
 * HoneyCombKey.cc
 *
 *  Created on: Jun 8, 2013
 *      Author: alex
 */

#include "HoneyCombKey.h"
#include "OverlayKey.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#include <UnderlayConfigurator.h>
#include <GlobalStatistics.h>
#include <BootstrapList.h>
#include <GlobalNodeList.h>
#include <vector>
#include "MyOverlay_m.h"

#include "MyOverlay.h"
HoneyCombKey::HoneyCombKey():OverlayKey() {

}
HoneyCombKey::HoneyCombKey(const unsigned char *buffer, uint32_t size)
:OverlayKey(buffer, size) {
    // TODO Auto-generated constructor stub

}
int HoneyCombKey::getMaxKey() {
    if(xKey >= yKey && xKey >= zKey)
        return xKey;
    if(yKey >= xKey && yKey >= zKey)
        return yKey;
    return zKey;
}

int HoneyCombKey::getMinKey() {
    if(xKey <= yKey && xKey <= zKey)
        return xKey;
    if(yKey <= xKey && yKey <= zKey)
        return yKey;
    return zKey;

}

bool HoneyCombKey::isTheSameKey(int xKey, int yKey, int zKey) {
    if(this->xKey == xKey && this->yKey == yKey && this->zKey == zKey)
        return true;
    return false;
}

bool HoneyCombKey::isTheSameKey(HoneyCombKey key) {
    return isTheSameKey(key.xKey, key.yKey, key.zKey);
}

int HoneyCombKey::getDist() {
    return abs(xKey) + abs(yKey) + abs(zKey);
}

int HoneyCombKey::compareTo(HoneyCombKey key) {
    if(xKey > key.xKey)
        return 1;
    if(xKey < key.xKey)
        return -1;
    if(yKey > key.yKey)
        return 1;
    if(yKey < key.yKey)
        return -1;
    if(zKey > key.zKey)
        return 1;
    if(zKey < key.zKey)
        return -1;
    return 0;
}

HoneyCombKey generateKey(int xKey, int yKey, int zKey) {
    unsigned char *buffer;
    buffer = (unsigned char *)malloc(KEY_LENGTH * sizeof(char));
    memcpy(buffer, &xKey, sizeof(int));
    memcpy(buffer + sizeof(int), &yKey, sizeof(int));
    memcpy(buffer + 2 * sizeof(int), &zKey, sizeof(int));
    HoneyCombKey hck = HoneyCombKey(buffer, KEY_LENGTH);
    hck.xKey = xKey;
    hck.yKey = yKey;
    hck.zKey = zKey;
    return hck;
}

int parseKey(OverlayKey key, int &x, int &y, int &z) {
    if(key.isUnspecified())
        return KEY_ERROR;
    x = key.getBitRange(0, sizeof(int));
    y = key.getBitRange(sizeof(int), sizeof(int));
    z = key.getBitRange(2 * sizeof(int), sizeof(int));

    return KEY_SUCCESS;
}
HoneyCombKey::~HoneyCombKey() {
    // TODO Auto-generated destructor stub
}

