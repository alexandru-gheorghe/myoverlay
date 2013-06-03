//
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

// @author Antonio Zea

cplusplus {{
#include <NodeHandle.h>
#include <OverlayKey.h>
#include <CommonMessages_m.h>
#include <TransportAddress.h>
}}
class noncobject NodeHandle;
class noncobject OverlayKey;
class noncobject TransportAddress;

class BaseCallMessage;
class BaseResponseMessage;

packet MyNeighborCall extends BaseCallMessage
{
    OverlayKey destinationKey;
};

enum MessageType 
{
	MSG_JOIN = 1;
	MSG_JOIN_ACCEPT  = 2;
	MSG_JOIN_DECLINE = 3;
	MSG_KEY_RESERVED = 4;
	MSG_KEY_RESERVED_ACK = 5;
	MSG_KEY_RESERVED_DECLINE = 6;
	MSG_UNKNOWN_HOST = 7;
	MSG_FIND_AVAI_KEY = 8;
	MSG_AVAI_KEY = 9;
}
enum NodeColor 
{
	WHITE_NODE = 1;
	BLACK_NODE = 2;
	UNKNOWN_COLOR = 3;
}

packet P2PMessageCall extends BaseCallMessage 
{
	int msgType enum (MessageType);
	int nodeColor enum (NodeColor);
	TransportAddress senderAddress;
	OverlayKey senderKey;
	OverlayKey propKey;
	int propX;
	int propY;
	int propZ;
};

packet P2PMessageResponse extends BaseResponseMessage 
{
	int msgType enum (MessageType);
	int nodeColor enum (NodeColor);
	TransportAddress senderAddress;
	OverlayKey senderKey;
	OverlayKey propKey;
	int propX;
	int propY;
	int propZ;
};
packet MyNeighborResponse extends BaseResponseMessage
{
    NodeHandle respondingNode;
    NodeHandle prevNeighbor;
    NodeHandle nextNeighbor;
};

