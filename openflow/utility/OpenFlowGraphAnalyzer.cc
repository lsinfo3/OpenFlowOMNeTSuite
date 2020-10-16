#include "OpenFlowGraphAnalyzer.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <numeric>
#include "LinkRemoverModule.h"
#include "ctopology.h"

Define_Module(OpenFlowGraphAnalyzer);

struct compNodeInt {
        bool operator()(const pair<cTopology::Node *, int> &a, const pair<cTopology::Node *, int> &b) {
            return a.second > b.second;
        }
};

struct compNodeDouble {
        bool operator()(const pair<cTopology::Node *, double> &a, const pair<cTopology::Node *, double> &b) {
            return a.second > b.second;
        }
};

void OpenFlowGraphAnalyzer::initialize(int stage) {
    if (stage == 4) {

        const char *NodeType = par("NodeType");
        considerOnlyEndToEnd = par("considerOnlyEndToEnd");
        std::vector<std::string> nodeTypes = cStringTokenizer(NodeType).asVector();
        topo.extractByNedTypeName(nodeTypes);

        // For weighted Paths
        std::vector<std::string> nodeTypes_weighted = cStringTokenizer("openflow.nodes.DistanceChannel openflow.nodes.Open_Flow_Domain").asVector();
        topo_weighted.extractByNedTypeName(nodeTypes_weighted);

        // Weighted Paths -> works only for Topologies with DinstanceChannels as Links
        double pathWeights_sum = 0.0;
        double pathCount = 0.0;
        for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
              auto src = topo_weighted.getNode(i);

                 for (int j = 0; j < topo_weighted.getNumNodes(); j++) {

                         if (i == j) {
                             continue;
                         }
                         auto trg = topo_weighted.getNode(j);
                         double pathWeight = getWeightedShortestPaths(src, trg);
                         pathWeights_sum = pathWeights_sum + pathWeight;
                         pathCount++;
                 }
             }
         avgPathDelay = pathWeights_sum/pathCount;

//////////////////////////////////For LinkRemover
        for (int i = 0; i < topo.getNumNodes(); i++) {
            for (int j = 0; j < topo.getNode(i)->getNumOutLinks(); j++) {
                if (strstr(topo.getNode(i)->getLinkOut(j)->getLocalGate()->getName(),"gateCPlane") != NULL) { // TODO: unnoetige Bedingung?
                    continue;
                }
                if (topo.getNode(i)->getModule()->findSubmodule("OF_Switch") > 0) {
                    if (strstr(topo.getNode(i)->getLinkOut(j)->getLocalGate()->getOwnerModule()->getName(), "open_flow_controller") != NULL) { // TODO: unnoetige Bedingung?
                        topo.getNode(i)->getLinkOut(j)->disable();

                    } else {
                        cModule *module = topo.getNode(i)->getModule()->getSubmodule("OF_Switch");
                        OF_Switch *swi = check_and_cast<OF_Switch *>(module);

                        int thisPort = topo.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex();
                        cGate *thisGate = topo.getNode(i)->getLinkOut(j)->getLocalGate();

                        if (swi->portVector[thisPort].state == (OFPPS_BLOCKED | OFPPS_LINK_DOWN)) {

                            //disabling a link
                            topo.getNode(i)->getLinkOut(j)->disable();

                            //coloring
                            cDisplayString& connDispStrOut = thisGate->getDisplayString();
                            cGate *gateIn = thisGate->getNextGate();
                            cDisplayString& connDispStrIn = gateIn->getDisplayString();
                            connDispStrIn.parse("ls=red,3,dashed");
                            connDispStrOut.parse("ls=red,3,dashed");
                        }
                    }
                }
            }
        }
////////////////////////////

        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "switch") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Switch") != NULL) {
                continue;
            }

            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (i == j) {
                    continue;
                }
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "switch") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Switch") != NULL) {
                    continue;
                }

                computedPaths.push_front(getShortestPath(topo.getNode(i), topo.getNode(j)));
            }
        }

        int nrOfSwitches = 0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            nrOfSwitches++;
        }

        // Radius, Durchmesser, Ekzentrizitaet berechnen
        std::vector<int> nodeEccentricities;
        hopCountDistribution = std::map<int, int>();
        closenesses = std::map<cTopology::Node *, double>();
        averageCloseness = 0.0;
        averageFarness = 0.0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            int max = 0;
            double farness = 0.0;
            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                if (i == j) {
                    continue;
                }
                auto shortestPath = getShortestPath(topo.getNode(i), topo.getNode(j));
                int shortestPathSize = shortestPath.size();
                farness += shortestPathSize;
                if (shortestPathSize > max) {
                    max = shortestPathSize;
                }
                auto it = hopCountDistribution.find(shortestPathSize - 1);
                if (it != hopCountDistribution.end()) {
                    int old = it->second;
                    it->second = old + 1;
                }
                else {
                    hopCountDistribution.insert(std::pair<int, int>(shortestPathSize - 1, 1));
                }
            }
            double farnessNormalized = farness / ((double) nrOfSwitches - 1.0);
            farnesses.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), farnessNormalized));
            averageFarness += farnessNormalized/(double) nrOfSwitches;
            double closeness = 1.0/farness * ((double) nrOfSwitches - 1.0);
            averageCloseness += closeness/(double) nrOfSwitches;
            closenesses.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), closeness));
            nodeEccentricities.push_back(max);
        }

        int sum = std::accumulate(nodeEccentricities.begin(), nodeEccentricities.end(), 0.0);
        eccentricity = (double) sum / (double) nodeEccentricities.size() - 1.0;
        radius = *std::min_element(nodeEccentricities.begin(), nodeEccentricities.end()) - 1;
        diameter = *std::max_element(nodeEccentricities.begin(), nodeEccentricities.end()) - 1;


        // Knotengrade (ohne Client-Knoten und -Links) berechnen
        nodeDegreeDistribution = std::map<int, int>();
        std::map<cTopology::Node *, int> nodeDegrees = std::map<cTopology::Node *, int>();
        int totalLinks = 0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            auto currentNode = topo.getNode(i);
            if (strstr(currentNode->getModule()->getFullPath().c_str(), "client") != NULL || strstr(currentNode->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(currentNode->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            int outLinks = currentNode->getNumOutLinks();
            int outLinksWithoutClients = 0;
            for (int j = 0; j < outLinks; j++) {
                if (strstr(currentNode->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL) {
                    continue;
                }
                ////////////fuer LinkRemover
                if (!(currentNode->getLinkOut(j)->isEnabled())) {
                           continue;
                }
                ////////////////////////////
                auto neighbour = currentNode->getLinkOut(j)->getRemoteNode();
                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") == NULL && strstr(neighbour->getModule()->getFullPath().c_str(), "Client") == NULL && strstr(neighbour->getModule()->getFullPath().c_str(), "host") == NULL) {
                    outLinksWithoutClients++;
                }
            }
            int inLinks = currentNode->getNumInLinks();
            int inLinksWithoutClients = 0;
            for (int j = 0; j < inLinks; j++) {
                if (strstr(currentNode->getLinkIn(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(currentNode->getLinkIn(j)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                    continue;
                }

                ////////////fuer LinkRemover
                       if (!(currentNode->getLinkIn(j)->isEnabled())) {
                           continue;
                       }
                ////////////////////////////
                auto neighbour = currentNode->getLinkIn(j)->getRemoteNode();
                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") == NULL && strstr(neighbour->getModule()->getFullPath().c_str(), "Client") == NULL && strstr(neighbour->getModule()->getFullPath().c_str(), "host") == NULL) {
                    inLinksWithoutClients++;
                }
            }

            int degree = outLinksWithoutClients + inLinksWithoutClients;
            totalLinks = totalLinks + outLinksWithoutClients;
            nodeDegrees.insert(std::pair<cTopology::Node *, int>(currentNode, degree));

            auto it = nodeDegreeDistribution.find(degree);
            if (it != nodeDegreeDistribution.end()) {
                int old = it->second;
                it->second = old + 1;
            }
            else {
                nodeDegreeDistribution.insert(std::pair<int, int>(degree, 1));
            }
        }

        // Assortativity (Pearson Korrelation der obigen Knotengrade) berechnen
        double sum1 = 0;
        double sum2 = 0;
        double sum3 = 0;
        double sum4 = 0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            auto currentNode = topo.getNode(i);
            if (strstr(currentNode->getModule()->getFullPath().c_str(), "client") != NULL || strstr(currentNode->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(currentNode->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            int degreeCurrent = nodeDegrees[currentNode];
            auto nrOfNeighbours = currentNode->getNumOutLinks();
            for (int j = 0; j < nrOfNeighbours; j++) {

                if (strstr(currentNode->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(currentNode->getLinkOut(j)->getLocalGate()->getName(), "gateControlPlane") != NULL ) {
                    continue;
                }
                ////////////fuer LinkRemover
                if (!(currentNode->getLinkOut(j)->isEnabled())) {
                           continue;
                }
                ////////////////////////////
                auto neighbour = currentNode->getLinkOut(j)->getRemoteNode();
                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                int degreeNeighbour = nodeDegrees[neighbour];


                double d1 = (double) degreeCurrent;
                double d2 = (double) degreeNeighbour;

                sum1 = sum1 + (d1 * d2);
                sum2 = sum2 + (d1 + d2) / (2 * (double) totalLinks);
                sum3 = sum3 + 0.5 * (d1 * d1 + d2 * d2);
                sum4 = sum4 + (d1 + d2) / (2 * (double) totalLinks);

            }
        }

        double r_zaehler = (sum1 / ((double) totalLinks)) - (sum2 * sum2);
        double r_nenner = (sum3 / ((double) totalLinks)) - (sum4 * sum4);
        double r;
        if (r_nenner == 0) {
            r = 0;
        }
        else {
            r = r_zaehler / r_nenner;
        }

        if (totalLinks/2 == nrOfSwitches * (nrOfSwitches - 1)/2) {
            assortativity = 0; // da vollstaendiger Graph, macht so mehr Sinn. Mit obiger Rechnung kï¿½me 1 raus, aber da alle Knoten
                               // in einem vollst. Graphen den gleichen Grad haben, gibt es kein "hohen" oder "niedrigen" Grad.
        } else {
            assortativity = r;
        }


        // Fuer alle Knotenpaare ALLE kuerzestenen Wege berechnen
        std::map<cTopology::Node *, std::map<cTopology::Node *, std::list<std::list<cTopology::Node *>>> >allShortestPaths = std::map<cTopology::Node *, std::map<cTopology::Node *, std::list<std::list<cTopology::Node * >>>>();
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            auto dist = getAllDistances(topo.getNode(i));

            auto map1 = std::map<cTopology::Node *, std::list<std::list<cTopology::Node *>>>();
            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                if (i == j) {
                    continue;
                }
                std::list<std::list<cTopology::Node *>> shortestPaths = std::list<std::list<cTopology::Node *>>();
                std::list<cTopology::Node *> currentPath = std::list<cTopology::Node *>();
                currentPath.push_front(topo.getNode(j));
                getAllShortestPaths(shortestPaths, topo.getNode(i), topo.getNode(j), dist, currentPath);

                auto pair1 = std::pair<cTopology::Node *, std::list<std::list<cTopology::Node *>>>(topo.getNode(j), shortestPaths);
                map1.insert(pair1);
            }
            auto pair2 = std::pair<cTopology::Node *, std::map<cTopology::Node *, std::list<std::list<cTopology::Node *>>> >(topo.getNode(i), map1);
            allShortestPaths.insert(pair2);
        }

        // Betweenness -> im Paper wurde hier die Summe ber alle Knotenpaare in der Formel vergessen?
               std::vector<double> betweennesses = std::vector<double>();
               betweennessesNormalized = std::map<cTopology::Node *, double>();
               double norm_factor = (nrOfSwitches - 1) * (nrOfSwitches - 2);
               for (int i = 0; i < topo.getNumNodes(); i++) {
                   double betweenness = 0.0;
                   if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                       continue;
                   }
                   for (int j = 0; j < topo.getNumNodes(); j++) {
                       if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                           continue;
                       }
                       if (j == i) {
                           continue;
                       }

                       for (int k = 0; k < topo.getNumNodes(); k++) {
                           if (strstr(topo.getNode(k)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(k)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(k)->getModule()->getFullPath().c_str(), "host") != NULL) {
                               continue;
                           }
                           if (k == j || k == i) {
                               continue;
                           }

                           auto paths = allShortestPaths[topo.getNode(j)][topo.getNode(k)];
                           for (auto it = paths.begin(); it != paths.end(); it++) {
                               auto nodeInPath = std::find(it->begin(), it->end(), topo.getNode(i));
                               auto path = *it;
                               if (nodeInPath != it->end()) {
                                   betweenness = betweenness + (1 / (double) paths.size());
                               }
                           }
                       }
                   }
                   betweennesses.push_back(betweenness);
                   betweennessesNormalized.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), betweenness/norm_factor));
               }
               double maxBetweenness = *std::max_element(betweennesses.begin(), betweennesses.end());
               averageBetweenness = (double) std::accumulate(betweennesses.begin(), betweennesses.end(), 0.0) / norm_factor / (double) nrOfSwitches;


        // Central Point of Dominance berechnen
        cpd = 0;
        for (auto it = betweennesses.begin(); it != betweennesses.end(); it++) {
            cpd = cpd + (maxBetweenness / norm_factor - *it / norm_factor) / ((nrOfSwitches - 1.0));
        }

        // Persistence
        std::list<int> nrOfDisjointPaths; // = alle disjoint paths <= Durchmesser
        std::list<int> maxFlows; // = alle disjoint paths
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            std::list<cTopology::Node *> neighbours;
            for (int k = 0; k < topo.getNode(i)->getNumOutLinks(); k++) {
                if (strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                    continue;
                }
                ////////////fuer LinkRemover
                if (!(topo.getNode(i)->getLinkOut(k)->isEnabled())) {
                    continue;
                }
                ////////////////////////////
                auto neighbour = topo.getNode(i)->getLinkOut(k)->getRemoteNode();

                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                neighbours.push_back(neighbour);
            }

            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                if (i == j) {
                    continue;
                }
                auto p = findDisjointPaths(topo.getNode(i), topo.getNode(j));
                maxFlows.push_back(p.first);

                auto isNeighbour = std::find(neighbours.begin(), neighbours.end(), topo.getNode(j));
                if (isNeighbour != neighbours.end()) {
                    continue;
                }
                auto paths = p.second;
                int pathCounter = 0;
                for (auto it = paths.begin(); it != paths.end(); it++) {
                    if (*it <= diameter) {
                        pathCounter++;
                    }
                }
                nrOfDisjointPaths.push_back(pathCounter);
            }
        }

        if (totalLinks/2 == nrOfSwitches * (nrOfSwitches - 1)/2) {
             edgePersistence = 1; // es muss bei einem vollstaendigen Graphen nur eine Kante entfernt werden, um den Durchmesser zu erhï¿½heh
                                    // >> Durchmesser wird von nrOfSwitches zu nrOfSwitches - 1 reduziert.
         } else {
             edgePersistence = *std::min_element(nrOfDisjointPaths.begin(), nrOfDisjointPaths.end());
         }

        edgeConnectivity = *std::min_element(maxFlows.begin(), maxFlows.end());

        averageNrOfEdgeDistinctPaths = (double) std::accumulate(maxFlows.begin(), maxFlows.end(), 0.0) / (double) maxFlows.size();

        std::list<int> nrOfNodeDisjointPaths; // = alle disjoint paths <= Durchmesser
        std::list<int> maxFlows2; // = alle disjoint paths
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            std::list<cTopology::Node *> neighbours;
            for (int k = 0; k < topo.getNode(i)->getNumOutLinks(); k++) {
                if (strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                    continue;
                }
                ////////////fuer LinkRemover
                if (!(topo.getNode(i)->getLinkOut(k)->isEnabled())) {
                    continue;
                }
                ////////////////////////////
                auto neighbour = topo.getNode(i)->getLinkOut(k)->getRemoteNode();

                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                neighbours.push_back(neighbour);
            }

            for (int j = 0; j < topo.getNumNodes(); j++) {

                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                if (i == j) {
                    continue;
                }

                auto p = findNodeDisjointPaths(topo.getNode(i), topo.getNode(j));
                maxFlows2.push_back(p.first);

                auto isNeighbour = std::find(neighbours.begin(), neighbours.end(), topo.getNode(j));
                if (isNeighbour != neighbours.end()) {
                    continue;
                }
                auto paths = p.second;
                int pathCounter = 0;
                for (auto it = paths.begin(); it != paths.end(); it++) {
                    int nrOfNodesInPath = *it + 1; // die Funktion gibt Anzahl der Kanten im Pfad zurueck (also Anz. Knoten - 1)
                    int nrOfNodesWithoutSrcAndTrg = nrOfNodesInPath - 2;
                    int nrOfDummyNodes = nrOfNodesWithoutSrcAndTrg / 2; // = Anzahl an eingefuegten Dummy-Kanten
                    int realPathLength = *it - nrOfDummyNodes;
                    if (realPathLength <= diameter) {
                        pathCounter++;
                    }

                }
                nrOfNodeDisjointPaths.push_back(pathCounter);
            }
        }


       if (totalLinks/2 == nrOfSwitches * (nrOfSwitches - 1)/2) {
            vertexPersistence = 1; // es muss bei einem vollstaendigen Graphen nur ein Knoten entfernt werden, um den Durchmesser zu erhï¿½heh
                                   // >> Durchmesser wird von nrOfSwitches zu nrOfSwitches - 1 reduziert.
        } else {
            vertexPersistence = *std::min_element(nrOfNodeDisjointPaths.begin(), nrOfNodeDisjointPaths.end());
        }


        vertexConnectivity = *std::min_element(maxFlows2.begin(), maxFlows2.end());
        averageNrOfNodeDistinctPaths = (double) std::accumulate(maxFlows2.begin(), maxFlows2.end(), 0.0) / (double) maxFlows2.size();

        // Clustering Coefficient
        std::map<cTopology::Node *, double> localClusteringCoefficients;
        globalClusteringCoefficient = 0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            std::list<cTopology::Node *> neighbours = std::list<cTopology::Node *>();
            int linksBetweenNeighbours = 0;
            for (int k = 0; k < topo.getNode(i)->getNumOutLinks(); k++) {
                if (strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL) {
                    continue;
                }
                ////////////fuer LinkRemover
                if (!(topo.getNode(i)->getLinkOut(k)->isEnabled())) {
                           continue;
                }
                ////////////////////////////
                auto neighbour = topo.getNode(i)->getLinkOut(k)->getRemoteNode();

                if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }

                neighbours.push_back(neighbour);
            }
            for (auto it = neighbours.begin(); it != neighbours.end(); it++) {
                auto n = *it;
                for (int j = 0; j < n->getNumOutLinks(); j++) {
                    if (strstr(n->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(n->getLinkOut(j)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                        continue;
                    }
                    ////////////fuer LinkRemover
                    if (!(n->getLinkOut(j)->isEnabled())) {
                               continue;
                    }
                    ////////////////////////////
                    auto neighbourOfNeighbour = n->getLinkOut(j)->getRemoteNode();
                    if (strstr(neighbourOfNeighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbourOfNeighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbourOfNeighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                        continue;
                    }

                    if (std::find(neighbours.begin(), neighbours.end(), neighbourOfNeighbour) != neighbours.end()) {
                        linksBetweenNeighbours++;
                    }
                }
            }

            double localClusteringCoefficient;
            if (neighbours.size() == 1) {
                localClusteringCoefficient = 0;
            }
            else {
                double localClusteringCoefficient_nenner = (double) (neighbours.size() * (neighbours.size() - 1));
                localClusteringCoefficient = linksBetweenNeighbours / localClusteringCoefficient_nenner;
            }
            localClusteringCoefficients.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), localClusteringCoefficient));
            globalClusteringCoefficient += localClusteringCoefficient;
        }
        globalClusteringCoefficient = globalClusteringCoefficient / ((double) localClusteringCoefficients.size());

        // Expansion
        int nrOfCalculations = 10;
        graphExpansions = std::list<double>();
        for (int i = 1; i <= nrOfCalculations; i++) {
            double ballRadiusNotRounded = (double) i * (1.0 / (double) nrOfCalculations) * (double) diameter;
            int ballRadius = ceil(ballRadiusNotRounded);
            double graphExpansion = 0;
            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                int nodesInRad = getNodesInRadius(topo.getNode(j), ballRadius);
                double expansion = (double) nodesInRad / (double) nrOfSwitches;
                graphExpansion += expansion/(double) nrOfSwitches; // Paper ist an der Stelle etwas wirr... hier fehlt auch wieder die Summe über alle Knoten... ähnlich wie bei der Betweenness?
                                                                   // ich habe es einfach so interpretiert: graphExpansion = avg. nodeExpansion
            }
            graphExpansions.push_back(graphExpansion);
        }

        // Rich Club Coefficient
        int nrOfCalculations2 = 10;
        richClubCoefficients = std::list<double>();
        for (int i = 1; i <= nrOfCalculations2; i++) {
            double nodesInClub = (double) i * (1.0 / (double) nrOfCalculations) * (double) nrOfSwitches;
            double coefficient = 0;
            int n = 0;
            int minDegree = INT_MAX;
            int linksInClub = 0;
            for (auto it = nodeDegreeDistribution.rbegin(); it != nodeDegreeDistribution.rend(); it++) {
                n += it->second;
                if ((double) n >= nodesInClub) {
                    minDegree = it->first;
                    break;
                }

            }

            std::list<cTopology::Node *> richClubNodes = std::list<cTopology::Node *>();
            for (auto it = nodeDegrees.begin(); it != nodeDegrees.end(); it++) {
                if (it->second >= minDegree) {
                    richClubNodes.push_back(it->first);

                }
            }
            for (auto it = richClubNodes.begin(); it != richClubNodes.end(); it++) {
                auto richNode = *it;
                for (int j = 0; j < richNode->getNumOutLinks(); j++) {
                    if (strstr(richNode->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(richNode->getLinkOut(j)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                        continue;
                    }
                    ////////////fuer LinkRemover
                    if (!(richNode->getLinkOut(j)->isEnabled())) {
                        continue;
                    }
                    ////////////////////////////
                    auto neighbour = richNode->getLinkOut(j)->getRemoteNode();
                    if (std::find(richClubNodes.begin(), richClubNodes.end(), neighbour) != richClubNodes.end()) {
                        linksInClub++;
                    }
                }
            }
            coefficient = (double) linksInClub / ((double) richClubNodes.size() * ((double) richClubNodes.size() - 1.0));
            richClubCoefficients.push_back(coefficient);
        }




        maxPathLength = 0;
        minPathLength = std::numeric_limits<int>::max();
        numClientNodes = 0;
        numSwitchNodes = 0;
        avgPathLength = 0;

        std::list<std::list<cTopology::Node *> >::iterator iterOuter;
        std::list<cTopology::Node *>::iterator iterInner;
        int pathCounter = 0;
        for (iterOuter = computedPaths.begin(); iterOuter != computedPaths.end(); iterOuter++) {
            if (iterOuter->size() - 1 < minPathLength) {
                minPathLength = iterOuter->size() - 1;
            }
            if (iterOuter->size() - 1 > maxPathLength) {
                maxPathLength = iterOuter->size() - 1;
            }
            pathCounter++;
            avgPathLength += iterOuter->size() - 1;

            int temp = 0;
            for (iterInner = iterOuter->begin(); iterInner != iterOuter->end(); iterInner++) {

                if (strstr((*iterInner)->getModule()->getFullName(), "switch") == NULL && strstr((*iterInner)->getModule()->getFullName(), "Switch") == NULL) {
                    if (clMap.count((*iterInner)->getModule()->getFullPath()) > 0) {
                        temp = clMap[(*iterInner)->getModule()->getFullPath()];
                        clMap.erase((*iterInner)->getModule()->getFullPath());
                        clMap[(*iterInner)->getModule()->getFullPath()] = temp + 1;
                    }
                    else {
                        clMap[(*iterInner)->getModule()->getFullPath()] = 1;
                    }
                }
                else {
                    if (swMap.count((*iterInner)->getModule()->getFullPath()) > 0) {
                        temp = swMap[(*iterInner)->getModule()->getFullPath()];
                        swMap.erase((*iterInner)->getModule()->getFullPath());
                        swMap[(*iterInner)->getModule()->getFullPath()] = temp + 1;
                    }
                    else {
                        swMap[(*iterInner)->getModule()->getFullPath()] = 1;
                    }
                }
            }
        }

        //compute avg links switch
        int numLinks = 0;
        for (int i = 0; i < topo.getNumNodes(); i++) {
            if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "switch") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Switch") != NULL) {

                for (int j = 0; j < topo.getNode(i)->getNumOutLinks(); j++) {
                    //ignore control plane
                    if (strstr(topo.getNode(i)->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(j)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                        continue;
                    }
                    ////////////fuer LinkRemover
                           if (!(topo.getNode(i)->getLinkOut(j)->isEnabled())) {
                               continue;
                           }
                    ////////////////////////////
                    numLinks++;
                }
            }
        }

        avgPathLength = avgPathLength / computedPaths.size();
        numClientNodes = clMap.size();
        numSwitchNodes = swMap.size();
        avgNumSwitchLinks = numLinks / numSwitchNodes;

    }
}

