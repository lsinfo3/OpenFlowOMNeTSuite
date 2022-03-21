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

package openflow.networks.random;

import inet.nodes.ethernet.EtherSwitch;
import inet.nodes.inet.Router;
import inet.nodes.inet.StandardHost;
import inet.util.ThruputMeteringChannel;
import inet.networklayer.autorouting.ipv4.*;

import openflow.utility.*;
import openflow.nodes.*;
import openflow.openflow.controller.*;
import openflow.openflow.switch.*;
import openflow.hyperflow.*;


network Barabasi_Albert_geometric_med_2_HF
{
parameters:
int numControllers = default(1);
int placementID = default(1);
types:
channel backboneline extends ThruputMeteringChannel
{
delay = 1us;
datarate = 40Gbps;
thruputDisplayFormat = "u";
}
submodules:
configurator: IPv4NetworkConfigurator {
parameters:
@display("p=449,598");
}

controllerInvolvementFilter: ControllerInvolvementFilter {@display("p=59,39");}
spanningTree: StaticSpanningTree {
@display("p=349,598");
}

openFlowGraphAnalyzer: OpenFlowGraphAnalyzer {
@display("p=218,598");
}

hf_synchronizer: Hyper_Flow_Synchronizer {
@display("p=396,23");
}
open_flow_controller1: Open_Flow_Controller if numControllers >=1 {@display("p=20,100");}
open_flow_controller2: Open_Flow_Controller if numControllers >=2 {@display("p=40,100");}
open_flow_controller3: Open_Flow_Controller if numControllers >=3 {@display("p=60,100");}
open_flow_controller4: Open_Flow_Controller if numControllers >=4 {@display("p=80,100");}
open_flow_controller5: Open_Flow_Controller if numControllers >=5 {@display("p=100,100");}
ofs_0: Open_Flow_Domain;
ofs_1: Open_Flow_Domain;
ofs_2: Open_Flow_Domain;
ofs_3: Open_Flow_Domain;
ofs_4: Open_Flow_Domain;
ofs_5: Open_Flow_Domain;
ofs_6: Open_Flow_Domain;
ofs_7: Open_Flow_Domain;
ofs_8: Open_Flow_Domain;
ofs_9: Open_Flow_Domain;
ofs_10: Open_Flow_Domain;
ofs_11: Open_Flow_Domain;
ofs_12: Open_Flow_Domain;
ofs_13: Open_Flow_Domain;
ofs_14: Open_Flow_Domain;
ofs_15: Open_Flow_Domain;
ofs_16: Open_Flow_Domain;
ofs_17: Open_Flow_Domain;
ofs_18: Open_Flow_Domain;
ofs_19: Open_Flow_Domain;
ofs_20: Open_Flow_Domain;
ofs_21: Open_Flow_Domain;
ofs_22: Open_Flow_Domain;
ofs_23: Open_Flow_Domain;
ofs_24: Open_Flow_Domain;
ofs_25: Open_Flow_Domain;

connections allowunconnected:
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 9km; } <--> ofs_1.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 131km; } <--> ofs_2.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 319km; } <--> ofs_3.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 174km; } <--> ofs_4.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 2002km; } <--> ofs_6.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 62km; } <--> ofs_7.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 352km; } <--> ofs_10.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 5km; } <--> ofs_11.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 159km; } <--> ofs_12.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 127km; } <--> ofs_13.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 465km; } <--> ofs_18.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 1091km; } <--> ofs_20.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 418km; } <--> ofs_8.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 517km; } <--> ofs_5.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 165km; } <--> ofs_9.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 185km; } <--> ofs_19.gateDPlane++;
ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 346km; } <--> ofs_15.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 420km; } <--> ofs_14.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 395km; } <--> ofs_17.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 151km; } <--> ofs_25.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 79km; } <--> ofs_16.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 230km; } <--> ofs_24.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 766km; } <--> ofs_22.gateDPlane++;
ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 453km; } <--> ofs_21.gateDPlane++;
ofs_19.gateDPlane++ <--> DistanceChannel {  distance = 101km; } <--> ofs_23.gateDPlane++;

ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 5km; } <--> ofs_11.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 9km; } <--> ofs_1.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 62km; } <--> ofs_7.gateCPlane++;
ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 79km; } <--> ofs_16.gateCPlane++;
ofs_19.gateCPlane++ <--> DistanceChannel {  distance = 101km; } <--> ofs_23.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 127km; } <--> ofs_13.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 131km; } <--> ofs_2.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 151km; } <--> ofs_25.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 159km; } <--> ofs_12.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 165km; } <--> ofs_9.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 174km; } <--> ofs_4.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 185km; } <--> ofs_19.gateCPlane++;
ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 230km; } <--> ofs_24.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 319km; } <--> ofs_3.gateCPlane++;
ofs_5.gateCPlane++ <--> DistanceChannel {  distance = 346km; } <--> ofs_15.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 352km; } <--> ofs_10.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 395km; } <--> ofs_17.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 418km; } <--> ofs_8.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 420km; } <--> ofs_14.gateCPlane++;
ofs_16.gateCPlane++ <--> DistanceChannel {  distance = 453km; } <--> ofs_21.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 465km; } <--> ofs_18.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 517km; } <--> ofs_5.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 766km; } <--> ofs_22.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 1091km; } <--> ofs_20.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 2002km; } <--> ofs_6.gateCPlane++;


ofs_2.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
ofs_16.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
ofs_7.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 1);

ofs_21.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
ofs_12.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 2);

ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
ofs_9.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 3);

ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 4);
ofs_20.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 4);
ofs_7.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 4);
ofs_17.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 4);

ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 5);
ofs_0.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 5);
ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 5);
ofs_17.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 5);

ofs_21.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 6);
ofs_14.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 6);
ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 6);
ofs_17.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 6);

ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 7);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 7);
ofs_11.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 7);
ofs_6.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 7);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 7);
ofs_25.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 7);

ofs_14.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 8);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 8);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 8);
ofs_20.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 8);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 8);
ofs_23.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 8);

ofs_11.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 9);
ofs_20.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 9);
ofs_3.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 9);
ofs_18.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 9);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 9);
ofs_25.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 9);
}