
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
        int testVar;
        cTopology topo;
        cTopology topo_weighted;

        std::list<std::list<cTopology::Node *> > computedPaths;
        std::list<cTopology::Node * > getShortestPath(cTopology::Node * src, cTopology::Node * trg);
        std::list<double> richClubCoefficients;
        std::list<double> graphExpansions;
        std::map<cTopology::Node *, double> betweennessesNormalized;
        std::map<int, int> hopCountDistribution;
        std::map<cTopology::Node *, double> closenesses;
        std::map<cTopology::Node *, double> farnesses;
        std::map<int, int> nodeDegreeDistribution;

        double radius;
        double diameter;
        double cpd;
        double assortativity;
        double vertexConnectivity;
        double edgeConnectivity;
        double vertexPersistence;
        double edgePersistence;
        double eccentricity;
        double averageNrOfNodeDistinctPaths;
        double averageNrOfEdgeDistinctPaths;
        double averageCloseness;
        double averageFarness;
        double averageBetweenness;
        double globalClusteringCoefficient;
        double avgPathDelay;

        double maxPathLength;
        double minPathLength;
        double avgPathLength;
        double numClientNodes;
        double numSwitchNodes;
        double avgNumSwitchLinks;
        bool considerOnlyEndToEnd;

        std::map<std::string,int> swMap;
        std::map<std::string,int> clMap;

        virtual int numInitStages() const  {return 5;}
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);
        virtual int getNodesInRadius(cTopology::Node * src, int radius);
        virtual std::map<cTopology::Node *, int> getAllDistances(cTopology::Node * src);
        virtual double getWeightedShortestPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual bool residualGraphBFS(std::map<int, std::map<int, int>> residualGraph, int src, int trg, std::map<int, int>& parents);
        virtual std::pair<int, std::list<int>> findNodeDisjointPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual std::pair<int, std::list<int>> findDisjointPaths(cTopology::Node * src, cTopology::Node * trg);
        virtual void getAllShortestPaths(std::list<std::list<cTopology::Node *>>& shortestPaths, cTopology::Node * src, cTopology::Node * trg, std::map<cTopology::Node *, int> distances,        std::list<cTopology::Node *> currentPath);
};


#endif /* SPANNINGTREE_H_ */
