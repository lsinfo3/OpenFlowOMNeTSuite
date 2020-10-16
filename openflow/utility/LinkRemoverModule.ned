package openflow.utility;


simple LinkRemoverModule
{
    parameters:
	@display("i=spanning-tree");
        int intRemoved = default(0);
    	int numNodes = default(4);
        string NodeType = default("openflow.openflow.switch.Open_Flow_Switch");
        int startNode = default(0);
        int seedNum=default(0);
        int option=default(1);
}
