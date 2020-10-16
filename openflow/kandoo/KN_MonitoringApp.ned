package openflow.kandoo;
import openflow.controllerApps.*;

simple KN_MonitoringApp like AbstractControllerApp
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
