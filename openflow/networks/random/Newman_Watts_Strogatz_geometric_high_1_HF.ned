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


network Newman_Watts_Strogatz_geometric_high_1_HF
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
ofs_26: Open_Flow_Domain;
ofs_27: Open_Flow_Domain;
ofs_28: Open_Flow_Domain;
ofs_29: Open_Flow_Domain;
ofs_30: Open_Flow_Domain;
ofs_31: Open_Flow_Domain;
ofs_32: Open_Flow_Domain;
ofs_33: Open_Flow_Domain;
ofs_34: Open_Flow_Domain;
ofs_35: Open_Flow_Domain;
ofs_36: Open_Flow_Domain;
ofs_37: Open_Flow_Domain;
ofs_38: Open_Flow_Domain;
ofs_39: Open_Flow_Domain;

connections allowunconnected:
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 15857km; } <--> ofs_1.gateDPlane++;
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 16867km; } <--> ofs_39.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 4840km; } <--> ofs_2.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 4805km; } <--> ofs_3.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 21125km; } <--> ofs_4.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 10914km; } <--> ofs_5.gateDPlane++;
ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 7242km; } <--> ofs_6.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 1882km; } <--> ofs_7.gateDPlane++;
ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 2275km; } <--> ofs_8.gateDPlane++;
ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 1124km; } <--> ofs_9.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 3339km; } <--> ofs_10.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 23212km; } <--> ofs_11.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 12160km; } <--> ofs_12.gateDPlane++;
ofs_12.gateDPlane++ <--> DistanceChannel {  distance = 630km; } <--> ofs_13.gateDPlane++;
ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 128km; } <--> ofs_14.gateDPlane++;
ofs_14.gateDPlane++ <--> DistanceChannel {  distance = 11445km; } <--> ofs_15.gateDPlane++;
ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 3852km; } <--> ofs_16.gateDPlane++;
ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 1117km; } <--> ofs_17.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 5599km; } <--> ofs_18.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 5167km; } <--> ofs_23.gateDPlane++;
ofs_18.gateDPlane++ <--> DistanceChannel {  distance = 651km; } <--> ofs_19.gateDPlane++;
ofs_19.gateDPlane++ <--> DistanceChannel {  distance = 1503km; } <--> ofs_20.gateDPlane++;
ofs_19.gateDPlane++ <--> DistanceChannel {  distance = 310km; } <--> ofs_37.gateDPlane++;
ofs_20.gateDPlane++ <--> DistanceChannel {  distance = 1178km; } <--> ofs_21.gateDPlane++;
ofs_20.gateDPlane++ <--> DistanceChannel {  distance = 710km; } <--> ofs_28.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 1074km; } <--> ofs_22.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 5783km; } <--> ofs_31.gateDPlane++;
ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 254km; } <--> ofs_23.gateDPlane++;
ofs_23.gateDPlane++ <--> DistanceChannel {  distance = 538km; } <--> ofs_24.gateDPlane++;
ofs_23.gateDPlane++ <--> DistanceChannel {  distance = 721km; } <--> ofs_34.gateDPlane++;
ofs_24.gateDPlane++ <--> DistanceChannel {  distance = 1903km; } <--> ofs_25.gateDPlane++;
ofs_25.gateDPlane++ <--> DistanceChannel {  distance = 1775km; } <--> ofs_26.gateDPlane++;
ofs_26.gateDPlane++ <--> DistanceChannel {  distance = 1473km; } <--> ofs_27.gateDPlane++;
ofs_27.gateDPlane++ <--> DistanceChannel {  distance = 6942km; } <--> ofs_28.gateDPlane++;
ofs_27.gateDPlane++ <--> DistanceChannel {  distance = 31128km; } <--> ofs_36.gateDPlane++;
ofs_28.gateDPlane++ <--> DistanceChannel {  distance = 3818km; } <--> ofs_29.gateDPlane++;
ofs_29.gateDPlane++ <--> DistanceChannel {  distance = 14429km; } <--> ofs_30.gateDPlane++;
ofs_30.gateDPlane++ <--> DistanceChannel {  distance = 2526km; } <--> ofs_31.gateDPlane++;
ofs_31.gateDPlane++ <--> DistanceChannel {  distance = 565km; } <--> ofs_32.gateDPlane++;
ofs_32.gateDPlane++ <--> DistanceChannel {  distance = 2628km; } <--> ofs_33.gateDPlane++;
ofs_33.gateDPlane++ <--> DistanceChannel {  distance = 1756km; } <--> ofs_34.gateDPlane++;
ofs_34.gateDPlane++ <--> DistanceChannel {  distance = 3400km; } <--> ofs_35.gateDPlane++;
ofs_35.gateDPlane++ <--> DistanceChannel {  distance = 5351km; } <--> ofs_36.gateDPlane++;
ofs_36.gateDPlane++ <--> DistanceChannel {  distance = 3091km; } <--> ofs_37.gateDPlane++;
ofs_37.gateDPlane++ <--> DistanceChannel {  distance = 13678km; } <--> ofs_38.gateDPlane++;
ofs_38.gateDPlane++ <--> DistanceChannel {  distance = 10803km; } <--> ofs_39.gateDPlane++;

ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 128km; } <--> ofs_14.gateCPlane++;
ofs_22.gateCPlane++ <--> DistanceChannel {  distance = 254km; } <--> ofs_23.gateCPlane++;
ofs_19.gateCPlane++ <--> DistanceChannel {  distance = 310km; } <--> ofs_37.gateCPlane++;
ofs_23.gateCPlane++ <--> DistanceChannel {  distance = 538km; } <--> ofs_24.gateCPlane++;
ofs_31.gateCPlane++ <--> DistanceChannel {  distance = 565km; } <--> ofs_32.gateCPlane++;
ofs_12.gateCPlane++ <--> DistanceChannel {  distance = 630km; } <--> ofs_13.gateCPlane++;
ofs_18.gateCPlane++ <--> DistanceChannel {  distance = 651km; } <--> ofs_19.gateCPlane++;
ofs_20.gateCPlane++ <--> DistanceChannel {  distance = 710km; } <--> ofs_28.gateCPlane++;
ofs_23.gateCPlane++ <--> DistanceChannel {  distance = 721km; } <--> ofs_34.gateCPlane++;
ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 1074km; } <--> ofs_22.gateCPlane++;
ofs_16.gateCPlane++ <--> DistanceChannel {  distance = 1117km; } <--> ofs_17.gateCPlane++;
ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 1124km; } <--> ofs_9.gateCPlane++;
ofs_20.gateCPlane++ <--> DistanceChannel {  distance = 1178km; } <--> ofs_21.gateCPlane++;
ofs_26.gateCPlane++ <--> DistanceChannel {  distance = 1473km; } <--> ofs_27.gateCPlane++;
ofs_19.gateCPlane++ <--> DistanceChannel {  distance = 1503km; } <--> ofs_20.gateCPlane++;
ofs_33.gateCPlane++ <--> DistanceChannel {  distance = 1756km; } <--> ofs_34.gateCPlane++;
ofs_25.gateCPlane++ <--> DistanceChannel {  distance = 1775km; } <--> ofs_26.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 1882km; } <--> ofs_7.gateCPlane++;
ofs_24.gateCPlane++ <--> DistanceChannel {  distance = 1903km; } <--> ofs_25.gateCPlane++;
ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 2275km; } <--> ofs_8.gateCPlane++;
ofs_30.gateCPlane++ <--> DistanceChannel {  distance = 2526km; } <--> ofs_31.gateCPlane++;
ofs_32.gateCPlane++ <--> DistanceChannel {  distance = 2628km; } <--> ofs_33.gateCPlane++;
ofs_36.gateCPlane++ <--> DistanceChannel {  distance = 3091km; } <--> ofs_37.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 3339km; } <--> ofs_10.gateCPlane++;
ofs_34.gateCPlane++ <--> DistanceChannel {  distance = 3400km; } <--> ofs_35.gateCPlane++;
ofs_28.gateCPlane++ <--> DistanceChannel {  distance = 3818km; } <--> ofs_29.gateCPlane++;
ofs_15.gateCPlane++ <--> DistanceChannel {  distance = 3852km; } <--> ofs_16.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 4805km; } <--> ofs_3.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 4840km; } <--> ofs_2.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 5167km; } <--> ofs_23.gateCPlane++;
ofs_5.gateCPlane++ <--> DistanceChannel {  distance = 7242km; } <--> ofs_6.gateCPlane++;
ofs_38.gateCPlane++ <--> DistanceChannel {  distance = 10803km; } <--> ofs_39.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 10914km; } <--> ofs_5.gateCPlane++;
ofs_14.gateCPlane++ <--> DistanceChannel {  distance = 11445km; } <--> ofs_15.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 12160km; } <--> ofs_12.gateCPlane++;
ofs_37.gateCPlane++ <--> DistanceChannel {  distance = 13678km; } <--> ofs_38.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 15857km; } <--> ofs_1.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 16867km; } <--> ofs_39.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 21125km; } <--> ofs_4.gateCPlane++;


ofs_29.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
ofs_0.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
ofs_8.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 1);

ofs_21.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
ofs_38.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
ofs_8.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 2);

ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
ofs_38.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
ofs_8.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 3);

ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 4);
ofs_9.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 4);
ofs_33.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 4);
ofs_37.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 4);

ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 5);
ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 5);
ofs_6.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 5);
ofs_18.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 5);

ofs_16.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 6);
ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 6);
ofs_7.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 6);
ofs_2.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 6);

ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 7);
ofs_16.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 7);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 7);
ofs_37.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 7);
ofs_33.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 7);
ofs_5.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 7);

ofs_28.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 8);
ofs_7.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 8);
ofs_37.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 8);
ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 8);
ofs_3.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 8);
ofs_29.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 8);

ofs_6.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 9);
ofs_9.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 9);
ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 9);
ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 9);
ofs_37.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 9);
ofs_37.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 9);
}