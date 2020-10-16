////////////////

//Adjusted for use with LinkRemoverModule

////////////////

#include "StaticSpanningTree.h"
#include <OF_Switch.h>

Define_Module(StaticSpanningTree);

void StaticSpanningTree::initialize(int stage)
{
    EV << "spanningTree stage test!";
    if (stage == 4)
    {
        //map the network in cTopology
        const char *NodeType = par("NodeType");
        int startNode = par("startNode");
        std::vector<std::string> nodeTypes = cStringTokenizer(NodeType).asVector();
        topo_spanntree.extractByNedTypeName(nodeTypes);
        EV << "cTopology found " << topo_spanntree.getNumNodes() << "\n";
        nodeInfo.resize(topo_spanntree.getNumNodes());
        for (int i = 0; i < topo_spanntree.getNumNodes(); i++)
        {
            nodeInfo[i].moduleID = topo_spanntree.getNode(i)->getModuleId();
            nodeInfo[i].treeNeighbors.resize(topo_spanntree.getNumNodes(), 0);
        }

// start node for calculation of spanning tree
        if (startNode < topo_spanntree.getNumNodes())
        {
            nodeInfo[startNode].isInTree = true;
            EV << "Starting at Node: " << topo_spanntree.getNode(startNode)->getModule()->getFullPath() << "\n";
        }
        else
        {
            int tempInt = intrand(topo_spanntree.getNumNodes());
            nodeInfo[tempInt].isInTree = true;
            EV << "Starting at Node: " << topo_spanntree.getNode(tempInt)->getModule()->getFullPath() << "\n";
        }

        int counter = 0;
        while (counter != topo_spanntree.getNumNodes())
        {
            counter = 0;

            for (int i = 0; i < topo_spanntree.getNumNodes(); i++)
            {

                if (nodeInfo[i].isProcessed)
                {
                    counter++;
                }

                if (nodeInfo[i].isInTree && !nodeInfo[i].isProcessed)
                {

//                if (nodeInfo[i].isInTree && !nodeInfo[i].isProcessed) {
                    EV << "Processing node " << topo_spanntree.getNode(i)->getModule()->getName() << " with index " << i << ".\n";
                    nodeInfo[i].isProcessed = true;
                    // for loop over all neighbors
                    for (int j = 0; j < topo_spanntree.getNode(i)->getNumOutLinks(); j++)
                    {
                        //ignore control plane
                        if (strstr(topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL)
                        {
                            continue;
                        }

                        // for loop over all nodes to identify neighbors
                        for (int x = 0; x < topo_spanntree.getNumNodes(); x++)
                        {

                            // test, if node x is neighbor of node i by using moduleID
                            if (nodeInfo[x].moduleID == topo_spanntree.getNode(i)->getLinkOut(j)->getRemoteNode()->getModuleId())
                            {
                                cModule *modTmp1 = topo_spanntree.getNode(i)->getModule()->getSubmodule("OF_Switch");
                                if (topo_spanntree.getNode(i)->getModule()->getSubmodule("OF_Switch") == NULL) {
                                    modTmp1 = topo_spanntree.getNode(i)->getModule()->getSubmodule("open_flow_switch")->getSubmodule("OF_Switch");
                                }
                                OF_Switch *swi1 = check_and_cast<OF_Switch *>(modTmp1);

                                cModule *modTmp2 = topo_spanntree.getNode(x)->getModule()->getSubmodule("OF_Switch");
                                if (topo_spanntree.getNode(i)->getModule()->getSubmodule("OF_Switch") == NULL) {
                                    modTmp2 = topo_spanntree.getNode(x)->getModule()->getSubmodule("open_flow_switch")->getSubmodule("OF_Switch");
                                }
                                OF_Switch *swi2 = check_and_cast<OF_Switch *>(modTmp2);

                                EV << "portVector.state THIS: " << swi1->portVector[j].state << "\nportVector.state OTHER: " << swi2->portVector[j].state << "\n";

                                //node x neighbour but link blocked by linkRemover module
                                if (swi1->portVector[topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex()].state == (OFPPS_BLOCKED | OFPPS_LINK_DOWN) && !nodeInfo[x].isInTree)
                                {
                                    //EV<<"OFPPS_BLOCKED!";
                                    swi1->portVector[topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex()].state = 3;
                                    //EV << "\ni:" << i << "\n";
                                    int otherGateIndex = -1;
                                    for (int k = 0; k < topo_spanntree.getNode(x)->getNumOutLinks(); k++)
                                    {
                                        EV << "\nOTHER candidate: " << topo_spanntree.getNode(x)->getLinkOut(k)->getRemoteGate()->getOwnerModule()->getIndex() << "\n";
                                        if (topo_spanntree.getNode(x)->getLinkOut(k)->getRemoteNode()->getModuleId() == topo_spanntree.getNode(i)->getModuleId())
                                        {
                                            //EV<<"\nk: "<<k<<"\n";
                                            otherGateIndex = topo_spanntree.getNode(x)->getLinkOut(k)->getLocalGate()->getIndex();
                                            EV << "\n[THIS index: " << j << "OTHER index: " << otherGateIndex << "]\n";
                                        }
                                    }

                                    swi2->portVector[otherGateIndex].state = 3;

                                    nodeInfo[i].ports.push_back(topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex());
                                    nodeInfo[x].ports.push_back(otherGateIndex);
                                    /*
                                     nodeInfo[topo_spanntree.getNode(i)->getLinkOut(
                                     j)->getRemoteNode()->getLinkOut(j)->getLocalGate()->getIndex())].ports.push_back(
                                     topo_spanntree.getNode(j)->getLinkOut(
                                     i)->getLocalGate()->getIndex());
                                     */

                                    EV << "Disable link with index " << topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex() << " at node " << i << " to node " << x << "!" << endl;
                                }
                                //node x is neighbour, not removed by remover but not in tree
                                else if (!nodeInfo[x].isInTree)
                                {
                                    // Neighbor is not yet in tree and will be added
                                    nodeInfo[x].isInTree = true;
                                    nodeInfo[x].treeNeighbors[i] = 1;
                                }
                                //node x is neigbour and in tree
                                else
                                {
                                    // Link is already in tree and must not be disabled
                                    if (nodeInfo[i].treeNeighbors[x] == 1)
                                    {
                                        continue;
                                    }
                                    // Neighbor is already in tree, deactivate corresponding link
                                    //EV << "\nSTATE: "<<swi1->portVector[j].state<<"\n";
                                    if (swi1->portVector[topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex()].state != OFPPS_BLOCKED)
                                    {
                                        nodeInfo[i].ports.push_back(topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex());
                                        EV << "Disable link with index " << topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex() << " at node " << i << " to node " << x << "!" << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // disable ports for all nodes
        for (int x = 0; x < topo_spanntree.getNumNodes(); x++)
        {
            // Find open_flow_swich module within submodules
            if (topo_spanntree.getNode(x)->getModule()->findSubmodule("open_flow_switch") >= 0)
            {
                cModule *mod = topo_spanntree.getNode(x)->getModule()->getSubmodule("open_flow_switch")->getSubmodule("OF_Switch");
                OF_Switch *proc = check_and_cast<OF_Switch *>(mod);
                proc->disablePorts(nodeInfo[x].ports);
            }
            else if (topo_spanntree.getNode(x)->getModule()->findSubmodule("OF_Switch") >= 0)
            {
                cModule *mod = topo_spanntree.getNode(x)->getModule()->getSubmodule("OF_Switch");
                OF_Switch *proc = check_and_cast<OF_Switch *>(mod);
                proc->disablePorts(nodeInfo[x].ports);
            }
        }
    }

}
void StaticSpanningTree::handleMessage(cMessage *msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}
