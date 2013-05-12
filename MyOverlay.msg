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

packet P2PMessage extends BaseCallMessage {
	int type;
	TransportAddress senderAddress;
};
packet MyNeighborResponse extends BaseResponseMessage
{
    NodeHandle respondingNode;
    NodeHandle prevNeighbor;
    NodeHandle nextNeighbor;
};
