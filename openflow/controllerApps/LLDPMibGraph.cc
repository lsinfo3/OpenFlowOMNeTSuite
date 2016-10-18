#include <omnetpp.h>
#include "LLDPMibGraph.h"

#include <vector>
#include <sstream>


using namespace std;




LLDPMibGraph::LLDPMibGraph(){
    numOfEdges=0;
    numOfVerticies=0;
    version = 0;
}

const std::string LLDPMibGraph::getStringGraph(){
    std::map<std::string,std::vector<LLDPMib> >::iterator iterKey;
    std::vector<LLDPMib>::iterator iterList;
    std::stringstream stream;

    for(iterKey= verticies.begin(); iterKey!= verticies.end();iterKey++){
        for(iterList=verticies[iterKey->first].begin(); iterList!=verticies[iterKey->first].end(); iterList++){
            stream << " ("<<iterList->getSrcId() << "," <<iterList->getSrcPort() << ") ->" << "("<<iterList->getDstId() << "," <<iterList->getDstPort() << ") Expires at:"<< iterList->getExpiresAt() << "\n";
        }
    }

    return stream.str();
}


bool LLDPMibGraph::addEntry(std::string src, int srcPort, std::string dst, int dstPort, SimTime timeOut) {
    //check if we have an arp packet
    if(srcPort == -1){
        if(verticies.count(dst) >0){
            //we have seen this arp before, check if we are the first hop
            std::vector<LLDPMib>::iterator iterList;
            for(iterList=verticies[dst].begin();iterList!=verticies[dst].end();iterList++){
                if(iterList->getSrcPort() == dstPort && iterList->getDstPort() != -1){
                    return false;
                }
            }
        }
    }

    //enter src to dst
    //check if vertex exists
    if(verticies.count(src) <= 0){
        verticies[src] = std::vector<LLDPMib>();
        LLDPMib mib = LLDPMib();
        mib.setDstId(dst);
        mib.setDstPort(dstPort);
        mib.setSrcId(src);
        mib.setSrcPort(srcPort);
        mib.setExpiresAt(simTime()+timeOut);
        verticies[src].push_back(mib);
        numOfVerticies++;
        numOfEdges++;
        version++;
    } else {
        //check if entry exists
        LLDPMib mib = LLDPMib();
        mib.setDstId(dst);
        mib.setDstPort(dstPort);
        mib.setSrcId(src);
        mib.setSrcPort(srcPort);
        mib.setExpiresAt(simTime()+timeOut);

        std::vector<LLDPMib >::iterator iterMib = std::find(verticies[src].begin(), verticies[src].end(), mib);
        if(iterMib != verticies[src].end()){
            (*iterMib).setExpiresAt(simTime()+timeOut);
        } else {
            verticies[src].push_back(mib);
            numOfEdges++;
            version++;
        }
    }

    //enter dst to src
    //check if vertex exists
    if(verticies.count(dst) <= 0){
        verticies[dst] = std::vector<LLDPMib>();
        LLDPMib mib = LLDPMib();
        mib.setDstId(src);
        mib.setDstPort(srcPort);
        mib.setSrcId(dst);
        mib.setSrcPort(dstPort);
        mib.setExpiresAt(simTime()+timeOut);
        verticies[dst].push_back(mib);
        numOfVerticies++;
        numOfEdges++;
        version++;
     } else {
        //check if entry exists
        LLDPMib mib = LLDPMib();
        mib.setDstId(src);
        mib.setDstPort(srcPort);
        mib.setSrcId(dst);
        mib.setSrcPort(dstPort);
        mib.setExpiresAt(simTime()+timeOut);

        std::vector<LLDPMib >::iterator iterMib = std::find(verticies[dst].begin(), verticies[dst].end(), mib);
        if(iterMib != verticies[dst].end()){
            (*iterMib).setExpiresAt(simTime()+timeOut);
        } else {
            verticies[dst].push_back(mib);
            numOfEdges++;
            version++;
        }
     }
    return true;

}


void LLDPMibGraph::removeExpiredEntries(){
    std::map<std::string, std::vector<LLDPMib > >::iterator iterKey = verticies.begin();
    std::vector<LLDPMib>::iterator iterList;
    while(iterKey != verticies.end()){
        //remove expired list entries
        iterList=iterKey->second.begin();
        while(iterList != iterKey->second.end()){
            if(iterList->getExpiresAt() < simTime()){
                iterKey->second.erase(iterList);
                iterList--;
                numOfEdges--;
                version++;
            }
            iterList++;
        }

        //remove vertex if no link is left
        if(iterKey->second.empty()){
            verticies.erase(iterKey);
            iterKey--;
            numOfVerticies--;
            version++;
        }
        iterKey++;
    }
}






long LLDPMibGraph::getNumOfEdges() const {
    return numOfEdges;
}

long LLDPMibGraph::getNumOfVerticies() const {
    return numOfVerticies;
}


const std::map<std::string, std::vector<LLDPMib> >& LLDPMibGraph::getVerticies() const {
    return verticies;
}

long LLDPMibGraph::getVersion() const {
    return version;
}

