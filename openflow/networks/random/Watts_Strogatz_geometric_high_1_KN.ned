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
//import openflow.hyperflow.*;


network Watts_Strogatz_geometric_high_1_KN
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

root: Open_Flow_Controller {
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

connections allowunconnected:
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 7598km; } <--> ofs_29.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 926km; } <--> ofs_10.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 2343km; } <--> ofs_22.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 2671km; } <--> ofs_3.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 5798km; } <--> ofs_14.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 1754km; } <--> ofs_17.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 1807km; } <--> ofs_9.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 2200km; } <--> ofs_23.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 8311km; } <--> ofs_20.gateDPlane++;
ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 4309km; } <--> ofs_6.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 392km; } <--> ofs_9.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 408km; } <--> ofs_25.gateDPlane++;
ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 2321km; } <--> ofs_19.gateDPlane++;
ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 7275km; } <--> ofs_10.gateDPlane++;
ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 5835km; } <--> ofs_19.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 6155km; } <--> ofs_24.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 7288km; } <--> ofs_11.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 1693km; } <--> ofs_32.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 3973km; } <--> ofs_13.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 3919km; } <--> ofs_27.gateDPlane++;
ofs_12.gateDPlane++ <--> DistanceChannel {  distance = 6728km; } <--> ofs_13.gateDPlane++;
ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 15717km; } <--> ofs_18.gateDPlane++;
ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 1629km; } <--> ofs_38.gateDPlane++;
ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 7882km; } <--> ofs_32.gateDPlane++;
ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 5394km; } <--> ofs_22.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 4340km; } <--> ofs_28.gateDPlane++;
ofs_18.gateDPlane++ <--> DistanceChannel {  distance = 7455km; } <--> ofs_19.gateDPlane++;
ofs_18.gateDPlane++ <--> DistanceChannel {  distance = 14414km; } <--> ofs_34.gateDPlane++;
ofs_20.gateDPlane++ <--> DistanceChannel {  distance = 187km; } <--> ofs_27.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 798km; } <--> ofs_36.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 7059km; } <--> ofs_35.gateDPlane++;
ofs_23.gateDPlane++ <--> DistanceChannel {  distance = 438km; } <--> ofs_30.gateDPlane++;
ofs_26.gateDPlane++ <--> DistanceChannel {  distance = 3630km; } <--> ofs_27.gateDPlane++;
ofs_28.gateDPlane++ <--> DistanceChannel {  distance = 1242km; } <--> ofs_29.gateDPlane++;
ofs_29.gateDPlane++ <--> DistanceChannel {  distance = 1603km; } <--> ofs_31.gateDPlane++;
ofs_31.gateDPlane++ <--> DistanceChannel {  distance = 6051km; } <--> ofs_35.gateDPlane++;
ofs_33.gateDPlane++ <--> DistanceChannel {  distance = 154km; } <--> ofs_34.gateDPlane++;
ofs_33.gateDPlane++ <--> DistanceChannel {  distance = 10330km; } <--> ofs_37.gateDPlane++;
ofs_36.gateDPlane++ <--> DistanceChannel {  distance = 2939km; } <--> ofs_37.gateDPlane++;

ofs_33.gateCPlane++ <--> DistanceChannel {  distance = 154km; } <--> ofs_34.gateCPlane++;
ofs_20.gateCPlane++ <--> DistanceChannel {  distance = 187km; } <--> ofs_27.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 392km; } <--> ofs_9.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 408km; } <--> ofs_25.gateCPlane++;
ofs_23.gateCPlane++ <--> DistanceChannel {  distance = 438km; } <--> ofs_30.gateCPlane++;
ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 798km; } <--> ofs_36.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 926km; } <--> ofs_10.gateCPlane++;
ofs_28.gateCPlane++ <--> DistanceChannel {  distance = 1242km; } <--> ofs_29.gateCPlane++;
ofs_29.gateCPlane++ <--> DistanceChannel {  distance = 1603km; } <--> ofs_31.gateCPlane++;
ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 1629km; } <--> ofs_38.gateCPlane++;
ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 1693km; } <--> ofs_32.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 1754km; } <--> ofs_17.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 1807km; } <--> ofs_9.gateCPlane++;
ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 2200km; } <--> ofs_23.gateCPlane++;
ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 2321km; } <--> ofs_19.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 2343km; } <--> ofs_22.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 2671km; } <--> ofs_3.gateCPlane++;
ofs_36.gateCPlane++ <--> DistanceChannel {  distance = 2939km; } <--> ofs_37.gateCPlane++;
ofs_26.gateCPlane++ <--> DistanceChannel {  distance = 3630km; } <--> ofs_27.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 3919km; } <--> ofs_27.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 3973km; } <--> ofs_13.gateCPlane++;
ofs_5.gateCPlane++ <--> DistanceChannel {  distance = 4309km; } <--> ofs_6.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 4340km; } <--> ofs_28.gateCPlane++;
ofs_16.gateCPlane++ <--> DistanceChannel {  distance = 5394km; } <--> ofs_22.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 5798km; } <--> ofs_14.gateCPlane++;
ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 5835km; } <--> ofs_19.gateCPlane++;
ofs_31.gateCPlane++ <--> DistanceChannel {  distance = 6051km; } <--> ofs_35.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 6155km; } <--> ofs_24.gateCPlane++;
ofs_12.gateCPlane++ <--> DistanceChannel {  distance = 6728km; } <--> ofs_13.gateCPlane++;
ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 7059km; } <--> ofs_35.gateCPlane++;
ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 7275km; } <--> ofs_10.gateCPlane++;
ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 7288km; } <--> ofs_11.gateCPlane++;
ofs_18.gateCPlane++ <--> DistanceChannel {  distance = 7455km; } <--> ofs_19.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 7598km; } <--> ofs_29.gateCPlane++;
ofs_15.gateCPlane++ <--> DistanceChannel {  distance = 7882km; } <--> ofs_32.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 8311km; } <--> ofs_20.gateCPlane++;
ofs_33.gateCPlane++ <--> DistanceChannel {  distance = 10330km; } <--> ofs_37.gateCPlane++;
ofs_18.gateCPlane++ <--> DistanceChannel {  distance = 14414km; } <--> ofs_34.gateCPlane++;


ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
ofs_9.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 1);

ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
ofs_23.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 2);

ofs_35.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
ofs_36.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
ofs_4.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 3);

ofs_22.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 4);
ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 4);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 4);
ofs_24.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 4);

ofs_13.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 5);
ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 5);
ofs_6.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 5);
ofs_6.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 5);

ofs_0.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 6);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 6);
ofs_12.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 6);
ofs_33.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 6);

ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 7);
ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 7);
ofs_33.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 7);
ofs_26.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 7);
ofs_15.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 7);
ofs_24.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 7);

ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 8);
ofs_17.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 8);
ofs_16.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 8);
ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 8);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 8);
ofs_10.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 8);

ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 9);
ofs_35.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 9);
ofs_26.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 9);
ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 9);
ofs_31.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 9);
ofs_29.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 9);
}