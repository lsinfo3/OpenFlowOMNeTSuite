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

package openflow.hyperflow;
import openflow.controllerApps.*;


simple HF_MonitoringApp like AbstractControllerApp
{
    parameters:     
         @signal[switches](type="int");
         @statistic[swID](title="switches"; source="switches"; record=vector,stats; interpolationmode=none);
         
         @signal[tableLengths](type="int");
         @statistic[tableLength](title="tableLengths"; source="tableLengths"; record=vector,stats; interpolationmode=none);
         
         @signal[avgNrOfPacketsMatched](type="double");
         @statistic[avgNrMatched](title="avgNrOfPacketsMatched"; source="avgNrOfPacketsMatched"; record=vector,stats; interpolationmode=none);
         
         @signal[avgBytesOfPacketsMatched](type="double");
         @statistic[avgBytesMatched](title="avgBytesOfPacketsMatched"; source="avgBytesOfPacketsMatched"; record=vector,stats; interpolationmode=none);
         
         @signal[timeDiff](type="double");
         @statistic[timeDiff](title="timeDiff"; source="timeDiff"; record=vector,stats; interpolationmode=none);
         
         @display("i=block/app");
          double pollInterval @unit("s") = default(2s);
}
