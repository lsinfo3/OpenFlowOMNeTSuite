#include "OpenFlowGraphAnalyzer.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <numeric>
#include "LinkRemoverModule.h"
#include "ctopology.h"
#include <cmath>
#include <regex>
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
// Function to calculate
// mean of data.
float OpenFlowGraphAnalyzer::mean(std::list<double> data, int n) {
    float sum = 0;
    std::list<double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        sum = sum + *it;
    }
    return sum / n;
}

float OpenFlowGraphAnalyzer::sd(std::list<double> data, int n){
    float sum = 0;
    float mw = mean(data, n);
    std::list<double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        sum = sum + pow((*it - mw),2);
    }
    return sqrt(sum / n);
}

float OpenFlowGraphAnalyzer::var(std::list<double> data, int n){
    float sum = 0;
    float mw = mean(data, n);
    std::list<double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        sum = sum + pow((*it - mw),2);
    }
    return sum / n;
}

float OpenFlowGraphAnalyzer::skew(std::list<double> data, int n){
    float sum = 0;
    float mw = mean(data, n);
    float stdev = sd(data,n);
    std::list<double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        sum = sum + pow((*it - mw)/stdev,3);
    }
    return sum / n;
}

float OpenFlowGraphAnalyzer::kurt(std::list<double> data, int n){
    float sum = 0;
    float mw = mean(data, n);
    float stdev = sd(data,n);
    std::list<double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        sum = sum + pow((*it - mw)/stdev,4);
    }
    return sum / n;
}

float OpenFlowGraphAnalyzer::min(std::list<double> data){
     return *std::min_element(data.begin(), data.end());
}

float OpenFlowGraphAnalyzer::max(std::list<double> data){
    return *std::max_element(data.begin(), data.end());
}

float OpenFlowGraphAnalyzer::median(std::list<double> data, int n){
    data.sort();
    double med;
    auto it = data.begin();

    if(data.size() % 2 == 0 ) {
        for(int i = 0 ; i < n / 2 ; i ++ ) {
            it++;
        }
        med = ( (double)*it + *--it ) / 2;

    } else {
        for( int i = 0 ; i < n / 2 ; i ++ ) {
            it++;
        }
        med = *it;
    }
    return med;
}


float OpenFlowGraphAnalyzer::mode(std::list<double> data, int n){
data.sort();
auto modes = std::map<float, int>();

for (auto iter = data.begin(); iter != data.end(); iter++) {
    auto it = modes.find(*iter);
    if (it != modes.end()) {
       int old = it->second;
       it->second = old + 1;
     }
    else {
       modes.insert(std::pair<float, int>(*iter, 1));
    }
}
int currentMode_count = 0;
float currentMode = -999.999;
for (auto iter = modes.begin(); iter !=modes.end(); iter++) {
    int count = iter->second;
    if (count >= currentMode_count) {
        currentMode = iter->first;
        currentMode_count = count;
    }
}

return currentMode;
}




