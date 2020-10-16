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

#include <LinkRemoverModule.h>
#include <OF_Switch.h>

Define_Module(LinkRemoverModule);
/*
LinkRemoverModule::LinkRemoverModule(){

}

LinkRemoverModule::~LinkRemoverModule(){

}
*/
void LinkRemoverModule::initialize(int stage) {
    EV << "Stage " << stage << " erreicht in linkRemover!";
    if (stage == 3) {
        EV << "Stage DREI erreicht!"; //intRemoved to be specified under parameters in netz03.ned or netz.ini
        intRemoved = par("intRemoved");
        numNodes = par("numNodes");

        cTopology topo_spanntree;
        //cTopology topo_spanntree;
        std::vector<std::string> nodeTypes = cStringTokenizer("openflow.openflow.switch.Open_Flow_Switch").asVector();
        topo_spanntree.extractByNedTypeName(nodeTypes);
        EV << "cTopology found " << topo_spanntree.getNumNodes() << "\n";


        //part of spanningtree
        nodeInfo.resize(topo_spanntree.getNumNodes());
        for (int i = 0; i < topo_spanntree.getNumNodes(); i++) {
            nodeInfo[i].moduleID = topo_spanntree.getNode(i)->getModuleId();
            nodeInfo[i].treeNeighbors.resize(topo_spanntree.getNumNodes(), 0);
        }
        ///////////////////////////////////////
        //LINKREMOVER MODULE

        intRemoved = par("intRemoved");
        numNodes = par("numNodes");

        //repeat limit set to the number of all possible links +1
        int wdh = topo_spanntree.getNumNodes() * topo_spanntree.getNumNodes() * topo_spanntree.getNumNodes();
        int intN = topo_spanntree.getNumNodes() - 1;
        int intL = 0;
        int tmpL = -1;
        int numBlk = 0;
        cModule *tmpModule;
        cTopology::Node *destNode;

        int nodeMatrix[10][10];// = new int[10][10];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
				if(i==j){
				    nodeMatrix[i][j] = 0;
				}else{
                nodeMatrix[i][j] = 1;
				}
            }
        }
        /*
        EV<<"Initial topological matrix: "<<endl;
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            //EV<<nodeMatrix[i][j]<<" & ";
                            EV<<nodeMatrix[i][j]<<" ";
                        }
//                        EV<<"\\\\ ";
                        EV<<endl;
                    }
                    EV<<endl;
*/
        //check if network connected
        bool isConn1 = true;
        topo_spanntree.calculateUnweightedSingleShortestPathsTo(
                topo_spanntree.getNode(0));

        for (int i = 1; i < topo_spanntree.getNumNodes(); i++) {
            if (topo_spanntree.getNode(i)->getNumPaths() < 1) {
                isConn1 = false;
            }
        }
        //        EV << "isConn1: " << isConn1;
        if (isConn1) { //counter to avoid loop when network separated at the start
            EV << "\nintRemoved: " << intRemoved << "\n";
            int optio=par("option");
            if(optio==1){
                for (int i = 0; i < intRemoved; i = i + 1) {

                    int intN=intrand(topo_spanntree.getNumNodes());

                    //EV<<"intN: "<<intN<<"\n";
                    if (((topo_spanntree.getNode(intN)->getNumOutLinks()) > 1)
                            && (wdh > 0)) {
                        wdh--;
                        tmpModule = topo_spanntree.getNode(intN)->getModule();

                        intL = intrand(topo_spanntree.getNode(intN)->getNumOutLinks());

                        //choose link to test
                        destNode =
                                topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode();

                        int thisOutPort = topo_spanntree.getNode(intN)->getLinkOut(
                                intL)->getLocalGate()->getIndex();
                        int thatOutPort= -1;

                        ///////////////////////////////////////////////////

                        int x =strcmp(topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getModule()->getName(),"open_flow_switch");
                        if(x!=0){
                            //EV<<"\nIST AUCH ENABLED2?"<<topo_spanntree.getNode(intN)->getLinkOut(intL)->isEnabled();
                            i--;
                            continue;
                        }
                        if(!topo_spanntree.getNode(intN)->getLinkOut(intL)->isEnabled()){
                            i--;
                            continue;
                        }

                        //outgoing link
                        topo_spanntree.getNode(intN)->getLinkOut(intL)->disable();
                        //topo_spanntree.getNode(intN)->getLinkIn(intL)->disable();

                        int m;
                        //inbound link
                        for (int i = 0;
                                i < topo_spanntree.getNode(intN)->getNumOutLinks();i++) {

                            if (topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getLinkOut(
                                    i)->getRemoteNode()->getModuleId()
                                    == topo_spanntree.getNode(intN)->getModuleId()) {

                                m=i;
                                //intL2 = i;
                                thatOutPort =topo_spanntree.getNode(intN)->getLinkOut(
                                        intL)->getRemoteNode()->getLinkOut(
                                                i)->getLocalGate()->getIndex();

                                topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getLinkOut(
                                        i)->disable();

                            }
                        }
                        const int intL2=m;
                        //EV<<"\nthatPortOut: "<<thatOutPort<<" plus intL2: "<<intL2;

                        //test if disabled link allowed
                        bool isConn2 = true;
                        topo_spanntree.calculateUnweightedSingleShortestPathsTo(
                                topo_spanntree.getNode(0));
                        for (int i = 1; i < topo_spanntree.getNumNodes(); i++) {

                            if (topo_spanntree.getNode(i)->getNumPaths() < 1) {
                                isConn2 = false;
                            }
                        }

                        if (isConn2) { //if all nodes reached, link can be disconnected

                            if (topo_spanntree.getNode(intN)->getModule()->findSubmodule(
                                    "open_flow_switch") >= 0) {
                                cModule *mod =
                                        topo_spanntree.getNode(intN)->getModule()->getSubmodule(
                                                "open_flow_switch")->getSubmodule(
                                                        "OF_Switch");
                            } else if (topo_spanntree.getNode(intN)->getModule()->findSubmodule(
                                    "OF_Switch") >= 0) {

                                cModule *mod1 = topo_spanntree.getNode(intN)->getModule();

                                cModule *mod =
                                        topo_spanntree.getNode(intN)->getModule()->getSubmodule(
                                                "OF_Switch");
                                OF_Switch *proc = check_and_cast<OF_Switch *>(mod);
                                EV<<"Switch1 name: "<<mod1->getFullName()<<endl;

                                EV<<"Switch1 number: "<<mod1->getFullName()[17]<<endl;
                                int switchInt1 = mod1->getFullName()[17] - '0';

                                if (proc->portVector[thisOutPort].state != OFPPS_BLOCKED) {

                                    // Highlight links that belong to spanning tree
                                    cModule *modOut =
                                            topo_spanntree.getNode(intN)->getLinkOut(
                                                    intL)->getRemoteNode()->getModule()->getSubmodule(
                                                            "OF_Switch");

                                    //For topo matrix
                                    ////////////////////
                                    cModule *mod2 = topo_spanntree.getNode(intN)->getLinkOut(
                                            intL)->getRemoteNode()->getModule();

                                    int switchInt2 =mod2->getFullName()[17]-'0';

                                    EV<<"Switch2 name: "<<mod2->getFullName()<<endl;
//                                    EV<<"Switch2 number: "<<mod2->getFullName()[17]<<endl;
                                    EV<<"Switch2 number: "<<switchInt2<<endl;
                                    nodeMatrix[switchInt1][switchInt2] = 0;
                                    nodeMatrix[switchInt2][switchInt1] = 0;

                                    ///////////////////


                                    OF_Switch *procOut =
                                            check_and_cast<OF_Switch *>(modOut);

                                    //coloring links
                                    cGate *gateOut = topo_spanntree.getNode(intN)->getLinkOut(
                                            intL)->getLocalGate();
                                    cDisplayString& connDispStrOut =
                                            gateOut->getDisplayString();
                                    connDispStrOut.parse("ls=red,3,dashed");

                                    cGate *gateIn = gateOut->getNextGate();
                                    cDisplayString& connDispStrIn =
                                            gateIn->getDisplayString();
                                    connDispStrIn.parse("ls=red,3,dashed");

                                    //actually blocking port
                                    EV << "portVector.state before: "<< proc->portVector[thisOutPort].state;
                                    proc->portVector[thisOutPort].state |= OFPPS_BLOCKED;
                                    proc->portVector[thisOutPort].state |= OFPPS_LINK_DOWN; //FUER LINKREMOVER
                                    //                                proc->portVector[thisOutPort].state |= OFPPC_PORT_DOWN; //FUER LINKREMOVER
                                    EV << "portVector.state after: "<< proc->portVector[thisOutPort].state;

                                    OF_Switch *procOther = check_and_cast<
                                            OF_Switch *>(
                                                    gateIn->getOwnerModule()->getSubmodule(
                                                            "OF_Switch"));


                                    procOther->portVector[thatOutPort].state |= OFPPS_BLOCKED;
                                    procOther->portVector[thatOutPort].state |= OFPPS_LINK_DOWN; //FUER LINKREMOVER
                                    //                                proc->portVector[thisOutPort].state |= OFPPC_PORT_DOWN; //FUER LINKREMOVER
                                    numBlk++;
                                    EV << "\nBlocking Link between Switch ID: "
                                            << proc->getParentModule()->getId()
                                            << " and Switch ID: "
                                            << procOut->getParentModule()->getId();

                                    EV << "\nColoring Link between Switch ID: "
                                            << gateOut->getOwnerModule()
                                            ->getId()
                                            << " and Switch ID: "
                                            << gateIn->getOwnerModule()->getId();

                                    EV << "\nNUMBLK: " << numBlk << "\n";
                                }
                            }

                        } else {
                            topo_spanntree.getNode(intN)->getLinkIn(intL)->enable();
                            topo_spanntree.getNode(intN)->getLinkOut(intL)->enable();
                            topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getLinkIn(
                                    intL2)->enable();
                            topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getLinkOut(
                                    intL2)->enable();
                            i = i - 1;  //repeat
                            //wdh = wdh - 1;
                        }
                        //                    srand(r); //seed for random
                        //                    r++;
                    }
                    //srand(r); //seed for random
                    //r++;
                    EV<<"\nEND i: "<<i<<"\n";
                    if (wdh <= 0) {
                        EV<<"\nSCHLUSS!\n";
                        i = intRemoved + 1;
                    }
                }


            }else if(optio==2){
                int j=0;
                int i=0;
                EV<<"numOutLinks, i=0: "<<topo_spanntree.getNode(i)->getNumOutLinks()<<endl;
                for (int g = 0; g < topo_spanntree.getNumNodes()*topo_spanntree.getNumNodes();g++) {
                    //weitere Kante
                    if(i+1>=topo_spanntree.getNumNodes()){
                        j++;
                    }
                    //EV<<"numOutLinks: "<<topo_spanntree.getNode(i)->getNumOutLinks()<<endl;
                    //mehrmals iteriert durch Knoten bis alle Kanten überprüft sind
                    i=g%numNodes;
//                    j=j%topo_spanntree.getNode(i)->getNumOutLinks();
                    EV<<"i1: "<<i<<endl;
                    EV<<"j1: "<<j<<endl;
                    //for (int j = 0; j < topo_spanntree.getNode(i)->getNumOutLinks(); j++) {
                    if(j<topo_spanntree.getNode(i)->getNumOutLinks()){
                        int tmpIndex=topo_spanntree.getNode(i)->getLinkOut(j)->getRemoteNode()->getModule()->getIndex();
                        //tmpIndex+1>=topo_spanntree.getNode(i)->getNumOutLinks()
                        if(!(tmpIndex==topo_spanntree.getNode(i)->getModule()->getIndex()-1 || tmpIndex==topo_spanntree.getNode(i)->getModule()->getIndex()+1)){
                            EV<<"TEST";
                            intN=i;
                            tmpModule = topo_spanntree.getNode(intN)->getModule();

                            intL = j;
                            //choose link to test
                            destNode =
                                    topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode();

                            int thisOutPort = topo_spanntree.getNode(intN)->getLinkOut(
                                    intL)->getLocalGate()->getIndex();
                            int thatOutPort =-1;

                            for (int m = 0;m < topo_spanntree.getNode(intN)->getNumOutLinks();m++) {

                                if (topo_spanntree.getNode(intN)->getLinkOut(intL)->getRemoteNode()->getLinkOut(
                                        m)->getRemoteNode()->getModuleId()
                                        == topo_spanntree.getNode(intN)->getModuleId()) {
                                    thatOutPort =topo_spanntree.getNode(intN)->getLinkOut(
                                            intL)->getRemoteNode()->getLinkOut(
                                                    m)->getLocalGate()->getIndex();
                                }
                            }

                            cModule *mod =topo_spanntree.getNode(intN)->getModule()->getSubmodule(
                                    "OF_Switch");
                            OF_Switch *proc = check_and_cast<OF_Switch *>(mod);


                            if (proc->portVector[thisOutPort].state != (OFPPS_BLOCKED | OFPPS_LINK_DOWN)) {

                                // Highlight links that belong to spanning tree
                                cModule *modOut =
                                        topo_spanntree.getNode(intN)->getLinkOut(
                                                intL)->getRemoteNode()->getModule()->getSubmodule(
                                                        "OF_Switch");

                                OF_Switch *procOut =
                                        check_and_cast<OF_Switch *>(modOut);

                                //coloring links
                                cGate *gateOut = topo_spanntree.getNode(intN)->getLinkOut(
                                        intL)->getLocalGate();
                                cDisplayString& connDispStrOut =
                                        gateOut->getDisplayString();
                                connDispStrOut.parse("ls=red,3,dashed");

                                cGate *gateIn = gateOut->getNextGate();
                                cDisplayString& connDispStrIn =
                                        gateIn->getDisplayString();
                                connDispStrIn.parse("ls=red,3,dashed");

                                //actually blocking port
                                EV << "portVector.state before: "<< proc->portVector[thisOutPort].state;
                                proc->portVector[thisOutPort].state |= OFPPS_BLOCKED;
                                proc->portVector[thisOutPort].state |= OFPPS_LINK_DOWN; //FUER LINKREMOVER
                                //                                proc->portVector[thisOutPort].state |= OFPPC_PORT_DOWN; //FUER LINKREMOVER
                                EV << "portVector.state after: "<< proc->portVector[thisOutPort].state;

                                OF_Switch *procOther = check_and_cast<
                                        OF_Switch *>(
                                                gateIn->getOwnerModule()->getSubmodule(
                                                        "OF_Switch"));


                                procOther->portVector[thatOutPort].state |= OFPPS_BLOCKED;
                                procOther->portVector[thatOutPort].state |= OFPPS_LINK_DOWN; //FUER LINKREMOVER
                                //proc->portVector[thisOutPort].state |= OFPPC_PORT_DOWN; //FUER LINKREMOVER
                                numBlk++;
                                EV << "\nBlocking Link between Switch ID: "
                                        << proc->getParentModule()->getId()
                                        << " and Switch ID: "
                                        << procOut->getParentModule()->getId();

                                EV << "\nColoring Link between Switch ID: "
                                        << gateOut->getOwnerModule()
                                        ->getId()
                                        << " and Switch ID: "
                                        << gateIn->getOwnerModule()->getId();

                                intRemoved--;
                                EV << "\nNUMBLK: " << numBlk << " intRemoved: "<<intRemoved<<endl;
                            }
                        }
                        EV<<"i2: "<<i<<endl;
                    }
                    if(intRemoved<=0){
                        //                           j=topo_spanntree.getNode(i)->getNumOutLinks();
                        g=topo_spanntree.getNumNodes()*topo_spanntree.getNumNodes();
                    }
                }
            }
        } else {
            EV << "Network not connected!";
        }
    }
}
void LinkRemoverModule::handleMessage(cMessage *msg) {
    error("this module doesn't handle messages, it runs only in initialize()");
}
void LinkRemoverModule::finish(){
}
