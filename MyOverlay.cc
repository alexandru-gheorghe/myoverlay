// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @author Antonio Zea
 */

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


// Important! This line must be present for each module you extend (see BaseApp)
Define_Module(MyOverlay);

// To convert between IP addresses (which have bit 24 active), and keys (which don't), we'll need to set or remove this bit.
#define BIGBIT (1 << 24)


// Called when the module is being initialized
void MyOverlay::initializeOverlay(int stage)
{
    // see BaseApp.cc
    if (stage != MIN_STAGE_OVERLAY) return;

    // get our key from our IP address
    myKey = thisNode.getIp().get4().getInt() & ~BIGBIT;

    // initialize the rest of variables
    numDropped = 0;
    if (!(par("enableDrops"))) {
        dropChance = 0;
    } else {
        dropChance = par("dropChance");
    }
    OverlayKey unspKey;
    thisNode.setKey(unspKey);

    xNode = NodeHandle::UNSPECIFIED_NODE;
    yNode = NodeHandle::UNSPECIFIED_NODE;
    zNode = NodeHandle::UNSPECIFIED_NODE;
    numRing = 1;

    rpcTimer = new cMessage("RPC timer");
    scheduleAt(simTime() + 5, rpcTimer);
}

// Called to set our own overlay key (optional)
void MyOverlay::setOwnNodeID()
{
    // create the corresponding overlay key

    thisNode.setKey(generateKey(xKey, yKey, zKey));

}



// Called when the module is ready to join the overlay
void MyOverlay::joinOverlay()
{
    // Set the information of the previous step in the chain
    /*
    prevNode.setIp(IPAddress(BIGBIT | (myKey - 1)));
    prevNode.setPort(thisNode.getPort());
    prevNode.setKey(OverlayKey(myKey - 1));
    // Set the information of the next step in the chain
    nextNode.setIp(IPAddress(BIGBIT | (myKey + 1)));
    nextNode.setPort(thisNode.getPort());
    nextNode.setKey(OverlayKey(myKey + 1));
    */
    this->globalNodeList-
    bootstrapNode = this->globalNodeList->getBootstrapNode(this->overlayId, NodeHandle::UNSPECIFIED_NODE);

    /* this means is the first node from overlay */
    if(bootstrapNode.isUnspecified()) {
        addFirstNode();
    } else {
        sendJoinMessage();
    }
    // tell the simulator that we're ready
    setOverlayReady(true);
}

void MyOverlay::addFirstNode() {
    // first node in the network has the key = (1, 0, 0)
    // and it is a black node;
    xKey = X_UNIT;
    yKey = 0;
    zKey = 0;
    nodeColor = BLACK_NODE;
    setOwnNodeID();
}

void MyOverlay::sendJoinMessage() {
    P2PMessageCall *msg = new P2PMessageCall();
    msg->setMsgType(MSG_JOIN);
    msg->setNodeColor(UNKNOWN_COLOR);

    TransportAddress nodeAddress( thisNode.getIp(),
                                  thisNode.getPort(),
                                  thisNode.getNatType());
    //msg->setSenderAddress(nodeAddress);
    //msg->setSenderKey(thisNode.getKey());
    sendRouteRpcCall(OVERLAY_COMP, bootstrapNode, msg);

}
void MyOverlay::sendMessage(HoneyCombKey key, P2PMessageCall *msg) {
    sendRouteRpcCall(OVERLAY_COMP, key, msg);
}

void MyOverlay::sendMessage(NodeHandle node, P2PMessageCall *msg) {
    //sendRouteRpcCall(OVERLAY_COMP, node, msg);
    sendRouteRpcCall(OVERLAY_COMP, node, msg);
}
void MyOverlay::handleTimerEvent(cMessage *msg)
{
    if (msg == rpcTimer) {
        // reschedule the timer
        scheduleAt(simTime() + 5, rpcTimer);

        // if the simulator is still busy creating the network, let's wait a bit longer
        if (underlayConfigurator->isInInitPhase()) return;

        // pick either or next neighbor, or our previous neighbor, and request their neighbors
        OverlayKey key;
        int neighborToAsk = intuniform(0, 1);

        if (neighborToAsk == 0) key = prevNode.getKey();
        else key = nextNode.getKey();

        getNeighbors(key);
    }
}

// Return whether the given node is responsible for the key
bool MyOverlay::isSiblingFor(const NodeHandle& node,
                             const OverlayKey& key,
                             int numSiblings,
                             bool* err)
{
    // is it our node and our key?
    if (node == thisNode && key == thisNode.getKey()) {
        return true;
    }
    // we don't know otherwise
    return false;
}

// Return the next step for the routing of the given message
NodeVector *MyOverlay::findNode(const OverlayKey& key,
                                int numRedundantNodes,
                                int numSiblings,
                                BaseOverlayMessage* msg)
{
    NodeVector* nextHops;

    // do we drop the packet?
    if (uniform(0, 1) < dropChance) {
        // if yes, return an empty node vector
        nextHops = new NodeVector(0);
        numDropped++;
        return nextHops;
    }

    // else, set the response vector with one node
    nextHops = new NodeVector(1);

    // are we responsible? next step is this node
    if (key == thisNode.getKey()) {
        nextHops->add(thisNode);
    }
    // is the key behind us? next step is the previous node
    else if (key < thisNode.getKey()) {
        nextHops->add(prevNode);
    }
    // otherwise, the next step is the next node
    else {
        nextHops->add(nextNode);
    }
    return nextHops;
}

// Called when the module is about to be destroyed
void MyOverlay::finishOverlay()
{
    // remove this node from the overlay
    setOverlayReady(false);

    // save the statistics (see BaseApp)
    globalStatistics->addStdDev("MyOverlay: Dropped packets", numDropped);
}