void OpenFlowGraphAnalyzer::initialize(int stage) {
    if (stage == 4) {

        const char *NodeType = par("NodeType");
        considerOnlyEndToEnd = par("considerOnlyEndToEnd");
        std::vector<std::string> nodeTypes = cStringTokenizer(NodeType).asVector();
        topo.extractByNedTypeName(nodeTypes);

        // For weighted Paths
        std::vector<std::string> nodeTypes_weighted = cStringTokenizer("openflow.nodes.DistanceChannel openflow.nodes.Open_Flow_Domain").asVector();
        topo_weighted.extractByNedTypeName(nodeTypes_weighted);



         std::vector<std::string> nodeTypes_complete = cStringTokenizer("openflow.openflow.switch.OF_Switch inet.nodes.inet.StandardHost openflow.openflow.controller.Open_Flow_Controller").asVector();
         topo_complete.extractByNedTypeName(nodeTypes_complete);

         auto switchMapping = std::map<std::string, std::list<std::string>>();

         nrOfSwitches = 0;
         switchesPerController = std::map<std::string, double>();
         for (int i = 0; i < topo_complete.getNumNodes(); i++) {
             auto potentialSwitch = topo_complete.getNode(i);
             if (strstr(potentialSwitch->getModule()->getFullPath().c_str(), "switch") == NULL && strstr(potentialSwitch->getModule()->getFullPath().c_str(), "Switch") == NULL) {
                 continue;
             }

             nrOfSwitches++;
             auto controllerToConnect = potentialSwitch->getModule()->par("connectAddress").str();
             controllerToConnect = std::regex_replace(controllerToConnect, std::regex("\""), "");


             auto it2 = switchMapping.find(controllerToConnect);
             if (it2 != switchMapping.end()) {
                 it2->second.push_back(std::regex_replace(potentialSwitch->getModule()->getFullPath().c_str(), std::regex("\\.open_flow_switch.OF_Switch"), ""));
             } else {
                 auto newlist = std::list<std::string>();
                 newlist.push_back(std::regex_replace(potentialSwitch->getModule()->getFullPath().c_str(), std::regex("\\.open_flow_switch.OF_Switch"), ""));
                 //std::cout << std::regex_replace(potentialSwitch->getModule()->getFullPath().c_str(), std::regex("\.open_flow_switch.OF_Switch"), "") << endl;
                 switchMapping.insert(std::pair<std::string, std::list<std::string>>(controllerToConnect, newlist));
             }
             //switchMapping.insert(std::pair<cTopology::Node *, std::string>(potentialSwitch,controllerToConnect));

             auto it = switchesPerController.find(controllerToConnect);
             if (it != switchesPerController.end()) {
                 int old = it->second;
                 it->second = old + 1;

             }

             else {
                 switchesPerController.insert(std::pair<std::string, double>(controllerToConnect, 1));
             }
         }

         topo_new.extractByModulePath(cStringTokenizer("**.etherSwitch **controller1 **controller2 **controller3 **controller4 **controller5 **root").asVector());
         auto controllerPlacement = std::map<std::string, std::string>();
         std::string rootPlacement;
         for (int i = 0; i < topo_new.getNumNodes(); i++) {
             auto potentialPlacement = topo_new.getNode(i);

             if (strstr(potentialPlacement->getModule()->getFullPath().c_str(), "controller") != NULL) {
                 //auto placement = potentialPlacement->getModule()->getFullPath().c_str()
                 auto name =  std::regex_replace(potentialPlacement->getLinkOut(0)->getRemoteNode()->getModule()->getFullPath().c_str(), std::regex("\\.etherSwitch"), "");
                 //std::cout << name << endl;
                 auto cname = std::regex_replace(potentialPlacement->getModule()->getFullPath().c_str(),std::regex(".*\\."),"");
                 //std::cout << cname << endl;
                 controllerPlacement.insert(std::pair<std::string, std::string>(cname, name));
                 //std::cout << potentialPlacement->getModule()->getFullPath().c_str() << endl;
                 //std::cout << potentialPlacement->getLinkOut(0)->getRemoteNode()->getModule()->getFullPath().c_str() << endl;
             }

             if (strstr(potentialPlacement->getModule()->getFullPath().c_str(), "root") != NULL) {
                 rootPlacement = std::regex_replace(potentialPlacement->getLinkOut(0)->getRemoteNode()->getModule()->getFullPath().c_str(), std::regex("\\.etherSwitch"), "");
                 //std::cout << potentialPlacement->getModule()->getFullPath().c_str() << endl;
                 //std::cout << potentialPlacement->getLinkOut(0)->getRemoteNode()->getModule()->getFullPath().c_str() << endl;
             }
         }


        std::list<double> c2rlatencies;
        std::map<std::string, std::string>::iterator it4;

        cTopology::Node* rootNode;
        for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
            rootNode = topo_weighted.getNode(i);
            if (rootNode->getModule()->getFullPath().c_str() == rootPlacement) {
                break;
            }
        }

        for (it4 = controllerPlacement.begin();it4 != controllerPlacement.end(); it4++) {
            auto cname = it4->first;
            auto swname = it4->second;

                cTopology::Node* trg;
                for (int j = 0; j < topo_weighted.getNumNodes(); j++) {
                    trg = topo_weighted.getNode(j);
                    if (trg->getModule()->getFullPath().c_str() == swname) {
                        //std::cout << rootNode->getModule()->getFullPath().c_str()<< endl;
                        //std::cout << trg->getModule()->getFullPath().c_str() << endl;
                        double pathWeight = getWeightedShortestPaths(rootNode, trg);
                        //std::cout << pathWeight << endl;
                        c2rlatencies.push_back(pathWeight);
                    }
                }
            }



         meanC2RL = mean(c2rlatencies, c2rlatencies.size());
         sdC2RL = sd(c2rlatencies, c2rlatencies.size());
         varC2RL = var(c2rlatencies, c2rlatencies.size());
         skewC2RL = skew(c2rlatencies, c2rlatencies.size());
         kurtC2RL = kurt(c2rlatencies, c2rlatencies.size());
         minC2RL = min(c2rlatencies);
         maxC2RL = max(c2rlatencies);
         medianC2RL = median(c2rlatencies, c2rlatencies.size());
         modeC2RL = mode(c2rlatencies, c2rlatencies.size());
         //std::cout << meanC2RL << endl;

        std::list<double> c2clatencies;
        std::map<std::string, std::string>::iterator it2;
        for (it2 = controllerPlacement.begin(); it2 != controllerPlacement.end(); it2++) {
            auto cname = it2->first;
            auto swname = it2->second;

            cTopology::Node* src;
            for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
                src = topo_weighted.getNode(i);
                if (src->getModule()->getFullPath().c_str() == swname) {
                    break;
                }
            }
            std::map<std::string, std::string>::iterator it3;
            for (it3 = controllerPlacement.begin(); it3 != controllerPlacement.end(); it3++) {
                auto cname_trg = it3->first;
                auto swname_trg = it3->second;

                if (cname_trg == cname) {
                    continue;
                }
                cTopology::Node* trg;
                for (int j = 0; j < topo_weighted.getNumNodes(); j++) {
                    trg = topo_weighted.getNode(j);
                    if (trg->getModule()->getFullPath().c_str() == swname_trg) {
                        //std::cout << src->getModule()->getFullPath().c_str() << endl;
                        //std::cout << trg->getModule()->getFullPath().c_str() << endl;
                        double pathWeight = getWeightedShortestPaths(src, trg);
                        //std::cout << pathWeight << endl;
                        c2clatencies.push_back(pathWeight);
                    }
                }
            }
        }


        meanC2CL = mean(c2clatencies, c2clatencies.size());
        sdC2CL = sd(c2clatencies, c2clatencies.size());
        varC2CL = var(c2clatencies, c2clatencies.size());
        skewC2CL = skew(c2clatencies, c2clatencies.size());
        kurtC2CL = kurt(c2clatencies, c2clatencies.size());
        minC2CL = min(c2clatencies);
        maxC2CL = max(c2clatencies);
        medianC2CL = median(c2clatencies, c2clatencies.size());
        modeC2CL = mode(c2clatencies, c2clatencies.size());
        //std::cout << meanC2CL << endl;

        std::list<double> c2slatencies;
        std::map<std::string, std::list<std::string>>::iterator it;
        for (it = switchMapping.begin(); it != switchMapping.end(); it++) {
            std::string cname = it->first;
            std::cout << cname << endl;
            std::list<std::string> swnames = it->second;

            std::string cplacement = controllerPlacement.find(cname)->second;
            std::cout << cplacement << endl;

            cTopology::Node* trg;
            for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
                trg = topo_weighted.getNode(i);
                if (trg->getModule()->getFullPath().c_str() == cplacement) {
                    break;
                }
            }

            for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
                auto src = topo_weighted.getNode(i);
                auto bla = std::find(swnames.begin(), swnames.end(), src->getModule()->getFullPath().c_str());
                if (bla == swnames.end()) {
                    continue;
                }

                    double pathWeight = getWeightedShortestPaths(src, trg);
                    std::cout << pathWeight << endl;
                    c2slatencies.push_back(pathWeight);
                }
            }


            meanC2SL = mean(c2slatencies, c2slatencies.size());
            sdC2SL = sd(c2slatencies, c2slatencies.size());
            varC2SL = var(c2slatencies, c2slatencies.size());
            skewC2SL = skew(c2slatencies, c2slatencies.size());
            kurtC2SL = kurt(c2slatencies, c2slatencies.size());
            minC2SL = min(c2slatencies);
            std::cout << "#########" << endl;
            std::cout << minC2SL << endl;
            std::cout << "#########" << endl;
            maxC2SL = max(c2slatencies);
            medianC2SL = median(c2slatencies, c2slatencies.size());
            modeC2SL = mode(c2slatencies, c2slatencies.size());
            //std::cout << meanC2SL << endl;






         nrOfControllers = 0;
         for (int i = 0; i < topo_complete.getNumNodes(); i++) {
             if (strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "controller") == NULL && strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "Controller") == NULL) {
                 continue;
             }
             nrOfControllers++;
         }

         nrOfClients= 0;
         for (int i = 0; i < topo_complete.getNumNodes(); i++) {
             if (strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "client") == NULL && strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "Client") == NULL && strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "host") == NULL && strstr(topo_complete.getNode(i)->getModule()->getFullPath().c_str(), "Host") == NULL) {
                 continue;
             }
             nrOfClients++;
         }

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
        std::list<double> s2slatencies;
        for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
            auto node = topo_weighted.getNode(i);
            for (int j = 0; j < node->getNumOutLinks(); j++) {
                       //ignore control plane

                       if (strstr(node->getLinkOut(j)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(node->getLinkOut(j)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
                           continue;
                       }
                       if (node->getLinkOut(j)->getLocalGate()->getChannel() == NULL) {
                           continue;
                       }

                       if (node->getLinkOut(j)->getLocalGate()->getChannel()->getNumParams() < 7) {
                           continue;
                       }
                ////////////fuer LinkRemover
                       if (!(node->getLinkOut(j)->isEnabled())) {
                           continue;
                       }
                ////////////////////////////
                       double s2slatency = node->getLinkOut(j)->getLocalGate()->getChannel()->par(1); // Hier ist der spezifizierte Delay gespeichtert -> deswegen funzt es vorerst nur für DistanceChannels
                       s2slatencies.push_back(s2slatency);
            }
        }
        int s2scount = s2slatencies.size();
        meanS2SL = mean(s2slatencies, s2scount);
        sdS2SL = sd(s2slatencies, s2scount);
        varS2SL = var(s2slatencies, s2scount);
        skewS2SL = skew(s2slatencies, s2scount);
        kurtS2SL = kurt(s2slatencies, s2scount);
        minS2SL = min(s2slatencies);
        maxS2SL = max(s2slatencies);
        medianS2SL = median(s2slatencies, s2scount);
        modeS2SL = mode(s2slatencies, s2scount);

        // Weighted Paths -> works only for Topologies with DistanceChannels as Links
        // WEIGHTED Radius, Durchmesser, Ekzentrizitaet berechnen
        double pathCount = 0.0;
        std::list<double> allWeightedShortestPaths;

        std::list<double> nodeEccentricities_weighted;
        closenesses_weighted = std::map<cTopology::Node *, double>();

        std::list<double> e2elatencies;
        std::list<double> farnesses_simple_weighted;
        std::list<double> closenesses_simple_weighted;
        std::list<double> farnesses_norm_weighted;
        std::list<double> closenesses_norm_weighted;
        for (int i = 0; i < topo_weighted.getNumNodes(); i++) {

               auto src = topo_weighted.getNode(i);
               double max = 0;
               double farness_weighted = 0.0;

                 for (int j = 0; j < topo_weighted.getNumNodes(); j++) {

                         if (i == j) {
                             continue;
                         }

                         auto trg = topo_weighted.getNode(j);

                         double pathWeight = getWeightedShortestPaths(src, trg);
                         e2elatencies.push_back(pathWeight);
                         farness_weighted = farness_weighted + pathWeight;
                         if (farness_weighted > max) {
                             max = farness_weighted;
                         }
                         pathCount++;
                 }
                 // std::cout << max << endl;
                 // e2elatencies.push_back(farness_weighted);
                 farnesses_simple_weighted.push_back(farness_weighted);
                 farnesses_norm_weighted.push_back(farness_weighted/ ((double) nrOfSwitches - 1.0));
                 closenesses_simple_weighted.push_back(1.0/farness_weighted);
                 closenesses_norm_weighted.push_back(1.0/farness_weighted * ((double) nrOfSwitches - 1.0));

                 double farnessNormalized_weighted = farness_weighted / ((double) nrOfSwitches - 1.0);
                 farnesses_weighted.insert(std::pair<cTopology::Node *, double>(topo_weighted.getNode(i), farnessNormalized_weighted));
                 double closeness_weighted = 1.0/farness_weighted * ((double) nrOfSwitches - 1.0);
                 closenesses_weighted.insert(std::pair<cTopology::Node *, double>(topo_weighted.getNode(i), closeness_weighted));
                 nodeEccentricities_weighted.push_back(max);
             }
         int e2elcount = e2elatencies.size();
         meanE2EL = mean(e2elatencies, e2elcount);
         sdE2EL = sd(e2elatencies, e2elcount);
         varE2EL = var(e2elatencies, e2elcount);
         skewE2EL = skew(e2elatencies, e2elcount);
         kurtE2EL = kurt(e2elatencies, e2elcount);
         minE2EL = min(e2elatencies);
         maxE2EL = max(e2elatencies);
         medianE2EL = median(e2elatencies, e2elcount);
         modeE2EL = mode(e2elatencies, e2elcount);

         int eccCount_weighted = nodeEccentricities_weighted.size();
         meanEccentricity_weighted = mean(nodeEccentricities_weighted, eccCount_weighted);
         sdEccentricity_weighted = sd(nodeEccentricities_weighted, eccCount_weighted);
         varEccentricity_weighted = var(nodeEccentricities_weighted, eccCount_weighted);
         skewEccentricity_weighted = skew(nodeEccentricities_weighted, eccCount_weighted);
         kurtEccentricity_weighted = kurt(nodeEccentricities_weighted, eccCount_weighted);
         minEccentricity_weighted = min(nodeEccentricities_weighted);
         maxEccentricity_weighted = max(nodeEccentricities_weighted);
         medianEccentricity_weighted = median(nodeEccentricities_weighted, eccCount_weighted);
         modeEccentricity_weighted = mode(nodeEccentricities_weighted, eccCount_weighted);

         int farCount_weighted = farnesses_simple_weighted.size();
         meanFarness_weighted = mean(farnesses_simple_weighted, farCount_weighted);
         sdFarness_weighted = sd(farnesses_simple_weighted, farCount_weighted);
         varFarness_weighted = var(farnesses_simple_weighted, farCount_weighted);
         skewFarness_weighted = skew(farnesses_simple_weighted, farCount_weighted);
         kurtFarness_weighted = kurt(farnesses_simple_weighted, farCount_weighted);
         minFarness_weighted = min(farnesses_simple_weighted);
         maxFarness_weighted = max(farnesses_simple_weighted);
         medianFarness_weighted = median(farnesses_simple_weighted, farCount_weighted);
         modeFarness_weighted = mode(farnesses_simple_weighted, farCount_weighted);

         meanFarnessCentrality_weighted = mean(farnesses_norm_weighted, farCount_weighted);
         sdFarnessCentrality_weighted = sd(farnesses_norm_weighted, farCount_weighted);
         varFarnessCentrality_weighted = var(farnesses_norm_weighted, farCount_weighted);
         skewFarnessCentrality_weighted = skew(farnesses_norm_weighted, farCount_weighted);
         kurtFarnessCentrality_weighted = kurt(farnesses_norm_weighted, farCount_weighted);
         minFarnessCentrality_weighted = min(farnesses_norm_weighted);
         maxFarnessCentrality_weighted = max(farnesses_norm_weighted);
         medianFarnessCentrality_weighted = median(farnesses_norm_weighted, farCount_weighted);
         modeFarnessCentrality_weighted = mode(farnesses_norm_weighted, farCount_weighted);

         meanCloseness_weighted = mean(closenesses_simple_weighted, farCount_weighted);
         sdCloseness_weighted = sd(closenesses_simple_weighted, farCount_weighted);
         varCloseness_weighted = var(closenesses_simple_weighted, farCount_weighted);
         skewCloseness_weighted = skew(closenesses_simple_weighted, farCount_weighted);
         kurtCloseness_weighted = kurt(closenesses_simple_weighted, farCount_weighted);
         minCloseness_weighted = min(closenesses_simple_weighted);
         maxCloseness_weighted = max(closenesses_simple_weighted);
         medianCloseness_weighted = median(closenesses_simple_weighted, farCount_weighted);
         modeCloseness_weighted = mode(closenesses_simple_weighted, farCount_weighted);

         meanClosenessCentrality_weighted = mean(closenesses_norm_weighted, farCount_weighted);
         sdClosenessCentrality_weighted = sd(closenesses_norm_weighted, farCount_weighted);
         varClosenessCentrality_weighted = var(closenesses_norm_weighted, farCount_weighted);
         skewClosenessCentrality_weighted = skew(closenesses_norm_weighted, farCount_weighted);
         kurtClosenessCentrality_weighted = kurt(closenesses_norm_weighted, farCount_weighted);
         minClosenessCentrality_weighted = min(closenesses_norm_weighted);
         maxClosenessCentrality_weighted = max(closenesses_norm_weighted);
         medianClosenessCentrality_weighted = median(closenesses_norm_weighted, farCount_weighted);
         modeClosenessCentrality_weighted = mode(closenesses_norm_weighted, farCount_weighted);

         //int sum = std::accumulate(nodeEccentricities.begin(), nodeEccentricities.end(), 0.0);
         //eccentricity = (double) sum / (double) nodeEccentricities.size() - 1.0;
         radius_weighted = *std::min_element(nodeEccentricities_weighted.begin(), nodeEccentricities_weighted.end());
         diameter_weighted = *std::max_element(nodeEccentricities_weighted.begin(), nodeEccentricities_weighted.end());

         //std::cout << radius_weighted << endl;

        // Radius, Durchmesser, Ekzentrizitaet berechnen
        std::list<double> nodeEccentricities;
        hopCountDistribution = std::map<int, int>();
        closenesses = std::map<cTopology::Node *, double>();

        std::list<double> hopCounts_simple;
        std::list<double> farnesses_simple;
        std::list<double> closenesses_simple;
        std::list<double> farnesses_norm;
        std::list<double> closenesses_norm;
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
                hopCounts_simple.push_back(shortestPathSize);
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
            //hopCounts_simple.push_back(farness);
            farnesses_simple.push_back(farness);
            farnesses_norm.push_back(farness/ ((double) nrOfSwitches - 1.0));
            closenesses_simple.push_back(1.0/farness);
            closenesses_norm.push_back(1.0/farness * ((double) nrOfSwitches - 1.0));

            double farnessNormalized = farness / ((double) nrOfSwitches - 1.0);
            farnesses.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), farnessNormalized));
            double closeness = 1.0/farness * ((double) nrOfSwitches - 1.0);
            closenesses.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), closeness));
            nodeEccentricities.push_back(max);
        }

        int hopCountCount = hopCounts_simple.size();
        meanHopCount = mean(hopCounts_simple, hopCountCount);
        sdHopCount = sd(hopCounts_simple, hopCountCount);
        varHopCount = var(hopCounts_simple, hopCountCount);
        skewHopCount = skew(hopCounts_simple, hopCountCount);
        kurtHopCount = kurt(hopCounts_simple, hopCountCount);
        minHopCount = min(hopCounts_simple);
        maxHopCount = max(hopCounts_simple);
        medianHopCount = median(hopCounts_simple, hopCountCount);
        modeHopCount = mode(hopCounts_simple, hopCountCount);

        int eccCount = nodeEccentricities.size();
        meanEccentricity = mean(nodeEccentricities, eccCount);
        sdEccentricity = sd(nodeEccentricities, eccCount);
        varEccentricity = var(nodeEccentricities, eccCount);
        skewEccentricity = skew(nodeEccentricities, eccCount);
        kurtEccentricity = kurt(nodeEccentricities, eccCount);
        minEccentricity = min(nodeEccentricities);
        maxEccentricity = max(nodeEccentricities);
        medianEccentricity = median(nodeEccentricities, eccCount);
        modeEccentricity = mode(nodeEccentricities, eccCount);

        int farCount = farnesses_simple.size();
        meanFarness = mean(farnesses_simple, farCount);
        sdFarness = sd(farnesses_simple, farCount);
        varFarness = var(farnesses_simple, farCount);
        skewFarness = skew(farnesses_simple, farCount);
        kurtFarness = kurt(farnesses_simple, farCount);
        minFarness = min(farnesses_simple);
        maxFarness = max(farnesses_simple);
        medianFarness = median(farnesses_simple, farCount);
        modeFarness = mode(farnesses_simple, farCount);

        meanFarnessCentrality = mean(farnesses_norm, farCount);
        sdFarnessCentrality = sd(farnesses_norm, farCount);
        varFarnessCentrality = var(farnesses_norm, farCount);
        skewFarnessCentrality = skew(farnesses_norm, farCount);
        kurtFarnessCentrality = kurt(farnesses_norm, farCount);
        minFarnessCentrality = min(farnesses_norm);
        maxFarnessCentrality = max(farnesses_norm);
        medianFarnessCentrality = median(farnesses_norm, farCount);
        modeFarnessCentrality = mode(farnesses_norm, farCount);

        meanCloseness = mean(closenesses_simple, farCount);
        sdCloseness = sd(closenesses_simple, farCount);
        varCloseness = var(closenesses_simple, farCount);
        skewCloseness = skew(closenesses_simple, farCount);
        kurtCloseness = kurt(closenesses_simple, farCount);
        minCloseness = min(closenesses_simple);
        maxCloseness = max(closenesses_simple);
        medianCloseness = median(closenesses_simple, farCount);
        modeCloseness = mode(closenesses_simple, farCount);

        meanClosenessCentrality = mean(closenesses_norm, farCount);
        sdClosenessCentrality = sd(closenesses_norm, farCount);
        varClosenessCentrality = var(closenesses_norm, farCount);
        skewClosenessCentrality = skew(closenesses_norm, farCount);
        kurtClosenessCentrality = kurt(closenesses_norm, farCount);
        minClosenessCentrality = min(closenesses_norm);
        maxClosenessCentrality = max(closenesses_norm);
        medianClosenessCentrality = median(closenesses_norm, farCount);
        modeClosenessCentrality = mode(closenesses_norm, farCount);

        //int sum = std::accumulate(nodeEccentricities.begin(), nodeEccentricities.end(), 0.0);
        //eccentricity = (double) sum / (double) nodeEccentricities.size() - 1.0;
        radius = *std::min_element(nodeEccentricities.begin(), nodeEccentricities.end()) - 1;
        diameter = *std::max_element(nodeEccentricities.begin(), nodeEccentricities.end()) - 1;


        // Knotengrade (ohne Client-Knoten und -Links) berechnen
        nodeDegreeDistribution = std::map<int, int>();
        std::list<double> nodeDegrees_simple;
        std::list<double> degreeCentralities;
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
            nodeDegrees_simple.push_back(degree);
            degreeCentralities.push_back(degree/nrOfSwitches);

            auto it = nodeDegreeDistribution.find(degree);
            if (it != nodeDegreeDistribution.end()) {
                int old = it->second;
                it->second = old + 1;
            }
            else {
                nodeDegreeDistribution.insert(std::pair<int, int>(degree, 1));
            }
        }
        int degreeCount = nodeDegrees_simple.size();
        meanDegree = mean(nodeDegrees_simple, degreeCount);
        sdDegree = sd(nodeDegrees_simple, degreeCount);
        varDegree = var(nodeDegrees_simple, degreeCount);
        skewDegree = skew(nodeDegrees_simple, degreeCount);
        kurtDegree = kurt(nodeDegrees_simple, degreeCount);
        minDegree = min(nodeDegrees_simple);
        maxDegree = max(nodeDegrees_simple);
        medianDegree = median(nodeDegrees_simple, degreeCount);
        modeDegree = mode(nodeDegrees_simple, degreeCount);

        meanDegreeCentrality = mean(degreeCentralities, degreeCount);
        sdDegreeCentrality = sd(degreeCentralities, degreeCount);
        varDegreeCentrality = var(degreeCentralities, degreeCount);
        skewDegreeCentrality = skew(degreeCentralities, degreeCount);
        kurtDegreeCentrality = kurt(degreeCentralities, degreeCount);
        minDegreeCentrality = min(degreeCentralities);
        maxDegreeCentrality = max(degreeCentralities);
        medianDegreeCentrality = median(degreeCentralities, degreeCount);
        modeDegreeCentrality = mode(degreeCentralities, degreeCount);

        // Graph Centralization berechnen
        graphCentralization = 0;
        for (auto it = degreeCentralities.begin(); it != degreeCentralities.end(); it++) {
            graphCentralization = graphCentralization + (maxDegreeCentrality - *it) / ((nrOfSwitches - 2.0));
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
               std::list<double> betweennesses;
               std::list<double> betweennessCentralities;
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
                   betweennessCentralities.push_back(betweenness/norm_factor);
                   betweennessesNormalized.insert(std::pair<cTopology::Node *, double>(topo.getNode(i), betweenness/norm_factor));
               }

               int betCount = betweennesses.size();
               meanBetweenness = mean(betweennesses, betCount);
               sdBetweenness = sd(betweennesses, betCount);
               varBetweenness = var(betweennesses, betCount);
               skewBetweenness = skew(betweennesses, betCount);
               kurtBetweenness = kurt(betweennesses, betCount);
               minBetweenness = min(betweennesses);
               maxBetweenness = max(betweennesses);
               medianBetweenness = median(betweennesses, betCount);
               modeBetweenness = mode(betweennesses, betCount);

               meanBetweennessCentrality = mean(betweennessCentralities, betCount);
               sdBetweennessCentrality = sd(betweennessCentralities, betCount);
               varBetweennessCentrality = var(betweennessCentralities, betCount);
               skewBetweennessCentrality = skew(betweennessCentralities, betCount);
               kurtBetweennessCentrality = kurt(betweennessCentralities, betCount);
               minBetweennessCentrality = min(betweennessCentralities);
               maxBetweennessCentrality = max(betweennessCentralities);
               medianBetweennessCentrality = median(betweennessCentralities, betCount);
               modeBetweennessCentrality = mode(betweennessCentralities, betCount);

        // Central Point of Dominance berechnen
        cpd = 0;
        for (auto it = betweennesses.begin(); it != betweennesses.end(); it++) {
            cpd = cpd + (maxBetweenness / norm_factor - *it / norm_factor) / ((nrOfSwitches - 1.0));
        }


        // WEIGHTED BETWEENNESS
        // Fuer alle Knotenpaare ALLE kuerzestenen Wege berechnen
         allShortestPaths = std::map<cTopology::Node *, std::map<cTopology::Node *, std::list<std::list<cTopology::Node * >>>>();
         for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
             if (strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                 continue;
             }
             auto dist = getAllWeightedDistances(topo_weighted.getNode(i));

             auto map1 = std::map<cTopology::Node *, std::list<std::list<cTopology::Node *>>>();
             for (int j = 0; j < topo_weighted.getNumNodes(); j++) {

                 if (strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                     continue;
                 }
                 if (i == j) {
                     continue;
                 }
                 std::list<std::list<cTopology::Node *>> shortestPaths = std::list<std::list<cTopology::Node *>>();
                 std::list<cTopology::Node *> currentPath = std::list<cTopology::Node *>();
                 currentPath.push_front(topo_weighted.getNode(j));
                 getAllWeightedShortestPaths(shortestPaths, topo_weighted.getNode(i), topo_weighted.getNode(j), dist, currentPath);

                 auto pair1 = std::pair<cTopology::Node *, std::list<std::list<cTopology::Node *>>>(topo_weighted.getNode(j), shortestPaths);
                 map1.insert(pair1);


             }
             auto pair2 = std::pair<cTopology::Node *, std::map<cTopology::Node *, std::list<std::list<cTopology::Node *>>> >(topo_weighted.getNode(i), map1);
             allShortestPaths.insert(pair2);

         }

         // Betweenness -> im Paper wurde hier die Summe ber alle Knotenpaare in der Formel vergessen?
                std::list<double> betweennesses_weighted;
                std::list<double> betweennessCentralities_weighted;
                betweennessesNormalized_weighted = std::map<cTopology::Node *, double>();
                norm_factor = (nrOfSwitches - 1) * (nrOfSwitches - 2);
                for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
                    double betweenness_weighted = 0.0;
                    if (strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(), "host") != NULL) {
                        continue;
                    }
                    for (int j = 0; j < topo_weighted.getNumNodes(); j++) {
                        if (strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                            continue;
                        }
                        if (j == i) {
                            continue;
                        }

                        for (int k = 0; k < topo_weighted.getNumNodes(); k++) {
                            if (strstr(topo_weighted.getNode(k)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo_weighted.getNode(k)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo_weighted.getNode(k)->getModule()->getFullPath().c_str(), "host") != NULL) {
                                continue;
                            }
                            if (k == j || k == i) {
                                continue;
                            }

                            auto paths = allShortestPaths[topo_weighted.getNode(j)][topo_weighted.getNode(k)];
                            for (auto it = paths.begin(); it != paths.end(); it++) {
                                auto nodeInPath = std::find(it->begin(), it->end(), topo_weighted.getNode(i));
                                auto path = *it;
                              if (strstr(topo_weighted.getNode(j)->getModule()->getFullPath().c_str(),"Barabasi_Albert_imbalanced_geometric_low_4_KN.ofs_40") ) {

                                //std::cout << topo_weighted.getNode(k)->getModule()->getFullPath().c_str() << endl;
                                //std::cout << topo_weighted.getNode(j)->getModule()->getFullPath().c_str() << endl;
                                for (auto it2 = path.begin(); it2 != path.end(); it2++) {
                                        auto node = *it2;
                                        std::cout << node->getModule()->getFullPath().c_str() << endl;
                                   }
                                //std::cout << "###################" << endl;
                               }

                                if (nodeInPath != it->end()) {
//                                    if (strstr(topo_weighted.getNode(i)->getModule()->getFullPath().c_str(),"Barabasi_Albert_imbalanced_geometric_low_4_KN.ofs_19") != NULL) {
//                                        std::cout << topo_weighted.getNode(k)->getModule()->getFullPath().c_str() << endl;
//                                        std::cout << topo_weighted.getNode(i)->getModule()->getFullPath().c_str() << endl;
//                                        std::cout << topo_weighted.getNode(j)->getModule()->getFullPath().c_str() << endl;
//                                        std::cout << "###################" << endl;
//                                    }
                                    betweenness_weighted = betweenness_weighted + (1 / (double) paths.size());
                                }
                            }
                        }
                    }
                    betweennesses_weighted.push_back(betweenness_weighted);
                    betweennessCentralities_weighted.push_back(betweenness_weighted/norm_factor);
                    betweennessesNormalized_weighted.insert(std::pair<cTopology::Node *, double>(topo_weighted.getNode(i), betweenness_weighted/norm_factor));
                }


                int betCount_weighted = betweennesses_weighted.size();
                meanBetweenness_weighted = mean(betweennesses_weighted, betCount_weighted);
                sdBetweenness_weighted = sd(betweennesses_weighted, betCount_weighted);
                varBetweenness_weighted = var(betweennesses_weighted, betCount_weighted);
                skewBetweenness_weighted = skew(betweennesses_weighted, betCount_weighted);
                kurtBetweenness_weighted = kurt(betweennesses_weighted, betCount_weighted);
                minBetweenness_weighted = min(betweennesses_weighted);
                maxBetweenness_weighted = max(betweennesses_weighted);
                medianBetweenness_weighted = median(betweennesses_weighted, betCount_weighted);
                modeBetweenness_weighted = mode(betweennesses_weighted, betCount_weighted);

                meanBetweennessCentrality_weighted = mean(betweennessCentralities_weighted, betCount_weighted);
                sdBetweennessCentrality_weighted = sd(betweennessCentralities_weighted, betCount_weighted);
                varBetweennessCentrality_weighted = var(betweennessCentralities_weighted, betCount_weighted);
                skewBetweennessCentrality_weighted = skew(betweennessCentralities_weighted, betCount_weighted);
                kurtBetweennessCentrality_weighted = kurt(betweennessCentralities_weighted, betCount_weighted);
                minBetweennessCentrality_weighted = min(betweennessCentralities_weighted);
                maxBetweennessCentrality_weighted = max(betweennessCentralities_weighted);
                medianBetweennessCentrality_weighted = median(betweennessCentralities_weighted, betCount_weighted);
                modeBetweennessCentrality_weighted = mode(betweennessCentralities_weighted, betCount_weighted);


                cpd_weighted = 0;
                for (auto it = betweennesses_weighted.begin(); it != betweennesses_weighted.end(); it++) {
                    cpd_weighted = cpd_weighted + (maxBetweenness_weighted / norm_factor - *it / norm_factor) / ((nrOfSwitches - 1.0));
                }





        // Persistence
        std::list<int> nrOfDisjointPaths; // = alle disjoint paths <= Durchmesser
        std::list<double> maxFlows; // = alle disjoint paths
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

        int disjPathCount = maxFlows.size();
        meanEdgeDistinctPaths = mean(maxFlows, disjPathCount);
        sdEdgeDistinctPaths = sd(maxFlows, disjPathCount);
        varEdgeDistinctPaths = var(maxFlows, disjPathCount);
        skewEdgeDistinctPaths = skew(maxFlows, disjPathCount);
        kurtEdgeDistinctPaths = kurt(maxFlows, disjPathCount);
        minEdgeDistinctPaths = min(maxFlows);
        maxEdgeDistinctPaths = max(maxFlows);
        medianEdgeDistinctPaths = median(maxFlows, disjPathCount);
        modeEdgeDistinctPaths = mode(maxFlows, disjPathCount);

        edgeConnectivity = *std::min_element(maxFlows.begin(), maxFlows.end());

        std::list<int> nrOfNodeDisjointPaths; // = alle disjoint paths <= Durchmesser
        std::list<double> maxFlows2; // = alle disjoint paths
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


       int disjPathCount2 = maxFlows2.size();
       meanNodeDisjointPaths = mean(maxFlows2, disjPathCount2);
       sdNodeDisjointPaths = sd(maxFlows2, disjPathCount2);
       varNodeDisjointPaths = var(maxFlows2, disjPathCount2);
       skewNodeDisjointPaths = skew(maxFlows2, disjPathCount2);
       kurtNodeDisjointPaths = kurt(maxFlows2, disjPathCount2);
       minNodeDisjointPaths = min(maxFlows2);
       maxNodeDisjointPaths = max(maxFlows2);
       medianNodeDisjointPaths = median(maxFlows2, disjPathCount2);
       modeNodeDisjointPaths = mode(maxFlows2, disjPathCount2);

        vertexConnectivity = *std::min_element(maxFlows2.begin(), maxFlows2.end());

        // Clustering Coefficient
        std::map<cTopology::Node *, double> localClusteringCoefficients;
        std::list<double> localCoeffs;
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
            localCoeffs.push_back(localClusteringCoefficient);
            globalClusteringCoefficient += localClusteringCoefficient;
        }

        int coeffCount = localCoeffs.size();
        meanLocalClusteringCoefficient = mean(localCoeffs, coeffCount);
        sdLocalClusteringCoefficient = sd(localCoeffs, coeffCount);
        varLocalClusteringCoefficient = var(localCoeffs, coeffCount);
        skewLocalClusteringCoefficient = skew(localCoeffs, coeffCount);
        kurtLocalClusteringCoefficient = kurt(localCoeffs, coeffCount);
        minLocalClusteringCoefficient = min(localCoeffs);
        maxLocalClusteringCoefficient = max(localCoeffs);
        medianLocalClusteringCoefficient = median(localCoeffs, coeffCount);
        modeLocalClusteringCoefficient = mode(localCoeffs, coeffCount);

        globalClusteringCoefficient = globalClusteringCoefficient / ((double) localClusteringCoefficients.size());

        // Expansion
        int nrOfCalculations = 4;

        meanNodeExpansion = std::list<double>();
        sdNodeExpansion = std::list<double>();
        varNodeExpansion = std::list<double>();
        skewNodeExpansion = std::list<double>();
        kurtNodeExpansion = std::list<double>();
        minNodeExpansion = std::list<double>();
        maxNodeExpansion = std::list<double>();
        medianNodeExpansion = std::list<double>();
        modeNodeExpansion = std::list<double>();
        for (int i = 1; i <= nrOfCalculations; i++) {
            auto nodeExpansions = std::list<double>();
            double ballRadiusNotRounded = (double) i * (1.0 / (double) nrOfCalculations) * (double) diameter;
            int ballRadius = ceil(ballRadiusNotRounded);
            //double graphExpansion = 0;
            for (int j = 0; j < topo.getNumNodes(); j++) {
                if (strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "Client") != NULL || strstr(topo.getNode(j)->getModule()->getFullPath().c_str(), "host") != NULL) {
                    continue;
                }
                int nodesInRad = getNodesInRadius(topo.getNode(j), ballRadius);
                double expansion = (double) nodesInRad / (double) nrOfSwitches;
                //graphExpansion += expansion/(double) nrOfSwitches; // Paper ist an der Stelle etwas wirr... hier fehlt auch wieder die Summe über alle Knoten... ähnlich wie bei der Betweenness?
                                                                   // ich habe es einfach so interpretiert: graphExpansion = avg. nodeExpansion
                nodeExpansions.push_back(expansion);
            }
            meanNodeExpansion.push_back(mean(nodeExpansions,nodeExpansions.size()));
            sdNodeExpansion.push_back(sd(nodeExpansions,nodeExpansions.size()));
            varNodeExpansion.push_back(var(nodeExpansions,nodeExpansions.size()));
            skewNodeExpansion.push_back(skew(nodeExpansions,nodeExpansions.size()));
            kurtNodeExpansion.push_back(kurt(nodeExpansions,nodeExpansions.size()));
            minNodeExpansion.push_back(min(nodeExpansions));
            maxNodeExpansion.push_back(max(nodeExpansions));
            medianNodeExpansion.push_back(median(nodeExpansions,nodeExpansions.size()));
            modeNodeExpansion.push_back(mode(nodeExpansions,nodeExpansions.size()));

        }

        // Rich Club Coefficient
        int nrOfCalculations2 = 4;
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

