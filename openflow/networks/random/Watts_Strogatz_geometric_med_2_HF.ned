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


network Watts_Strogatz_geometric_med_2_HF
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

connections allowunconnected:
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 222km; } <--> ofs_4.gateDPlane++;
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 7km; } <--> ofs_10.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 650km; } <--> ofs_6.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 332km; } <--> ofs_12.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 1091km; } <--> ofs_30.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 93km; } <--> ofs_25.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 140km; } <--> ofs_18.gateDPlane++;
ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 319km; } <--> ofs_6.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 73km; } <--> ofs_12.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 224km; } <--> ofs_8.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 8km; } <--> ofs_18.gateDPlane++;
ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 809km; } <--> ofs_18.gateDPlane++;
ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 54km; } <--> ofs_25.gateDPlane++;
ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 453km; } <--> ofs_16.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 152km; } <--> ofs_13.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 16km; } <--> ofs_27.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 59km; } <--> ofs_31.gateDPlane++;
ofs_12.gateDPlane++ <--> DistanceChannel {  distance = 601km; } <--> ofs_13.gateDPlane++;
ofs_12.gateDPlane++ <--> DistanceChannel {  distance = 1108km; } <--> ofs_19.gateDPlane++;
ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 29km; } <--> ofs_17.gateDPlane++;
ofs_14.gateDPlane++ <--> DistanceChannel {  distance = 166km; } <--> ofs_25.gateDPlane++;
ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 254km; } <--> ofs_24.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 1923km; } <--> ofs_25.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 293km; } <--> ofs_23.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 871km; } <--> ofs_29.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 165km; } <--> ofs_32.gateDPlane++;
ofs_20.gateDPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_27.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 874km; } <--> ofs_24.gateDPlane++;
ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 732km; } <--> ofs_23.gateDPlane++;
ofs_24.gateDPlane++ <--> DistanceChannel {  distance = 137km; } <--> ofs_25.gateDPlane++;
ofs_26.gateDPlane++ <--> DistanceChannel {  distance = 146km; } <--> ofs_28.gateDPlane++;
ofs_28.gateDPlane++ <--> DistanceChannel {  distance = 398km; } <--> ofs_30.gateDPlane++;
ofs_31.gateDPlane++ <--> DistanceChannel {  distance = 1390km; } <--> ofs_32.gateDPlane++;

ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 7km; } <--> ofs_10.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 8km; } <--> ofs_18.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 16km; } <--> ofs_27.gateCPlane++;
ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 29km; } <--> ofs_17.gateCPlane++;
ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 54km; } <--> ofs_25.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 59km; } <--> ofs_31.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 73km; } <--> ofs_12.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 93km; } <--> ofs_25.gateCPlane++;
ofs_24.gateCPlane++ <--> DistanceChannel {  distance = 137km; } <--> ofs_25.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 140km; } <--> ofs_18.gateCPlane++;
ofs_26.gateCPlane++ <--> DistanceChannel {  distance = 146km; } <--> ofs_28.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 152km; } <--> ofs_13.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 165km; } <--> ofs_32.gateCPlane++;
ofs_14.gateCPlane++ <--> DistanceChannel {  distance = 166km; } <--> ofs_25.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 222km; } <--> ofs_4.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 224km; } <--> ofs_8.gateCPlane++;
ofs_15.gateCPlane++ <--> DistanceChannel {  distance = 254km; } <--> ofs_24.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 293km; } <--> ofs_23.gateCPlane++;
ofs_20.gateCPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_27.gateCPlane++;
ofs_5.gateCPlane++ <--> DistanceChannel {  distance = 319km; } <--> ofs_6.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 332km; } <--> ofs_12.gateCPlane++;
ofs_28.gateCPlane++ <--> DistanceChannel {  distance = 398km; } <--> ofs_30.gateCPlane++;
ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 453km; } <--> ofs_16.gateCPlane++;
ofs_12.gateCPlane++ <--> DistanceChannel {  distance = 601km; } <--> ofs_13.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 650km; } <--> ofs_6.gateCPlane++;
ofs_22.gateCPlane++ <--> DistanceChannel {  distance = 732km; } <--> ofs_23.gateCPlane++;
ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 809km; } <--> ofs_18.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 871km; } <--> ofs_29.gateCPlane++;
ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 874km; } <--> ofs_24.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 1091km; } <--> ofs_30.gateCPlane++;
ofs_12.gateCPlane++ <--> DistanceChannel {  distance = 1108km; } <--> ofs_19.gateCPlane++;
ofs_31.gateCPlane++ <--> DistanceChannel {  distance = 1390km; } <--> ofs_32.gateCPlane++;


ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
ofs_13.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
ofs_21.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 1);

ofs_14.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
ofs_28.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 2);

ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
ofs_29.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
ofs_1.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 2 && placementID == 3);

ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 4);
ofs_7.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 4);
ofs_5.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 4);
ofs_17.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 4);

ofs_22.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 5);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 5);
ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 5);
ofs_13.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 5);

ofs_9.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 6);
ofs_28.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 6);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 6);
ofs_17.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 3 && placementID == 6);

ofs_26.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 7);
ofs_20.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 7);
ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 7);
ofs_9.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 7);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 7);
ofs_31.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 7);

ofs_28.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 8);
ofs_22.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 8);
ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 8);
ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 8);
ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 8);
ofs_21.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 8);

ofs_18.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 9);
ofs_5.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 9);
ofs_28.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 9);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 9);
ofs_9.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 9);
ofs_1.gateCPlane++ <--> backboneline <--> hf_synchronizer.ethg++ if (numControllers == 5 && placementID == 9);
}