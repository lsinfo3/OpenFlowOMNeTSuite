//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef LINKREMOVERMODULE_H_
#define LINKREMOVERMODULE_H_

#include <omnetpp.h>
#include "OF_Switch.h"

class LinkRemoverModule : public cSimpleModule
{
    public:
		virtual void finish();
		int intRemoved;
		int numNodes;

    struct NodeInfo {
            NodeInfo() {isInTree=false;isProcessed=false;}
            bool isInTree;
            bool isProcessed;
            int moduleID;
            std::vector<int> ports;
            std::vector<int> treeNeighbors;
        };

        typedef std::vector<NodeInfo> NodeInfoVector;
        cTopology topo_spanntree;
        NodeInfoVector nodeInfo;

        virtual int numInitStages() const  {return 5;}
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);
};


#endif /* LINKREMOVERMODULE_H_ */