std::map<cTopology::Node *, double> OpenFlowGraphAnalyzer::getAllWeightedDistances(cTopology::Node * src) {
    std::map<cTopology::Node *, double> distances = std::map<cTopology::Node *, double>();
    for (int i = 0; i < topo_weighted.getNumNodes(); i++) {
        cTopology::Node * tmpNode = topo_weighted.getNode(i);
        if (tmpNode == src) {
            distances[tmpNode] = 0.0;
        }
        else {
            distances[tmpNode] = getWeightedShortestPaths(src, tmpNode);
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
            pathFlow = std::min(pathFlow, rGraph[previous][current]);
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
            pathFlow = std::min(pathFlow, rGraph[previous][current]);
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
                q.push(pair<cTopology::Node *, int>(u->getLinkOut(i)->getRemoteNode(), alt));
            }
        }
        visited[u] = true;
    }
    result = dist[trg];
    return result;
}

double OpenFlowGraphAnalyzer::getWeightedShortestPathsControlPlane(cTopology::Node * src, cTopology::Node * trg) {
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

            if (strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") == NULL && strstr(u->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") == NULL) {
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
                q.push(pair<cTopology::Node *, int>(u->getLinkOut(i)->getRemoteNode(), alt));
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

void OpenFlowGraphAnalyzer::getAllWeightedShortestPaths(std::list<std::list<cTopology::Node *>>& shortestPaths, cTopology::Node * src, cTopology::Node * trg, std::map<cTopology::Node *, double> distances,
        std::list<cTopology::Node *> currentPath) {
    double trgDist = distances[trg];
    for (int i = 0; i < trg->getNumOutLinks(); i++) {
        if (strstr(trg->getLinkOut(i)->getLocalGate()->getName(), "gateCPlane") != NULL || strstr(trg->getLinkOut(i)->getLocalGate()->getName(), "gateControlPlane") != NULL) {
            continue;
        }
////////////fuer LinkRemover
        if (!(trg->getLinkOut(i)->isEnabled())) {
            continue;
        }
////////////////////////////
        if (trg->getLinkOut(i)->getLocalGate()->getChannel() == NULL) {
            continue;
        }

        if (trg->getLinkOut(i)->getLocalGate()->getChannel()->getNumParams() < 7) {
            continue;
        }

        auto neighbour = trg->getLinkOut(i)->getRemoteNode();
        double neighbourDist = distances[neighbour];
        double dist_from_trg_to_neighbour = (double) trg->getLinkOut(i)->getLocalGate()->getChannel()->par(1) + 0.000035;
        double actual_dist = dist_from_trg_to_neighbour + neighbourDist;
        double diff = ((dist_from_trg_to_neighbour + neighbourDist) - trgDist);
        if ((diff  < 0.000001) && (neighbour != src)) {
            //std::cout << "##################" << endl;
            auto path = currentPath;
            path.push_front(neighbour);
            getAllWeightedShortestPaths(shortestPaths, src, neighbour, distances, path);
        }
        else if (((dist_from_trg_to_neighbour + neighbourDist) == trgDist) && (neighbour == src)) {
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
    recordScalar("nrOfControllers", nrOfControllers);
    recordScalar("nrOfSwitches", nrOfSwitches);
    recordScalar("nrOfClients", nrOfClients);
    for (auto iter = switchesPerController.begin(); iter != switchesPerController.end(); iter++) {
        recordScalar(("switchesPerController-" + iter->first).c_str(), iter->second);
    }
    recordScalar("meanE2EL", meanE2EL);
    recordScalar("sdE2EL", sdE2EL);
    recordScalar("varE2EL", varE2EL);
    recordScalar("skewE2EL", skewE2EL);
    recordScalar("kurtE2EL", kurtE2EL);
    recordScalar("medianE2EL", medianE2EL);
    recordScalar("minE2EL", minE2EL);
    recordScalar("maxE2EL", maxE2EL);
    recordScalar("modeE2EL", modeE2EL);

    recordScalar("meanS2SL", meanS2SL);
    recordScalar("sdS2SL", sdS2SL);
    recordScalar("varS2SL", varS2SL);
    recordScalar("skewS2SL", skewS2SL);
    recordScalar("kurtS2SL", kurtS2SL);
    recordScalar("medianS2SL", medianS2SL);
    recordScalar("minS2SL", minS2SL);
    recordScalar("maxS2SL", maxS2SL);
    recordScalar("modeS2SL", modeS2SL);

    recordScalar("meanC2SL", meanC2SL);
    recordScalar("sdC2SL", sdC2SL);
    recordScalar("varC2SL", varC2SL);
    recordScalar("skewC2SL", skewC2SL);
    recordScalar("kurtC2SL", kurtC2SL);
    recordScalar("medianC2SL", medianC2SL);
    recordScalar("minC2SL", minC2SL);
    recordScalar("maxC2SL", maxC2SL);
    recordScalar("modeC2SL", modeC2SL);

    recordScalar("meanC2CL", meanC2CL);
    recordScalar("sdC2CL", sdC2CL);
    recordScalar("varC2CL", varC2CL);
    recordScalar("skewC2CL", skewC2CL);
    recordScalar("kurtC2CL", kurtC2CL);
    recordScalar("medianC2CL", medianC2CL);
    recordScalar("minC2CL", minC2CL);
    recordScalar("maxC2CL", maxC2CL);
    recordScalar("modeC2CL", modeC2CL);

    recordScalar("meanC2RL", meanC2RL);
    recordScalar("sdC2RL", sdC2RL);
    recordScalar("varC2RL", varC2RL);
    recordScalar("skewC2RL", skewC2RL);
    recordScalar("kurtC2RL", kurtC2RL);
    recordScalar("medianC2RL", medianC2RL);
    recordScalar("minC2RL", minC2RL);
    recordScalar("maxC2RL", maxC2RL);
    recordScalar("modeC2RL", modeC2RL);

    recordScalar("meanEccentricity", meanEccentricity);
    recordScalar("sdEccentricity", sdEccentricity);
    recordScalar("varEccentricity", varEccentricity);
    recordScalar("skewEccentricity", skewEccentricity);
    recordScalar("kurtEccentricity", kurtEccentricity);
    recordScalar("medianEccentricity", medianEccentricity);
    recordScalar("minEccentricity", minEccentricity);
    recordScalar("maxEccentricity", maxEccentricity);
    recordScalar("modeEccentricity", modeEccentricity);

    recordScalar("meanEccentricity_weighted", meanEccentricity_weighted);
    recordScalar("sdEccentricity_weighted", sdEccentricity_weighted);
    recordScalar("varEccentricity_weighted", varEccentricity_weighted);
    recordScalar("skewEccentricity_weighted", skewEccentricity_weighted);
    recordScalar("kurtEccentricity_weighted", kurtEccentricity_weighted);
    recordScalar("medianEccentricity_weighted", medianEccentricity_weighted);
    recordScalar("minEccentricity_weighted", minEccentricity_weighted);
    recordScalar("maxEccentricity_weighted", maxEccentricity_weighted);
    recordScalar("modeEccentricity_weighted", modeEccentricity_weighted);

    recordScalar("meanDegree", meanDegree);
    recordScalar("sdDegree", sdDegree);
    recordScalar("varDegree", varDegree);
    recordScalar("skewDegree", skewDegree);
    recordScalar("kurtDegree", kurtDegree);
    recordScalar("medianDegree", medianDegree);
    recordScalar("minDegree", minDegree);
    recordScalar("maxDegree", maxDegree);
    recordScalar("modeDegree", modeDegree);

    recordScalar("meanDegreeCentrality", meanDegreeCentrality);
    recordScalar("sdDegreeCentrality", sdDegreeCentrality);
    recordScalar("varDegreeCentrality", varDegreeCentrality);
    recordScalar("skewDegreeCentrality", skewDegreeCentrality);
    recordScalar("kurtDegreeCentrality", kurtDegreeCentrality);
    recordScalar("medianDegreeCentrality", medianDegreeCentrality);
    recordScalar("minDegreeCentrality", minDegreeCentrality);
    recordScalar("maxDegreeCentrality", maxDegreeCentrality);
    recordScalar("modeDegreeCentrality", modeDegreeCentrality);

    recordScalar("meanBetweenness", meanBetweenness);
    recordScalar("sdBetweenness", sdBetweenness);
    recordScalar("varBetweenness", varBetweenness);
    recordScalar("skewBetweenness", skewBetweenness);
    recordScalar("kurtBetweenness", kurtBetweenness);
    recordScalar("medianBetweenness", medianBetweenness);
    recordScalar("minBetweenness", minBetweenness);
    recordScalar("maxBetweenness", maxBetweenness);
    recordScalar("modeBetweenness", modeBetweenness);

    recordScalar("meanBetweennessCentrality", meanBetweennessCentrality);
    recordScalar("sdBetweennessCentrality", sdBetweennessCentrality);
    recordScalar("varBetweennessCentrality", varBetweennessCentrality);
    recordScalar("skewBetweennessCentrality", skewBetweennessCentrality);
    recordScalar("kurtBetweennessCentrality", kurtBetweennessCentrality);
    recordScalar("medianBetweennessCentrality", medianBetweennessCentrality);
    recordScalar("minBetweennessCentrality", minBetweennessCentrality);
    recordScalar("maxBetweennessCentrality", maxBetweennessCentrality);
    recordScalar("modeBetweennessCentrality", modeBetweennessCentrality);

    recordScalar("meanBetweenness_weighted", meanBetweenness_weighted);
    recordScalar("sdBetweenness_weighted", sdBetweenness_weighted);
    recordScalar("varBetweenness_weighted", varBetweenness_weighted);
    recordScalar("skewBetweenness_weighted", skewBetweenness_weighted);
    recordScalar("kurtBetweenness_weighted", kurtBetweenness_weighted);
    recordScalar("medianBetweenness_weighted", medianBetweenness_weighted);
    recordScalar("minBetweenness_weighted", minBetweenness_weighted);
    recordScalar("maxBetweenness_weighted", maxBetweenness_weighted);
    recordScalar("modeBetweenness_weighted", modeBetweenness_weighted);

    recordScalar("meanBetweennessCentrality_weighted", meanBetweennessCentrality_weighted);
    recordScalar("sdBetweennessCentrality_weighted", sdBetweennessCentrality_weighted);
    recordScalar("varBetweennessCentrality_weighted", varBetweennessCentrality_weighted);
    recordScalar("skewBetweennessCentrality_weighted", skewBetweennessCentrality_weighted);
    recordScalar("kurtBetweennessCentrality_weighted", kurtBetweennessCentrality_weighted);
    recordScalar("medianBetweennessCentrality_weighted", medianBetweennessCentrality_weighted);
    recordScalar("minBetweennessCentrality_weighted", minBetweennessCentrality_weighted);
    recordScalar("maxBetweennessCentrality_weighted", maxBetweennessCentrality_weighted);
    recordScalar("modeBetweennessCentrality_weighted", modeBetweennessCentrality_weighted);

    recordScalar("meanFarness", meanFarness);
    recordScalar("sdFarness", sdFarness);
    recordScalar("varFarness", varFarness);
    recordScalar("skewFarness", skewFarness);
    recordScalar("kurtFarness", kurtFarness);
    recordScalar("medianFarness", medianFarness);
    recordScalar("minFarness", minFarness);
    recordScalar("maxFarness", maxFarness);
    recordScalar("modeFarness", modeFarness);

    recordScalar("meanFarnessCentrality", meanFarnessCentrality);
    recordScalar("sdFarnessCentrality", sdFarnessCentrality);
    recordScalar("varFarnessCentrality", varFarnessCentrality);
    recordScalar("skewFarnessCentrality", skewFarnessCentrality);
    recordScalar("kurtFarnessCentrality", kurtFarnessCentrality);
    recordScalar("medianFarnessCentrality", medianFarnessCentrality);
    recordScalar("minFarnessCentrality", minFarnessCentrality);
    recordScalar("maxFarnessCentrality", maxFarnessCentrality);
    recordScalar("modeFarnessCentrality", modeFarnessCentrality);

    recordScalar("meanCloseness", meanCloseness);
    recordScalar("sdCloseness", sdCloseness);
    recordScalar("varCloseness", varCloseness);
    recordScalar("skewCloseness", skewCloseness);
    recordScalar("kurtCloseness", kurtCloseness);
    recordScalar("medianCloseness", medianCloseness);
    recordScalar("minCloseness", minCloseness);
    recordScalar("maxCloseness", maxCloseness);
    recordScalar("modeCloseness", modeCloseness);

    recordScalar("meanClosenessCentrality", meanClosenessCentrality);
    recordScalar("sdClosenessCentrality", sdClosenessCentrality);
    recordScalar("varClosenessCentrality", varClosenessCentrality);
    recordScalar("skewClosenessCentrality", skewClosenessCentrality);
    recordScalar("kurtClosenessCentrality", kurtClosenessCentrality);
    recordScalar("medianClosenessCentrality", medianClosenessCentrality);
    recordScalar("minClosenessCentrality", minClosenessCentrality);
    recordScalar("maxClosenessCentrality", maxClosenessCentrality);
    recordScalar("modeClosenessCentrality", modeClosenessCentrality);

    recordScalar("meanFarnessCentrality_weighted", meanFarnessCentrality_weighted);
    recordScalar("sdFarnessCentrality_weighted", sdFarnessCentrality_weighted);
    recordScalar("varFarnessCentrality_weighted", varFarnessCentrality_weighted);
    recordScalar("skewFarnessCentrality_weighted", skewFarnessCentrality_weighted);
    recordScalar("kurtFarnessCentrality_weighted", kurtFarnessCentrality_weighted);
    recordScalar("medianFarnessCentrality_weighted", medianFarnessCentrality_weighted);
    recordScalar("minFarnessCentrality_weighted", minFarnessCentrality_weighted);
    recordScalar("maxFarnessCentrality_weighted", maxFarnessCentrality_weighted);
    recordScalar("modeFarnessCentrality_weighted", modeFarnessCentrality_weighted);

    recordScalar("meanFarness_weighted", meanFarness_weighted);
    recordScalar("sdFarness_weighted", sdFarness_weighted);
    recordScalar("varFarness_weighted", varFarness_weighted);
    recordScalar("skewFarness_weighted", skewFarness_weighted);
    recordScalar("kurtFarness_weighted", kurtFarness_weighted);
    recordScalar("medianFarness_weighted", medianFarness_weighted);
    recordScalar("minFarness_weighted", minFarness_weighted);
    recordScalar("maxFarness_weighted", maxFarness_weighted);
    recordScalar("modeFarness_weighted", modeFarness_weighted);

    recordScalar("meanHopCount", meanHopCount);
    recordScalar("sdHopCount", sdHopCount);
    recordScalar("varHopCount", varHopCount);
    recordScalar("skewHopCount", skewHopCount);
    recordScalar("kurtHopCount", kurtHopCount);
    recordScalar("medianHopCount", medianHopCount);
    recordScalar("minHopCount", minHopCount);
    recordScalar("maxHopCount", maxHopCount);
    recordScalar("modeHopCount", modeHopCount);

    recordScalar("meanCloseness_weighted", meanCloseness_weighted);
    recordScalar("sdCloseness_weighted", sdCloseness_weighted);
    recordScalar("varCloseness_weighted", varCloseness_weighted);
    recordScalar("skewCloseness_weighted", skewCloseness_weighted);
    recordScalar("kurtCloseness_weighted", kurtCloseness_weighted);
    recordScalar("medianCloseness_weighted", medianCloseness_weighted);
    recordScalar("minCloseness_weighted", minCloseness_weighted);
    recordScalar("maxCloseness_weighted", maxCloseness_weighted);
    recordScalar("modeCloseness_weighted", modeCloseness_weighted);

    recordScalar("meanClosenessCentrality_weighted", meanClosenessCentrality_weighted);
    recordScalar("sdClosenessCentrality_weighted", sdClosenessCentrality_weighted);
    recordScalar("varClosenessCentrality_weighted", varClosenessCentrality_weighted);
    recordScalar("skewClosenessCentrality_weighted", skewClosenessCentrality_weighted);
    recordScalar("kurtClosenessCentrality_weighted", kurtClosenessCentrality_weighted);
    recordScalar("medianClosenessCentrality_weighted", medianClosenessCentrality_weighted);
    recordScalar("minClosenessCentrality_weighted", minClosenessCentrality_weighted);
    recordScalar("maxClosenessCentrality_weighted", maxClosenessCentrality_weighted);
    recordScalar("modeClosenessCentrality_weighted", modeClosenessCentrality_weighted);

    recordScalar("graphCentralization", graphCentralization);

    recordScalar("meanEdgeDistinctPaths", meanEdgeDistinctPaths);
    recordScalar("sdEdgeDistinctPaths", sdEdgeDistinctPaths);
    recordScalar("varEdgeDistinctPaths", varEdgeDistinctPaths);
    recordScalar("skewEdgeDistinctPaths", skewEdgeDistinctPaths);
    recordScalar("kurtEdgeDistinctPaths", kurtEdgeDistinctPaths);
    recordScalar("medianEdgeDistinctPaths", medianEdgeDistinctPaths);
    recordScalar("minEdgeDistinctPaths", minEdgeDistinctPaths);
    recordScalar("maxEdgeDistinctPaths", maxEdgeDistinctPaths);
    recordScalar("modeEdgeDistinctPaths", modeEdgeDistinctPaths);

    recordScalar("meanNodeDisjointPaths", meanNodeDisjointPaths);
    recordScalar("sdNodeDisjointPaths", sdNodeDisjointPaths);
    recordScalar("varNodeDisjointPaths", varNodeDisjointPaths);
    recordScalar("skewNodeDisjointPaths", skewNodeDisjointPaths);
    recordScalar("kurtNodeDisjointPaths", kurtNodeDisjointPaths);
    recordScalar("medianNodeDisjointPaths", medianNodeDisjointPaths);
    recordScalar("minNodeDisjointPaths", minNodeDisjointPaths);
    recordScalar("maxNodeDisjointPaths", maxNodeDisjointPaths);
    recordScalar("modeNodeDisjointPaths", modeNodeDisjointPaths);

    recordScalar("meanLocalClusteringCoefficient", meanLocalClusteringCoefficient);
    recordScalar("sdLocalClusteringCoefficient", sdLocalClusteringCoefficient);
    recordScalar("varLocalClusteringCoefficient", varLocalClusteringCoefficient);
    recordScalar("skewLocalClusteringCoefficient", skewLocalClusteringCoefficient);
    recordScalar("kurtLocalClusteringCoefficient", kurtLocalClusteringCoefficient);
    recordScalar("medianLocalClusteringCoefficient", medianLocalClusteringCoefficient);
    recordScalar("minLocalClusteringCoefficient", minLocalClusteringCoefficient);
    recordScalar("maxLocalClusteringCoefficient", maxLocalClusteringCoefficient);
    recordScalar("modeLocalClusteringCoefficient", modeLocalClusteringCoefficient);

    double i = 1.0;
    for (auto iter = meanNodeExpansion.begin(); iter != meanNodeExpansion.end(); iter++) {
        recordScalar(("meanNodeExpansion-" + std::to_string(i * 1.0/(double) meanNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = sdNodeExpansion.begin(); iter != sdNodeExpansion.end(); iter++) {
        recordScalar(("sdNodeExpansion-" + std::to_string(i * 1.0/(double) sdNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = varNodeExpansion.begin(); iter != varNodeExpansion.end(); iter++) {
        recordScalar(("varNodeExpansion-" + std::to_string(i * 1.0/(double) varNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = skewNodeExpansion.begin(); iter != skewNodeExpansion.end(); iter++) {
        recordScalar(("skewNodeExpansion-" + std::to_string(i * 1.0/(double) skewNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = kurtNodeExpansion.begin(); iter != kurtNodeExpansion.end(); iter++) {
        recordScalar(("kurtNodeExpansion-" + std::to_string(i * 1.0/(double) kurtNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = minNodeExpansion.begin(); iter != minNodeExpansion.end(); iter++) {
        recordScalar(("minNodeExpansion-" + std::to_string(i * 1.0/(double) minNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = maxNodeExpansion.begin(); iter != maxNodeExpansion.end(); iter++) {
        recordScalar(("maxNodeExpansion-" + std::to_string(i * 1.0/(double) maxNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = medianNodeExpansion.begin(); iter != medianNodeExpansion.end(); iter++) {
        recordScalar(("medianNodeExpansion-" + std::to_string(i * 1.0/(double) medianNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = modeNodeExpansion.begin(); iter != modeNodeExpansion.end(); iter++) {
        recordScalar(("modeNodeExpansion-" + std::to_string(i * 1.0/(double) modeNodeExpansion.size()) + "OfDiameter").c_str(), *iter);
        i++;
    }

    i = 1.0;
    for (auto iter = richClubCoefficients.begin(); iter != richClubCoefficients.end(); iter++) {
        recordScalar(("richClubCoefficient-" + std::to_string(i * 1.0/(double) richClubCoefficients.size()) + "OfNodes").c_str(), *iter);
        i++;
    }

    recordScalar("radius", radius);
    recordScalar("diameter", diameter);

    recordScalar("radius_weighted", radius_weighted);
    recordScalar("diameter_weighted", diameter_weighted);

    recordScalar("cpd", cpd);
    recordScalar("cpd_weighted", cpd_weighted);
    recordScalar("assortativity", assortativity);

    recordScalar("vertexConnectivity", vertexConnectivity);
    recordScalar("edgeConnectivity", edgeConnectivity);
    recordScalar("vertexPersistence", vertexPersistence);
    recordScalar("edgePersistence", edgePersistence);

    recordScalar("globalClusteringCoefficient", globalClusteringCoefficient);


    std::map<int, int>::iterator iter;
    for (iter = nodeDegreeDistribution.begin(); iter != nodeDegreeDistribution.end(); iter++) {
        recordScalar(("nodesWithDegree-" + std::to_string(iter->first)).c_str(), iter->second);
    }
    for (iter = hopCountDistribution.begin(); iter != hopCountDistribution.end(); iter++) {
        recordScalar(("pathsWithHopCount-" + std::to_string(iter->first)).c_str(), iter->second);
    }
    for (auto iter = closenesses_weighted.begin(); iter != closenesses_weighted.end(); iter++) {
        recordScalar(("closeness_weightedOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
    }
    for (auto iter = farnesses_weighted.begin(); iter != farnesses_weighted.end(); iter++) {
        recordScalar(("farness_weightedOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
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
    for (auto iter = betweennessesNormalized_weighted.begin(); iter != betweennessesNormalized_weighted.end(); iter++) {
        recordScalar(("betweenness_weightedOfNode-" + iter->first->getModule()->getFullPath()).c_str(), iter->second);
    }
}

void OpenFlowGraphAnalyzer::handleMessage(cMessage *msg) {
    error("this module doesn't handle messages, it runs only in initialize()");
}
