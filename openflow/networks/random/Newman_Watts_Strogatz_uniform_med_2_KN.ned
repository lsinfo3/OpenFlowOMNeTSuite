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


network Newman_Watts_Strogatz_uniform_med_2_KN
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

connections allowunconnected:
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 609km; } <--> ofs_1.gateDPlane++;
ofs_0.gateDPlane++ <--> DistanceChannel {  distance = 105km; } <--> ofs_31.gateDPlane++;
ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 687km; } <--> ofs_2.gateDPlane++;
ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 109km; } <--> ofs_3.gateDPlane++;
ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 928km; } <--> ofs_4.gateDPlane++;
ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 377km; } <--> ofs_5.gateDPlane++;
ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 260km; } <--> ofs_6.gateDPlane++;
ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 438km; } <--> ofs_7.gateDPlane++;
ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 384km; } <--> ofs_8.gateDPlane++;
ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 267km; } <--> ofs_9.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 179km; } <--> ofs_10.gateDPlane++;
ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 611km; } <--> ofs_20.gateDPlane++;
ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 964km; } <--> ofs_11.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 794km; } <--> ofs_12.gateDPlane++;
ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 527km; } <--> ofs_20.gateDPlane++;
ofs_12.gateDPlane++ <--> DistanceChannel {  distance = 497km; } <--> ofs_13.gateDPlane++;
ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 732km; } <--> ofs_14.gateDPlane++;
ofs_14.gateDPlane++ <--> DistanceChannel {  distance = 874km; } <--> ofs_15.gateDPlane++;
ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 912km; } <--> ofs_16.gateDPlane++;
ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 884km; } <--> ofs_17.gateDPlane++;
ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 70km; } <--> ofs_18.gateDPlane++;
ofs_18.gateDPlane++ <--> DistanceChannel {  distance = 760km; } <--> ofs_19.gateDPlane++;
ofs_19.gateDPlane++ <--> DistanceChannel {  distance = 95km; } <--> ofs_20.gateDPlane++;
ofs_20.gateDPlane++ <--> DistanceChannel {  distance = 2km; } <--> ofs_21.gateDPlane++;
ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 508km; } <--> ofs_22.gateDPlane++;
ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 273km; } <--> ofs_23.gateDPlane++;
ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 242km; } <--> ofs_28.gateDPlane++;
ofs_23.gateDPlane++ <--> DistanceChannel {  distance = 833km; } <--> ofs_24.gateDPlane++;
ofs_24.gateDPlane++ <--> DistanceChannel {  distance = 160km; } <--> ofs_25.gateDPlane++;
ofs_25.gateDPlane++ <--> DistanceChannel {  distance = 225km; } <--> ofs_26.gateDPlane++;
ofs_26.gateDPlane++ <--> DistanceChannel {  distance = 422km; } <--> ofs_27.gateDPlane++;
ofs_27.gateDPlane++ <--> DistanceChannel {  distance = 580km; } <--> ofs_28.gateDPlane++;
ofs_28.gateDPlane++ <--> DistanceChannel {  distance = 862km; } <--> ofs_29.gateDPlane++;
ofs_29.gateDPlane++ <--> DistanceChannel {  distance = 260km; } <--> ofs_30.gateDPlane++;
ofs_30.gateDPlane++ <--> DistanceChannel {  distance = 335km; } <--> ofs_31.gateDPlane++;

ofs_20.gateCPlane++ <--> DistanceChannel {  distance = 2km; } <--> ofs_21.gateCPlane++;
ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 70km; } <--> ofs_18.gateCPlane++;
ofs_19.gateCPlane++ <--> DistanceChannel {  distance = 95km; } <--> ofs_20.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 105km; } <--> ofs_31.gateCPlane++;
ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 109km; } <--> ofs_3.gateCPlane++;
ofs_24.gateCPlane++ <--> DistanceChannel {  distance = 160km; } <--> ofs_25.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 179km; } <--> ofs_10.gateCPlane++;
ofs_25.gateCPlane++ <--> DistanceChannel {  distance = 225km; } <--> ofs_26.gateCPlane++;
ofs_22.gateCPlane++ <--> DistanceChannel {  distance = 242km; } <--> ofs_28.gateCPlane++;
ofs_5.gateCPlane++ <--> DistanceChannel {  distance = 260km; } <--> ofs_6.gateCPlane++;
ofs_29.gateCPlane++ <--> DistanceChannel {  distance = 260km; } <--> ofs_30.gateCPlane++;
ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 267km; } <--> ofs_9.gateCPlane++;
ofs_22.gateCPlane++ <--> DistanceChannel {  distance = 273km; } <--> ofs_23.gateCPlane++;
ofs_30.gateCPlane++ <--> DistanceChannel {  distance = 335km; } <--> ofs_31.gateCPlane++;
ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 377km; } <--> ofs_5.gateCPlane++;
ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 384km; } <--> ofs_8.gateCPlane++;
ofs_26.gateCPlane++ <--> DistanceChannel {  distance = 422km; } <--> ofs_27.gateCPlane++;
ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 438km; } <--> ofs_7.gateCPlane++;
ofs_12.gateCPlane++ <--> DistanceChannel {  distance = 497km; } <--> ofs_13.gateCPlane++;
ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 508km; } <--> ofs_22.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 527km; } <--> ofs_20.gateCPlane++;
ofs_27.gateCPlane++ <--> DistanceChannel {  distance = 580km; } <--> ofs_28.gateCPlane++;
ofs_0.gateCPlane++ <--> DistanceChannel {  distance = 609km; } <--> ofs_1.gateCPlane++;
ofs_9.gateCPlane++ <--> DistanceChannel {  distance = 611km; } <--> ofs_20.gateCPlane++;
ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 687km; } <--> ofs_2.gateCPlane++;
ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 732km; } <--> ofs_14.gateCPlane++;
ofs_18.gateCPlane++ <--> DistanceChannel {  distance = 760km; } <--> ofs_19.gateCPlane++;
ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 794km; } <--> ofs_12.gateCPlane++;
ofs_28.gateCPlane++ <--> DistanceChannel {  distance = 862km; } <--> ofs_29.gateCPlane++;
ofs_14.gateCPlane++ <--> DistanceChannel {  distance = 874km; } <--> ofs_15.gateCPlane++;
ofs_16.gateCPlane++ <--> DistanceChannel {  distance = 884km; } <--> ofs_17.gateCPlane++;


ofs_31.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
ofs_31.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 1);

ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
ofs_31.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
ofs_21.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 2);

ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
ofs_19.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
ofs_25.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 2 && placementID == 3);

ofs_22.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 4);
ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 4);
ofs_23.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 4);
ofs_19.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 4);

ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 5);
ofs_18.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 5);
ofs_21.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 5);
ofs_6.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 5);

ofs_4.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 6);
ofs_25.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 6);
ofs_0.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 6);
ofs_10.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 3 && placementID == 6);

ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 7);
ofs_4.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 7);
ofs_8.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 7);
ofs_30.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 7);
ofs_14.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 7);
ofs_16.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 7);

ofs_6.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 8);
ofs_15.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 8);
ofs_24.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 8);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 8);
ofs_20.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 8);
ofs_2.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 8);

ofs_11.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 9);
ofs_15.gateCPlane++ <--> backboneline <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 9);
ofs_10.gateCPlane++ <--> backboneline <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 9);
ofs_27.gateCPlane++ <--> backboneline <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 9);
ofs_1.gateCPlane++ <--> backboneline <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 9);
ofs_14.gateCPlane++ <--> backboneline <--> root.ethg++ if (numControllers == 5 && placementID == 9);
}