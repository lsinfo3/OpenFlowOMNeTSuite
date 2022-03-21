
#ifndef OPENFLOWGRAPHANALYZER_H_
#define OPENFLOWGRAPHANALYZER_H_

#include <omnetpp.h>
#include "OF_Switch.h"
#include "ctopology.h"
//#include "LinkRemoverModule.h"

class Node;

class OpenFlowGraphAnalyzer : public cSimpleModule
{

public:
    virtual void finish();

protected:
        cTopology topo;
        cTopology topo_new;
        cTopology topo_weighted;
        cTopology topo_complete;

        std::map<int, int> hopCountDistribution;
        std::map<int, int> nodeDegreeDistribution;

        std::map<cTopology::Node *, double> closenesses;
        std::map<cTopology::Node *, double> farnesses;
        std::map<cTopology::Node *, double> closenesses_weighted;
        std::map<cTopology::Node *, double> farnesses_weighted;
        std::map<cTopology::Node *, double> betweennessesNormalized;
        std::map<cTopology::Node *, double> betweennessesNormalized_weighted;

        double nrOfControllers;
        double nrOfSwitches;
        double nrOfClients;
        std::map<std::string, double> switchesPerController;

        float meanE2EL;
        float sdE2EL;
        float varE2EL;
        float skewE2EL;
        float kurtE2EL;
        float minE2EL;
        float maxE2EL;
        float medianE2EL;
        float modeE2EL;

        float meanS2SL;
        float sdS2SL;
        float varS2SL;
        float skewS2SL;
        float kurtS2SL;
        float minS2SL;
        float maxS2SL;
        float medianS2SL;
        float modeS2SL;


        float meanC2SL;
        float sdC2SL;
        float varC2SL;
        float skewC2SL;
        float kurtC2SL;
        float minC2SL;
        float maxC2SL;
        float medianC2SL;
        float modeC2SL;

        float meanC2CL;
        float sdC2CL;
        float varC2CL;
        float skewC2CL;
        float kurtC2CL;
        float minC2CL;
        float maxC2CL;
        float medianC2CL;
        float modeC2CL;

        float meanC2RL;
        float sdC2RL;
        float varC2RL;
        float skewC2RL;
        float kurtC2RL;
        float minC2RL;
        float maxC2RL;
        float medianC2RL;
        float modeC2RL;

        float meanEccentricity;
        float sdEccentricity;
        float varEccentricity;
        float skewEccentricity;
        float kurtEccentricity;
        float minEccentricity;
        float maxEccentricity;
        float medianEccentricity;
        float modeEccentricity;

        float meanEccentricity_weighted;
        float sdEccentricity_weighted;
        float varEccentricity_weighted;
        float skewEccentricity_weighted;
        float kurtEccentricity_weighted;
        float minEccentricity_weighted;
        float maxEccentricity_weighted;
        float medianEccentricity_weighted;
        float modeEccentricity_weighted;

        float radius;
        float diameter;

        float radius_weighted;
        float diameter_weighted;

        float meanDegree;
        float sdDegree;
        float varDegree;
        float skewDegree;
        float kurtDegree;
        float minDegree;
        float maxDegree;
        float medianDegree;
        float modeDegree;

        float meanHopCount;
        float sdHopCount;
        float varHopCount;
        float skewHopCount;
        float kurtHopCount;
        float minHopCount;
        float maxHopCount;
        float medianHopCount;
        float modeHopCount;

        float meanDegreeCentrality;
        float sdDegreeCentrality;
        float varDegreeCentrality;
        float skewDegreeCentrality;
        float kurtDegreeCentrality;
        float minDegreeCentrality;
        float maxDegreeCentrality;
        float medianDegreeCentrality;
        float modeDegreeCentrality;

        float assortativity;

        float meanBetweenness;
        float sdBetweenness;
        float varBetweenness;
        float skewBetweenness;
        float kurtBetweenness;
        float minBetweenness;
        float maxBetweenness;
        float medianBetweenness;
        float modeBetweenness;

        float meanBetweenness_weighted;
        float sdBetweenness_weighted;
        float varBetweenness_weighted;
        float skewBetweenness_weighted;
        float kurtBetweenness_weighted;
        float minBetweenness_weighted;
        float maxBetweenness_weighted;
        float medianBetweenness_weighted;
        float modeBetweenness_weighted;

        float meanBetweennessCentrality;
        float sdBetweennessCentrality;
        float varBetweennessCentrality;
        float skewBetweennessCentrality;
        float kurtBetweennessCentrality;
        float minBetweennessCentrality;
        float maxBetweennessCentrality;
        float medianBetweennessCentrality;
        float modeBetweennessCentrality;

        float meanBetweennessCentrality_weighted;
        float sdBetweennessCentrality_weighted;
        float varBetweennessCentrality_weighted;
        float skewBetweennessCentrality_weighted;
        float kurtBetweennessCentrality_weighted;
        float minBetweennessCentrality_weighted;
        float maxBetweennessCentrality_weighted;
        float medianBetweennessCentrality_weighted;
        float modeBetweennessCentrality_weighted;

        float meanFarness;
        float sdFarness;
        float varFarness;
        float skewFarness;
        float kurtFarness;
        float minFarness;
        float maxFarness;
        float medianFarness;
        float modeFarness;

        float meanFarnessCentrality;
        float sdFarnessCentrality;
        float varFarnessCentrality;
        float skewFarnessCentrality;
        float kurtFarnessCentrality;
        float minFarnessCentrality;
        float maxFarnessCentrality;
        float medianFarnessCentrality;
        float modeFarnessCentrality;

