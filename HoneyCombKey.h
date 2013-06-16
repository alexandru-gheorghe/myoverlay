/*
 * HoneyCombKey.h
 *
 *  Created on: Jun 8, 2013
 *      Author: alex
 */

#ifndef HONEYCOMBKEY_H_
#define HONEYCOMBKEY_H_
#include <stdint.h>
#include "OverlayKey.h"

class HoneyCombKey: public OverlayKey {
public:
    int xKey;
    int yKey;
    int zKey;
    HoneyCombKey();
    HoneyCombKey(const unsigned char *buffer, uint32_t size);
    HoneyCombKey(const HoneyCombKey &oldKey);
    int getMaxKey();
    int getMinKey();
    int getDist();
    int compareTo(HoneyCombKey key);
    bool isTheSameKey(int xKey, int yKey, int zKey);
    bool isTheSameKey(HoneyCombKey key);
    bool isInteriorToChain(int numRing);
    bool isXNeigh(HoneyCombKey key);
    bool isYNeigh(HoneyCombKey key);
    bool isZNeigh(HoneyCombKey key);
    virtual HoneyCombKey& operator= ( const HoneyCombKey& rhs );
    virtual OverlayKey& operator= ( const OverlayKey& rhs );
    virtual ~HoneyCombKey();
};

HoneyCombKey generateKey(int xKey, int yKey, int zKey);
int parseKey(OverlayKey key, int &x, int &y, int &z);
#endif /* HONEYCOMBKEY_H_ */