// Return the max amount of siblings that can be queried about
int MyOverlay::getMaxNumSiblings()
{
    return 1;
}

// Return the max amount of redundant that can be queried about
int MyOverlay::getMaxNumRedundantNodes()
{
    return 1;
}


void MyOverlay::getNeighbors(const OverlayKey &neighborKey)
{
    MyNeighborCall *msg = new MyNeighborCall();
    msg->setDestinationKey(neighborKey);

    // The function we'll be using to send an RPC is sendRouteRpcCall.
    // The first value is to which tier we'll be talking. Can be either
    // OVERLAY_COMP, TIER1_COMP, TIER2_COMP, and so on.
    // The second parameter is the node to which we'll send the message.
    // Can be either an OverlayKey or a TransportAddress.
    // The third parameter is the message.

    EV << thisNode << ": (RPC) Sending query to "
       << neighborKey << "!" << std::endl;

    sendRouteRpcCall(OVERLAY_COMP, neighborKey, msg);
}

// Handle an incoming Call message
// Only delete msg if the RPC is handled here, and you won't respond using sendRpcResponse!
bool MyOverlay::handleRpcCall(BaseCallMessage *msg)
{
    // There are many macros to simplify the handling of RPCs. The full list is in <OverSim>/src/common/RpcMacros.h.

    // start a switch
    RPC_SWITCH_START(msg);

    // enters the following block if the message is of type MyNeighborCall (note the shortened parameter!)
    RPC_ON_CALL(P2PMessage) {
        // get Call message
        P2PMessageCall *p2pmc = (P2PMessageCall*)msg;
        P2PMessageResponse *p2pmr = createJoinResponse(p2pmc);
        sendRpcResponse(p2pmc, p2pmr);

        RPC_HANDLED = true;  // set to true, since we did handle this RPC (default is false)
    }

    // end the switch
    RPC_SWITCH_END();

    // return whether we handled the message or not.
    // don't delete unhandled messages!
    return RPC_HANDLED;
}

// Called when an RPC we sent has timed out.
// Don't delete msg here!
/*
P2PMessageResponse* MyOverlay::createJoinResponse(P2PMessageCall *p2pmc) {
    P2PMessageResponse *p2pmr = new P2PMessageResponse();
    p2pmr->setMsgType(MSG_JOIN_ACCEPT);
    if(nodeColor == BLACK_NODE)
        p2pmr->setNodeColor(WHITE_NODE);
    else if (nodeColor == WHITE_NODE)
            p2pmr->setNodeColor(BLACK_NODE);
         else   p2pmr->setNodeColor(UNKNOWN_COLOR);

    TransportAddress senderAddr(thisNode.getIp(),
                                thisNode.getPort(),
                                thisNode.getNatType());
    p2pmr->setSenderAddress(senderAddr);
    p2pmr->setSenderKey(thisNode.getKey());
    int x;
    int y;
    int z;
    if(getAvailableKey(x, y, z) != KEY_ERROR) {
        p2pmr->setPropKey(generateKey(x, y, z));
        p2pmr->setPropX(x);
        p2pmr->setPropY(y);
        p2pmr->setPropZ(z);
    } else {
        p2pmr->setPropKey(OverlayKey::UNSPECIFIED_KEY);
        p2pmr->setPropX(0);
        p2pmr->setPropY(0);
        p2pmr->setPropZ(0);
    }
    return p2pmr;
}
*/


void MyOverlay::handleRpcTimeout(BaseCallMessage* msg,
                         const TransportAddress& dest,
                         cPolymorphic* context, int rpcId,
                         const OverlayKey&)
{
    // Same macros as in handleRpc

    // start a switch
    RPC_SWITCH_START(msg);

    // enters the following block if the message is of type MyNeighborCall (note the shortened parameter!)
    RPC_ON_CALL(MyNeighbor) {
        MyNeighborCall *mrpc = (MyNeighborCall*)msg;          // get Call message
        callbackTimeout(mrpc->getDestinationKey());           // call interface function
    }
    // end the switch
    RPC_SWITCH_END();
}

// Called when we receive an RPC response from another node.
// Don't delete msg here!

void MyOverlay::handleRpcResponse(BaseResponseMessage* msg,
                                  cPolymorphic* context,
                                  int rpcId,
                                  simtime_t rtt)
{
    // The macros are here similar. Just use RPC_ON_RESPONSE instead of RPC_ON_CALL.

    // start a switch
    RPC_SWITCH_START(msg);

    // enters the following block if the message is of type MyNeighborCall (note the shortened parameter!)
    RPC_ON_RESPONSE(P2PMessage) {
        // get Response message
        P2PMessageResponse *p2pmr = (P2PMessageResponse*)msg;
        // call our interface function
        if( !p2pmr->getPropKey().isUnspecified() ) {
            //parseKey(p2pmr->getPropKey(), xKey, yKey, zKey);
            xKey = p2pmr->getPropX();
            yKey = p2pmr->getPropY();
            zKey = p2pmr->getPropZ();
            setOwnNodeID();
        }
    }
    // end the switch
    RPC_SWITCH_END();
}

void MyOverlay::callbackNeighbors(const NodeHandle& neighborKey,
                                  const NodeHandle& prevNeighbor,
                                  const NodeHandle& nextNeighbor)
{
    EV << thisNode << ": (RPC) Got response from "
       << neighborKey << "\n"
       << thisNode << ": (RPC) Neighbors: "
       << prevNeighbor.getIp() << ", "
       << nextNeighbor.getIp() << std::endl;
}

void MyOverlay::callbackTimeout(const OverlayKey &neighborKey)
{
    EV << thisNode << ": (RPC) Query to " << neighborKey
       << " timed out!" << std::endl;
}