        float meanCloseness;
        float sdCloseness;
        float varCloseness;
        float skewCloseness;
        float kurtCloseness;
        float minCloseness;
        float maxCloseness;
        float medianCloseness;
        float modeCloseness;

        float meanClosenessCentrality;
        float sdClosenessCentrality;
        float varClosenessCentrality;
        float skewClosenessCentrality;
        float kurtClosenessCentrality;
        float minClosenessCentrality;
        float maxClosenessCentrality;
        float medianClosenessCentrality;
        float modeClosenessCentrality;

        float meanFarness_weighted;
        float sdFarness_weighted;
        float varFarness_weighted;
        float skewFarness_weighted;
        float kurtFarness_weighted;
        float minFarness_weighted;
        float maxFarness_weighted;
        float medianFarness_weighted;
        float modeFarness_weighted;

        float meanFarnessCentrality_weighted;
        float sdFarnessCentrality_weighted;
        float varFarnessCentrality_weighted;
        float skewFarnessCentrality_weighted;
        float kurtFarnessCentrality_weighted;
        float minFarnessCentrality_weighted;
        float maxFarnessCentrality_weighted;
        float medianFarnessCentrality_weighted;
        float modeFarnessCentrality_weighted;

        float meanCloseness_weighted;
        float sdCloseness_weighted;
        float varCloseness_weighted;
        float skewCloseness_weighted;
        float kurtCloseness_weighted;
        float minCloseness_weighted;
        float maxCloseness_weighted;
        float medianCloseness_weighted;
        float modeCloseness_weighted;

        float meanClosenessCentrality_weighted;
        float sdClosenessCentrality_weighted;
        float varClosenessCentrality_weighted;
        float skewClosenessCentrality_weighted;
        float kurtClosenessCentrality_weighted;
        float minClosenessCentrality_weighted;
        float maxClosenessCentrality_weighted;
        float medianClosenessCentrality_weighted;
        float modeClosenessCentrality_weighted;

        float meanEdgeDistinctPaths;
        float sdEdgeDistinctPaths;
        float varEdgeDistinctPaths;
        float skewEdgeDistinctPaths;
        float kurtEdgeDistinctPaths;
        float minEdgeDistinctPaths;
        float maxEdgeDistinctPaths;
        float medianEdgeDistinctPaths;
        float modeEdgeDistinctPaths;

        float meanNodeDisjointPaths;
        float sdNodeDisjointPaths;
        float varNodeDisjointPaths;
        float skewNodeDisjointPaths;
        float kurtNodeDisjointPaths;
        float minNodeDisjointPaths;
        float maxNodeDisjointPaths;
        float medianNodeDisjointPaths;
        float modeNodeDisjointPaths;

        float meanLocalClusteringCoefficient;
        float sdLocalClusteringCoefficient;
        float varLocalClusteringCoefficient;
        float skewLocalClusteringCoefficient;
        float kurtLocalClusteringCoefficient;
        float minLocalClusteringCoefficient;
        float maxLocalClusteringCoefficient;
        float medianLocalClusteringCoefficient;
        float modeLocalClusteringCoefficient;

        float globalClusteringCoefficient;

        float graphCentralization;
        float cpd;
        float cpd_weighted;

        std::list<double> richClubCoefficients;

        float vertexConnectivity;
        float edgeConnectivity;
        float vertexPersistence;
        float edgePersistence;

        std::list<double> meanNodeExpansion;
        std::list<double> sdNodeExpansion;
        std::list<double> varNodeExpansion;
        std::list<double> skewNodeExpansion;
        std::list<double> kurtNodeExpansion;
        std::list<double> minNodeExpansion;
        std::list<double> maxNodeExpansion;
        std::list<double> medianNodeExpansion;
        std::list<double> modeNodeExpansion;

        bool considerOnlyEndToEnd;

        float mean(std::list<double> data, int n);
        float sd(std::list<double> data, int n);
        float var(std::list<double> data, int n);
        float skew(std::list<double> data, int n);
        float kurt(std::list<double> data, int n);
        float min(std::list<double> data);
        float max(std::list<double> data);
        float median(std::list<double> data, int n);
        float mode(std::list<double> data, int n);

        virtual int numInitStages() const  {return 5;}
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);
        std::list<cTopology::Node * > getShortestPath(cTopology::Node * src, cTopology::Node * trg);
        virtual int getNodesInRadius(cTopology::Node * src, int radius);
        virtual std::map<cTopology::Node *, int> getAllDistances(cTopology::Node * src);
        virtual std::map<cTopology::Node *, double> getAllWeightedDistances(cTopology::Node * src);
        virtual double getWeightedShortestPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual double getWeightedShortestPathsControlPlane(cTopology::Node * src, cTopology::Node * trg);
        virtual bool residualGraphBFS(std::map<int, std::map<int, int>> residualGraph, int src, int trg, std::map<int, int>& parents);
        virtual std::pair<int, std::list<int>> findNodeDisjointPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual std::pair<int, std::list<int>> findDisjointPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual void getAllShortestPaths(std::list<std::list<cTopology::Node *>>& shortestPaths, cTopology::Node * src, cTopology::Node * trg, std::map<cTopology::Node *, int> distances,        std::list<cTopology::Node *> currentPath);
        virtual void getAllWeightedShortestPaths(std::list<std::list<cTopology::Node *>>& shortestPaths, cTopology::Node * src, cTopology::Node * trg, std::map<cTopology::Node *, double> distances,        std::list<cTopology::Node *> currentPath);
};


#endif /* SPANNINGTREE_H_ */
