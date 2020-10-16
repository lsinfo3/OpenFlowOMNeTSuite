

package openflow.kandoo;
import openflow.controllerApps.*;

simple KN_LLDPAgent like AbstractControllerApp
{
    parameters:
        @signal[timeDiff](type="double");
        @statistic[timeDiff](title="timeDiff"; source="timeDiff"; record=vector,stats; interpolationmode=none);
         
        @display("i=block/app");
        
        //default value cisco
        double pollInterval @unit("s") = default(30s);
        
        //default value cisco
        double timeOut @unit("s") = default(120s);
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(60);
        bool printMibGraph = default(false);
        
}
