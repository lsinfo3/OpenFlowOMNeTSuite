#include <KN_LLDPAgent.h>
#include <algorithm>


#define MSGKIND_TRIGGERLLDP 101
#define MSGKIND_LLDPAGENTBOOTED 201

Define_Module(KN_LLDPAgent);

KN_LLDPAgent::KN_LLDPAgent(){

}

KN_LLDPAgent::~KN_LLDPAgent(){

}

void KN_LLDPAgent::initialize(){
    LLDPAgent::initialize();
    kandooAgent = NULL;

    appName = "KN_LLDPAgent";

    //register signals
    kandooEventSignalId =registerSignal("KandooEvent");
    getParentModule()->subscribe("KandooEvent",this);

    timeDiff_signal = registerSignal("timeDiff");

}






void KN_LLDPAgent::handlePacketIn(OFP_Packet_In * packet_in_msg){
    //check if it is a received lldp
    CommonHeaderFields headerFields = extractCommonHeaderFields(packet_in_msg);

    //check if it is an lldp packet
    if(headerFields.eth_type == 0x88CC){
        EthernetIIFrame *frame =  dynamic_cast<EthernetIIFrame *>(packet_in_msg->getEncapsulatedPacket());
        //check if we have received the entire frame, if not the flow mods have not been sent yet
        if(frame != NULL){
            LLDP *lldp = (LLDP *) frame->getEncapsulatedPacket();
            mibGraph.addEntry(lldp->getChassisID(),lldp->getPortID(),headerFields.swInfo->getMacAddress(),headerFields.inport,timeOut);
            if(printMibGraph){
                EV << mibGraph.getStringGraph() << endl;
            }

            if(!kandooAgent->getIsRootController()){
                //inform kandoo root
                LLDP_Wrapper *wrapper = new LLDP_Wrapper();
                wrapper->setDstId(headerFields.swInfo->getMacAddress());
                wrapper->setDstPort(headerFields.inport);
                wrapper->setSrcId(lldp->getChassisID());
                wrapper->setSrcPort(lldp->getPortID());
                wrapper->setTimestamp(simTime().dbl());

                KandooEntry entry = KandooEntry();
                entry.srcApp = "KN_LLDPAgent";
                entry.srcSwitch = headerFields.swInfo->getMacAddress();
                entry.trgSwitch = "";
                entry.trgApp = "KN_LLDPAgent";
                entry.type =0;
                entry.srcController = controller->getFullPath();
                entry.trgController = "RootController";
                entry.payload = wrapper;

                kandooAgent->sendRequest(entry);
            }

        } else {
            //resend flow mod
            triggerFlowMod(headerFields.swInfo);
        }

     } else {
         //this could be a packet originating from an end device, check if the port is associated with an lldp entry


         bool needToAdd = mibGraph.addEntry(headerFields.src_mac.str(),-1,headerFields.swInfo->getMacAddress(),headerFields.inport,timeOut);
         if(!kandooAgent->getIsRootController() && needToAdd ){
             //inform kandoo root
             LLDP_Wrapper *wrapper = new LLDP_Wrapper();
             wrapper->setDstId(headerFields.swInfo->getMacAddress());
             wrapper->setDstPort(headerFields.inport);
             wrapper->setSrcId(headerFields.src_mac.str());
             wrapper->setSrcPort(-1);
             wrapper->setTimestamp(simTime().dbl());

             KandooEntry entry = KandooEntry();
             entry.srcApp = "KN_LLDPAgent";
             entry.trgApp = "KN_LLDPAgent";
             entry.srcSwitch = headerFields.swInfo->getMacAddress();
             entry.trgSwitch = "";
             entry.type =0;
             entry.srcController = controller->getFullPath();
             entry.trgController = "RootController";
             entry.payload = wrapper;

             kandooAgent->sendRequest(entry);
         }

         if(printMibGraph){
             EV << mibGraph.getStringGraph() << endl;
         }
     }



}


void KN_LLDPAgent::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    //set knagent link
    if(kandooAgent == NULL && controller != NULL){
        auto appList = controller->getAppList();

        for(auto iterApp=appList->begin();iterApp!=appList->end();++iterApp){
            if(dynamic_cast<KandooAgent *>(*iterApp) != NULL) {
                KandooAgent *kn = (KandooAgent *) *iterApp;
                kandooAgent = kn;
                break;
            }
        }
    }

    LLDPAgent::receiveSignal(src,id,obj);

    //check for kandoo events
    if(id == kandooEventSignalId){
        if(dynamic_cast<KN_Packet *>(obj) != NULL) {
            KN_Packet *knpck = (KN_Packet *) obj;
            if(strcmp(knpck->getKnEntry().trgApp.c_str(),appName.c_str())==0){
                if(knpck->getKnEntry().type==0){
                    if (dynamic_cast<LLDP_Wrapper *>(knpck->getKnEntry().payload) != NULL) {
                        LLDP_Wrapper *wrapper = (LLDP_Wrapper *) knpck->getKnEntry().payload;
                        mibGraph.addEntry(wrapper->getSrcId(),wrapper->getSrcPort(),wrapper->getDstId(),wrapper->getDstPort(),timeOut);
                        double timeDifference =  simTime().dbl() - wrapper->getTimestamp();
                        emit(timeDiff_signal, timeDifference);
                        if(printMibGraph){
                            EV << mibGraph.getStringGraph() << endl;
                        }
                    }
                }
            }

        }
    }

}


