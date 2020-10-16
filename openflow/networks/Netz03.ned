package openflow.networks;

import inet.nodes.ethernet.EtherSwitch;
import openflow.hostApps.TCPTrafficGeneratorApp;
import openflow.openflow.controller.Open_Flow_Controller;
import openflow.openflow.controller.*;
import openflow.openflow.switch.Open_Flow_Switch;
import openflow.openflow.switch.*;
import openflow.utility.*;

import inet.nodes.inet.StandardHost;
import inet.networklayer.autorouting.ipv4.IPv4NodeConfigurator;
import inet.networklayer.autorouting.ipv4.*;
import inet.util.ThruputMeteringChannel;

network Netz03
{
    parameters:
        int numNodes = default(4);
        int numControllers @display("bgb=768,465") = default(1);
        
    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 0us;
            datarate = 100Mbps;
            thruputDisplayFormat = "N";
        }
    submodules:
        analizer: OpenFlowGraphAnalyzer {
            @display("p=61,62");
        }
        linkRemover: LinkRemoverModule {
            @display("p=53,134");
        }
        spanningTree: StaticSpanningTree {
            parameters:
                @display("p=61,32");
        }
        open_flow_switch[numNodes]: Open_Flow_Switch {
            @display("p=306,200,ring,150");
        }
        host[numNodes]: StandardHost {
            @display("p=236,130,ring,220");
        }
        open_flow_controller1: Open_Flow_Controller {
            @display("p=456,350");
        }
        etherSwitch: EtherSwitch {
            @display("p=456,350");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=61,196");
        }

    connections allowunconnected:

        //host - switch connections
        for i=0..(numNodes)-1 {
            host[i].ethg++ <--> ethernetline <--> open_flow_switch[i].gateDataPlane++;
        }

        //switch to switch connections
        for i=0..(numNodes)-2 {
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+1].gateDataPlane++ if (i+1)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+2].gateDataPlane++ if (i+2)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+3].gateDataPlane++ if (i+3)<numNodes;

            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+4].gateDataPlane++ if (i+4)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+5].gateDataPlane++ if (i+5)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+6].gateDataPlane++ if (i+6)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+7].gateDataPlane++ if (i+7)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+8].gateDataPlane++ if (i+8)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+9].gateDataPlane++ if (i+9)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+10].gateDataPlane++ if (i+10)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+11].gateDataPlane++ if (i+11)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+12].gateDataPlane++ if (i+12)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+13].gateDataPlane++ if (i+13)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+14].gateDataPlane++ if (i+14)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+15].gateDataPlane++ if (i+15)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+16].gateDataPlane++ if (i+16)<numNodes;
            open_flow_switch[i].gateDataPlane++ <--> ethernetline <--> open_flow_switch[i+17].gateDataPlane++ if (i+17)<numNodes;
        }
        //switch - etherSwitch connections
        for i=0..(numNodes)-1 {
            etherSwitch.ethg++ <--> ethernetline <--> open_flow_switch[i].gateControlPlane++;
        }

        //etherSwitch - controller
        etherSwitch.ethg++ <--> ethernetline <--> open_flow_controller1.ethg++;
}