int OpenFlowGraphAnalyzer::getNodesInRadius(cTopology::Node * src, int rad) {
    int inRadius = 1;
    for (int i = 0; i < topo.getNumNodes(); i++) {
        auto node = topo.getNode(i);
        if (strstr(node->getModule()->getFullPath().c_str(), "client") != NULL || strstr(node->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(node->getModule()->getFullPath().c_str(), "host") != NULL) {
            continue;
        }

        if (strstr(node->getModule()->getFullPath().c_str(),src->getModule()->getFullPath().c_str()) != NULL) {
            continue;

        }
        if (getShortestPath(src, node).size() - 1 <= rad) {
            inRadius++;
        }
    }
    return inRadius;
}

std::map<cTopology::Node *, int> OpenFlowGraphAnalyzer::getAllDistances(cTopology::Node * src) {
    std::map<cTopology::Node *, int> distances = std::map<cTopology::Node *, int>();
    for (int i = 0; i < topo.getNumNodes(); i++) {
        cTopology::Node * tmpNode = topo.getNode(i);
        if (tmpNode == src) {
            distances[tmpNode] = 0;
        }
        else {
            distances[tmpNode] = std::numeric_limits<int>::max();
        }
    }
    std::list<cTopology::Node *> queue = std::list<cTopology::Node *>();
    queue.push_front(src);
    cTopology::Node * currentNode = NULL;
    while (!queue.empty()) {
        currentNode = queue.front();
        queue.pop_front();

        for (int i = 0; i < currentNode->getNumOutLinks(); i++) {
            //ignore control plane
            if (strstr(currentNode->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(currentNode->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                continue;
            }
///////////fuer LinkRemover
            if (!(currentNode->getLinkOut(i)->isEnabled())) {
                continue;
            }
///////////////////////////
            if (distances[currentNode->getLinkOut(i)->getRemoteNode()] == std::numeric_limits<int>::max()) {
                distances[currentNode->getLinkOut(i)->getRemoteNode()] = distances[currentNode] + 1;
                queue.push_back(currentNode->getLinkOut(i)->getRemoteNode());
            }
        }
    }
    return distances;
}

bool OpenFlowGraphAnalyzer::residualGraphBFS(std::map<int, std::map<int, int>> residualGraph, int src, int trg, std::map<int, int>& parents) {
    // cf. www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/
    // cf.www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
    std::map<int, bool> visited = std::map<int, bool>();
    queue<int> q;

    q.push(src);
    visited[src] = true;
    parents[src] = NULL;

    while (!q.empty()) {
        auto currentNode = q.front();
        q.pop();
        auto neighbours = residualGraph[currentNode];
        for (auto it = neighbours.begin(); it != neighbours.end(); it++) {
            auto neighbour = it->first;
            auto capacity = it->second;
            if (visited[neighbour] == false && capacity > 0) {
                q.push(neighbour);
                parents[neighbour] = currentNode;
                visited[neighbour] = true;
            }
        }
    }
    return (visited[trg] == true);
}

std::pair<int, std::list<int>> OpenFlowGraphAnalyzer::findNodeDisjointPaths(cTopology::Node * src, cTopology::Node * trg) {
    std::map<int, std::map<int, int>> rGraph = std::map<int, std::map<int, int>>(); // Residual Graph
    std::map<cTopology::Node *, int> nodeMap = std::map<cTopology::Node *, int>();  // Nummerierung der Knoten

    // Source und Target nummerieren
    nodeMap.insert(std::pair<cTopology::Node *, int>(src, 1));
    nodeMap.insert(std::pair<cTopology::Node*, int>(trg, 2));

    // Andere Knoten nummerieren
    int counter = 3;
    for (int i = 0; i < topo.getNumNodes(); i++) {
        if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
            continue;
        }
        if (topo.getNode(i) == src || topo.getNode(i) == trg) {
            continue;
        }
        nodeMap.insert(std::pair<cTopology::Node *, int>(topo.getNode(i), counter));
        counter++;
    }

    // Fï¿½r alle Knoten (ausser Source und Target) zwei Nummerierungen einfuehren und diese verbinden
    for (int i = 3; i <= nodeMap.size(); i++) {
        std::pair<int, int> pair1 = std::pair<int, int>(i + nodeMap.size() - 2, 1);
        rGraph[i].insert(pair1);
    }

    for (int i = 0; i < topo.getNumNodes(); i++) {
        if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
            continue;
        }

        // Nachbarn finden
        std::list<cTopology::Node *> neighbours;
        for (int k = 0; k < topo.getNode(i)->getNumOutLinks(); k++) {
            if (strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateControlPlane") != NULL  ) {
                continue;
            }
            ////////////fuer LinkRemover
            if (!(topo.getNode(i)->getLinkOut(k)->isEnabled())) {
                       continue;
            }
            ////////////////////////////
            auto neighbour = topo.getNode(i)->getLinkOut(k)->getRemoteNode();

            if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            neighbours.push_back(neighbour);
        }

        // Eintrag fuer Nachbarn entsprechend im rGraph einfuegen
        auto map1 = std::map<int, int>();
        for (int j = 0; j < topo.getNumNodes(); j++) {
            if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            auto isNeighbour = std::find(neighbours.begin(), neighbours.end(), topo.getNode(j));
            auto pair1 = std::pair<int, int>();
            if (isNeighbour != neighbours.end()) {
                pair1 = std::pair<int, int>(nodeMap[topo.getNode(j)], 1);
            }
            else {
                pair1 = std::pair<int, int>(nodeMap[topo.getNode(j)], 0);
            }
            map1.insert(pair1);
        }
        std::pair<int, std::map<int, int>> pair2;

        // alle "in"-Kanten eines Knoten gehen in die Original-Nummerierung, alle "out"-Kanten gehen aus der Zusatz-Nummerierung
        if (topo.getNode(i) == src || topo.getNode(i) == trg) {
            pair2 = std::pair<int, std::map<int, int>>(nodeMap[topo.getNode(i)], map1);
        }
        else {
            pair2 = std::pair<int, std::map<int, int>>(nodeMap[topo.getNode(i)] + nodeMap.size() - 2, map1);
        }
        rGraph.insert(pair2);
    }
    // cf. www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/
    // cf.www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
    std::map<int, int> parents = std::map<int, int>();
    int maxFlow = 0;
    int current;
    int previous;
    std::list<int> pathLengths;

    while (residualGraphBFS(rGraph, nodeMap[src], nodeMap[trg], parents)) {
        int pathFlow = INT_MAX;
        int pathLength = 0;
        current = nodeMap[trg];
        while (current != nodeMap[src]) {
            previous = parents[current];
            pathFlow = min(pathFlow, rGraph[previous][current]);
            current = parents[current];
            pathLength++;
        }

        pathLengths.push_back(pathLength);
        current = nodeMap[trg];
        while (current != nodeMap[src]) {
            previous = parents[current];
            rGraph[previous][current] -= pathFlow;
            rGraph[current][previous] += pathFlow;
            current = parents[current];
        }
        maxFlow += pathFlow;
    }
    return std::pair<int, std::list<int>>(maxFlow, pathLengths);
}

std::pair<int, std::list<int>> OpenFlowGraphAnalyzer::findDisjointPaths(cTopology::Node * src, cTopology::Node * trg) {
    std::map<int, std::map<int, int>> rGraph = std::map<int, std::map<int, int>>();
    std::map<cTopology::Node *, int> nodeMap = std::map<cTopology::Node *, int>();
    int counter = 1;
    for (int i = 0; i < topo.getNumNodes(); i++) {
        if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
            continue;
        }
        nodeMap.insert(std::pair<cTopology::Node *, int>(topo.getNode(i), counter));
        counter++;
    }

    for (int i = 0; i < topo.getNumNodes(); i++) {
        if (strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
            continue;
        }
        std::list<cTopology::Node *> neighbours;
        for (int k = 0; k < topo.getNode(i)->getNumOutLinks(); k++) {

            if (strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(topo.getNode(i)->getLinkOut(k)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                continue;
            }
            ////////////fuer LinkRemover
            if (!(topo.getNode(i)->getLinkOut(k)->isEnabled())) {
                       continue;
            }
            ////////////////////////////
            auto neighbour = topo.getNode(i)->getLinkOut(k)->getRemoteNode();

            if (strstr(neighbour->getModule()->getFullPath().c_str(), "client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(neighbour->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            neighbours.push_back(neighbour);
        }

        auto map1 = std::map<int, int>();
        for (int j = 0; j < topo.getNumNodes(); j++) {
            if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                continue;
            }
            auto isNeighbour = std::find(neighbours.begin(), neighbours.end(), topo.getNode(j));
            auto pair1 = std::pair<int, int>();
            if (isNeighbour != neighbours.end()) {
                pair1 = std::pair<int, int>(nodeMap[topo.getNode(j)], 1);
            }
            else {
                pair1 = std::pair<int, int>(nodeMap[topo.getNode(j)], 0);
            }
            map1.insert(pair1);
        }
        auto pair2 = std::pair<int, std::map<int, int>>(nodeMap[topo.getNode(i)], map1);
        rGraph.insert(pair2);
    }
    // cf. www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/
    // cf.www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
    std::map<int, int> parents = std::map<int, int>();
    int maxFlow = 0;
    int current;
    int previous;
    std::list<int> pathLengths;
    while (residualGraphBFS(rGraph, nodeMap[src], nodeMap[trg], parents)) {
        int pathFlow = INT_MAX;
        int pathLength = 0;

        current = nodeMap[trg];

        while (current != nodeMap[src]) {
            previous = parents[current];
            pathFlow = min(pathFlow, rGraph[previous][current]);
            current = parents[current];
            pathLength++;
        }

        pathLengths.push_back(pathLength);
        current = nodeMap[trg];
        while (current != nodeMap[src]) {
            previous = parents[current];
            rGraph[previous][current] -= pathFlow;
            rGraph[current][previous] += pathFlow;
            current = parents[current];
        }

        maxFlow += pathFlow;
    }
    return std::pair<int, std::list<int>>(maxFlow, pathLengths);
}

double OpenFlowGraphAnalyzer::getWeightedShortestPaths(cTopology::Node * src, cTopology::Node * trg) {
    double result = 0.0;

    std::map<cTopology::Node *, bool> visited = std::map<cTopology::Node *, bool>();
    std::map<cTopology::Node *, double> dist = std::map<cTopology::Node *, double>();
    std::map<cTopology::Node *, cTopology::Node *> prev = std::map<cTopology::Node *, cTopology::Node *>();

    priority_queue<pair<cTopology::Node*, double>, vector<pair<cTopology::Node*, double>>, compNodeDouble> q;

    //init verticies
    for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
        cTopology::Node * tmpNode = topo_weighted.getNode(i);
        if (tmpNode == src) {
            continue;
        }
        q.push(pair<cTopology::Node *, double>(tmpNode, std::numeric_limits<double>::max()));
        dist[tmpNode] = std::numeric_limits<double>::max();
        prev[tmpNode] = NULL;
    }

    //init src
    q.push(pair<cTopology::Node *, int>(src, 0));
    dist[src] = 0.0;
    prev[src] = NULL;

    cTopology::Node * u = NULL;
    while (!q.empty()) {

        u = q.top().first;
        q.pop();

        double alt;

        for (int i = 0; i < u->getNumOutLinks(); i++) {
            //ignore control plane

            if (strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                continue;
            }
            if (u->getLinkOut(i)->getLocalGate()->getChannel() == NULL) {
                continue;
            }

            if (u->getLinkOut(i)->getLocalGate()->getChannel()->getNumParams() < 7) {
                continue;
            }
     ////////////fuer LinkRemover
            if (!(u->getLinkOut(i)->isEnabled())) {
                continue;
            }
     ////////////////////////////
            double weight = u->getLinkOut(i)->getLocalGate()->getChannel()->par(1); // Hier ist der spezifizierte Delay gespeichtert -> deswegen funzt es vorerst nur für DistanceChannels
            weight = weight + 0.000035; // ServiceTime vom Switch miteinberechnen
            alt = dist[u] + weight;
            if (alt < dist[u->getLinkOut(i)->getRemoteNode()]) {
                dist[u->getLinkOut(i)->getRemoteNode()] = alt;
                prev[u->getLinkOut(i)->getRemoteNode()] = u;
                q.push(
                        pair<cTopology::Node *, int>(
                                u->getLinkOut(i)->getRemoteNode(), alt));
            }
        }
        visited[u] = true;
    }
    result = dist[trg];
    return result;
}
void OpenFlowGraphAnalyzer::getAllShortestPaths(std::list<std::list<cTopology::Node *>>& shortestPaths, cTopology::Node * src, cTopology::Node * trg, std::map<cTopology::Node *, int> distances,
        std::list<cTopology::Node *> currentPath) {
    int trgDist = distances[trg];

    for (int i = 0; i < trg->getNumOutLinks(); i++) {
        if (strstr(trg->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(trg->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
            continue;
        }
////////////fuer LinkRemover
        if (!(trg->getLinkOut(i)->isEnabled())) {
            continue;
        }
////////////////////////////
        auto neighbour = trg->getLinkOut(i)->getRemoteNode();
        int neighbourDist = distances[neighbour];
        if (neighbourDist < trgDist && neighbour != src) {
            auto path = currentPath;
            path.push_front(neighbour);

            getAllShortestPaths(shortestPaths, src, neighbour, distances, path);
        }
        else if (neighbour == src) {
            auto path = currentPath;
            path.push_front(neighbour);

            shortestPaths.push_front(path);
        }
    }
}

std::list<cTopology::Node *> OpenFlowGraphAnalyzer::getShortestPath(cTopology::Node * src, cTopology::Node * trg) {
    std::list<cTopology::Node *> result = std::list<cTopology::Node *>();

    std::map<cTopology::Node *, bool> visited = std::map<cTopology::Node *, bool>();
    std::map<cTopology::Node *, int> dist = std::map<cTopology::Node *, int>();
    std::map<cTopology::Node *, cTopology::Node *> prev = std::map<cTopology::Node *, cTopology::Node *>();

    priority_queue<pair<cTopology::Node*, int>, vector<pair<cTopology::Node*, int>>, compNodeInt> q;

    //init verticies
    for (int i = 0; i < topo.getNumNodes(); i++) {
        cTopology::Node * tmpNode = topo.getNode(i);
        if (tmpNode == src) {
            continue;
        }
        q.push(pair<cTopology::Node *, int>(tmpNode, std::numeric_limits<int>::max()));
        dist[tmpNode] = std::numeric_limits<int>::max();
        prev[tmpNode] = NULL;
    }

    //init src
    q.push(pair<cTopology::Node *, int>(src, 0));
    dist[src] = 0;
    prev[src] = NULL;

    cTopology::Node * u = NULL;
    while (!q.empty()) {

        u = q.top().first;
        q.pop();

        if (visited.count(u) > 0) {
            continue;
        }

        int alt;

        for (int i = 0; i < u->getNumOutLinks(); i++) {
            //ignore control plane
            if (strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                continue;
            }

     ////////////fuer LinkRemover
            if (!(u->getLinkOut(i)->isEnabled())) {
                continue;
            }
     ////////////////////////////

            if (visited.count(u->getLinkOut(i)->getRemoteNode()) <= 0) {
                alt = dist[u] + 1;
                if (alt < dist[u->getLinkOut(i)->getRemoteNode()]) {
                    dist[u->getLinkOut(i)->getRemoteNode()] = alt;
                    prev[u->getLinkOut(i)->getRemoteNode()] = u;
                    q.push(pair<cTopology::Node *, int>(u->getLinkOut(i)->getRemoteNode(), alt));
                }
            }
        }

        visited[u] = true;
    }

    cTopology::Node * tempTrg = trg;
    while (prev[tempTrg] != NULL) {
        result.push_back(tempTrg);
        tempTrg = prev[tempTrg];
    }
    result.push_back(tempTrg);

    if (tempTrg != src) {
        result.clear();
    }

    return result;
}

void OpenFlowGraphAnalyzer::finish() {
    // record statistics
    recordScalar("minPathLength", minPathLength);
    recordScalar("maxPathLength", maxPathLength);
    recordScalar("avgPathLength", avgPathLength);
    recordScalar("avgNumSwitchLinks", avgNumSwitchLinks);
    recordScalar("numClients", numClientNodes);
    recordScalar("numSwitches", numSwitchNodes);
    recordScalar("numPaths", computedPaths.size());

    std::map<std::string, int>::iterator iterMap;
    for (iterMap = swMap.begin(); iterMap != swMap.end(); iterMap++) {
        recordScalar(("nodeInNumPaths-" + iterMap->first).c_str(), iterMap->second);
    }
    for (iterMap = clMap.begin(); iterMap != clMap.end(); iterMap++) {
        recordScalar(("nodeInNumPaths-" + iterMap->first).c_str(), iterMap->second);
    }
    recordScalar("eccentricity", eccentricity);
    recordScalar("radius", radius);
    recordScalar("diameter", diameter);
    recordScalar("cpd", cpd);
    recordScalar("assortativity", assortativity);
    recordScalar("vertexConnectivity", vertexConnectivity);
    recordScalar("edgeConnectivity", edgeConnectivity);
    recordScalar("vertexPersistence", vertexPersistence);
    recordScalar("edgePersistence", edgePersistence);
    std::map<int, int>::iterator iter;
    for (iter = nodeDegreeDistribution.begin(); iter != nodeDegreeDistribution.end(); iter++) {
        recordScalar(("nodesWithDegree-" + std::to_string(iter->first)).c_str(), iter->second);
    }
    for (iter = hopCountDistribution.begin(); iter != hopCountDistribution.end(); iter++) {
        recordScalar(("pathsWithHopCount-" + std::to_string(iter->first)).c_str(), iter->second);
    }
    for (auto iter = closenesses.begin(); iter != closenesses.end(); iter++) {
        recordScalar(("closenessOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
    }
    for (auto iter = farnesses.begin(); iter != farnesses.end(); iter++) {
        recordScalar(("farnessOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
    }
    for (auto iter = betweennessesNormalized.begin(); iter != betweennessesNormalized.end(); iter++) {
        recordScalar(("betweennessOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
    }
    recordScalar("globalClusteringCoefficient", globalClusteringCoefficient);
    double i = 1.0;
    for (auto iter = graphExpansions.begin(); iter != graphExpansions.end(); iter++) {
        recordScalar(("graphExpansion-" + std::to_string(i * 1.0/(double) graphExpansions.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = richClubCoefficients.begin(); iter != richClubCoefficients.end(); iter++) {
        recordScalar(("richClubCoefficient-" + std::to_string(i * 1.0/(double) richClubCoefficients.size()) + "OfNodes").c_str(), *iter);
        i++;
    }
    recordScalar("averageNrOfNodeDistinctPaths", averageNrOfNodeDistinctPaths);
    recordScalar("averageNrOfEdgeDistinctPaths", averageNrOfEdgeDistinctPaths);
    recordScalar("averageCloseness", averageCloseness);
    recordScalar("averageFarness", averageFarness);
    recordScalar("averageBetweenness", averageBetweenness);
    recordScalar("avgPathDelay", avgPathDelay);
}

void OpenFlowGraphAnalyzer::handleMessage(cMessage *msg) {
    error("this module doesn't handle messages, it runs only in initialize()");
}
