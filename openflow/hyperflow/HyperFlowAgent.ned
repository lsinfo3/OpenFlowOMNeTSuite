
import openflow.controllerApps.*;

package openflow.hyperflow;



simple HyperFlowAgent extends openflow.controllerApps.AbstractTCPControllerApp
{
    
    parameters:
        @signal[replysize](type="int");
        @statistic[replysize](title="replysize"; source="replysize"; record=vector,stats; interpolationmode=none);
        
        @class(HyperFlowAgent);
        @display("i=block/app");
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(1);
        int localPort = default(-1);
        string localAddress = default("");
        string connectAddressHyperFlowSynchronizer = default("HyperFlowSynchronizer");
        int connectPortHyperFlowSynchronizer = default(1003);
        
        double connectAt @unit("s") = default(1s);
        
        //should be 1/3 of the checkAliveEvery
        double reportInEvery @unit("s") = default(1s);
        double checkSyncEvery @unit("s") = default(1s);
        
        //should be the same as aliveintervall of the synchronizer module
        double checkAliveEvery @unit("s") = default(3s);
        
 
        
}
