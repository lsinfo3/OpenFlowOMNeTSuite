#
# OMNeT++/OMNEST Makefile for openflow_executable
#
# This file was generated with the command:
#  opp_makemake -f --deep -o openflow_executable -O out -I/home/nicholas/omnetpp/samples/inet/src/linklayer/ieee80211/radio -I/home/nicholas/omnetpp/samples/inet/src/linklayer/ethernet -I/home/nicholas/omnetpp/samples/inet/src/networklayer/routing/aodv -I/home/nicholas/omnetpp/samples/inet/src/networklayer/common -I/home/nicholas/omnetpp/samples/inet/src -I/home/nicholas/omnetpp/samples/inet/src/networklayer/icmpv6 -I/home/nicholas/omnetpp/samples/inet/src/transport/tcp -I/home/nicholas/omnetpp/samples/inet/src/world/obstacles -I/home/nicholas/omnetpp/samples/inet/src/transport/tcp/queues -I/home/nicholas/omnetpp/samples/inet/src/networklayer/xmipv6 -I/home/nicholas/omnetpp/samples/inet/src/networklayer/contract -I/home/nicholas/omnetpp/samples/inet/src/networklayer/autorouting/ipv4 -I/home/nicholas/omnetpp/samples/inet/src/util -I/home/nicholas/omnetpp/samples/inet/src/linklayer/common -I/home/nicholas/omnetpp/samples/inet/src/transport/contract -I/home/nicholas/omnetpp/samples/inet/src/status -I/home/nicholas/omnetpp/samples/inet/src/applications/tcpapp -I/home/nicholas/omnetpp/samples/inet/src/linklayer/radio/propagation -I/home/nicholas/omnetpp/samples/inet/src/linklayer/ieee80211/radio/errormodel -I/home/nicholas/omnetpp/samples/inet/src/linklayer/radio -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers/tcp -I/home/nicholas/omnetpp/samples/inet/src/networklayer/ipv4 -I/home/nicholas/omnetpp/samples/inet/src/mobility/contract -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers/ipv4 -I/home/nicholas/omnetpp/samples/inet/src/base -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers -I/home/nicholas/omnetpp/samples/inet/src/world/radio -I/home/nicholas/omnetpp/samples/inet/src/linklayer/ieee80211/mac -I/home/nicholas/omnetpp/samples/inet/src/networklayer/ipv6 -I/home/nicholas/omnetpp/samples/inet/src/transport/sctp -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers/udp -I/home/nicholas/omnetpp/samples/inet/src/networklayer/ipv6tunneling -I/home/nicholas/omnetpp/samples/inet/src/applications/pingapp -I/home/nicholas/omnetpp/samples/inet/src/battery/models -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers/ipv6 -I/home/nicholas/omnetpp/samples/inet/src/util/headerserializers/sctp -I/home/nicholas/omnetpp/samples/inet/src/linklayer/contract -I/home/nicholas/omnetpp/samples/inet/src/transport/tcp_common -I/home/nicholas/omnetpp/samples/inet/src/networklayer/arp -I/home/nicholas/omnetpp/samples/inet/src/transport/udp -L/home/nicholas/omnetpp/samples/inet/out/$$\(CONFIGNAME\)/src -linet -DINET_IMPORT -KINET_PROJ=/home/nicholas/omnetpp/samples/inet
#

# Name of target to be created (-o option)
TARGET = openflow_executable$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio \
    -I$(INET_PROJ)/src/linklayer/ethernet \
    -I$(INET_PROJ)/src/networklayer/routing/aodv \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src \
    -I$(INET_PROJ)/src/networklayer/icmpv6 \
    -I$(INET_PROJ)/src/transport/tcp \
    -I$(INET_PROJ)/src/world/obstacles \
    -I$(INET_PROJ)/src/transport/tcp/queues \
    -I$(INET_PROJ)/src/networklayer/xmipv6 \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(INET_PROJ)/src/networklayer/autorouting/ipv4 \
    -I$(INET_PROJ)/src/util \
    -I$(INET_PROJ)/src/linklayer/common \
    -I$(INET_PROJ)/src/transport/contract \
    -I$(INET_PROJ)/src/status \
    -I$(INET_PROJ)/src/applications/tcpapp \
    -I$(INET_PROJ)/src/linklayer/radio/propagation \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio/errormodel \
    -I$(INET_PROJ)/src/linklayer/radio \
    -I$(INET_PROJ)/src/util/headerserializers/tcp \
    -I$(INET_PROJ)/src/networklayer/ipv4 \
    -I$(INET_PROJ)/src/mobility/contract \
    -I$(INET_PROJ)/src/util/headerserializers/ipv4 \
    -I$(INET_PROJ)/src/base \
    -I$(INET_PROJ)/src/util/headerserializers \
    -I$(INET_PROJ)/src/world/radio \
    -I$(INET_PROJ)/src/linklayer/ieee80211/mac \
    -I$(INET_PROJ)/src/networklayer/ipv6 \
    -I$(INET_PROJ)/src/transport/sctp \
    -I$(INET_PROJ)/src/util/headerserializers/udp \
    -I$(INET_PROJ)/src/networklayer/ipv6tunneling \
    -I$(INET_PROJ)/src/applications/pingapp \
    -I$(INET_PROJ)/src/battery/models \
    -I$(INET_PROJ)/src/util/headerserializers/ipv6 \
    -I$(INET_PROJ)/src/util/headerserializers/sctp \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I$(INET_PROJ)/src/transport/tcp_common \
    -I$(INET_PROJ)/src/networklayer/arp \
    -I$(INET_PROJ)/src/transport/udp \
    -I. \
    -IcontrollerApps \
    -IhostApps \
    -Ihyperflow \
    -Iimages \
    -Ikandoo \
    -Imessages \
    -ImodifiedInetFiles \
    -Inetworks \
    -Inodes \
    -Iopenflow \
    -Iopenflow/controller \
    -Iopenflow/protocol \
    -Iopenflow/switch \
    -Iscenarios \
    -Iscenarios/fattree \
    -Iscenarios/hyperflow \
    -Iscenarios/hyperflow/fattree \
    -Iscenarios/hyperflow/usa \
    -Iscenarios/hyperflow/usa/results \
    -Iscenarios/hyperflow/usa/results/Scenario_USA_ARP_HF_Ping_5C.ini \
    -Iscenarios/kandoo \
    -Iscenarios/kandoo/fattree \
    -Iscenarios/kandoo/fattree/results \
    -Iscenarios/kandoo/usa \
    -Iscenarios/kandoo/usa/results \
    -Iscenarios/testcases \
    -Iscenarios/testcases/results \
    -Iscenarios/testcases/results/Scenario_TestCase_Diamond.ini \
    -Iscenarios/testcases/results/Scenario_TestCase_LearningSwitch.ini \
    -Iscenarios/topologyzoo \
    -Iscenarios/topologyzoo/results \
    -Iscenarios/usa \
    -Iscenarios/usa/results \
    -Iscenarios/usa/results/Scenario_USA_ARP_Ping_Drop.ini \
    -Iutility

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/controllerApps/AbstractControllerApp.o \
    $O/controllerApps/ARPResponder.o \
    $O/controllerApps/LLDPForwarding.o \
    $O/controllerApps/LLDPMib.o \
    $O/controllerApps/LLDPMibGraph.o \
    $O/controllerApps/LLDPBalancedMinHop.o \
    $O/controllerApps/LearningSwitch.o \
    $O/controllerApps/AbstractTCPControllerApp.o \
    $O/controllerApps/LLDPAgent.o \
    $O/controllerApps/Hub.o \
    $O/hostApps/TCPTrafficGeneratorApp.o \
    $O/hostApps/TCPTrafficSinkApp.o \
    $O/hostApps/LocalityPingAppRandom.o \
    $O/hostApps/PingAppRandom.o \
    $O/hyperflow/HyperFlowSynchronizer.o \
    $O/hyperflow/HF_ReFire_Wrapper.o \
    $O/hyperflow/HF_ARPResponder.o \
    $O/hyperflow/HF_LLDPAgent.o \
    $O/hyperflow/HyperFlowAgent.o \
    $O/kandoo/KandooAgent.o \
    $O/kandoo/KN_LLDPBalancedMinHop.o \
    $O/kandoo/KN_ARPResponder.o \
    $O/kandoo/KN_LLDPForwarding.o \
    $O/kandoo/KN_LLDPAgent.o \
    $O/openflow/controller/OF_Controller.o \
    $O/openflow/controller/Switch_Info.o \
    $O/openflow/switch/OF_Switch.o \
    $O/openflow/switch/Flow_Table.o \
    $O/openflow/switch/Buffer.o \
    $O/openflow/switch/Flow_Table_Entry.o \
    $O/utility/OpenFlowGraphAnalyzer.o \
    $O/utility/ControllerInvolvmentFilter.o \
    $O/utility/LLDP_Wrapper.o \
    $O/utility/ARP_Wrapper.o \
    $O/utility/StaticSpanningTree.o \
    $O/messages/Open_Flow_Message_m.o \
    $O/messages/OFP_Port_Mod_m.o \
    $O/messages/HF_ReportIn_m.o \
    $O/messages/HF_SyncReply_m.o \
    $O/messages/LLDP_m.o \
    $O/messages/OFP_Packet_In_m.o \
    $O/messages/KN_Packet_m.o \
    $O/messages/OFP_Features_Reply_m.o \
    $O/messages/OFP_Hello_m.o \
    $O/messages/HF_SyncRequest_m.o \
    $O/messages/HF_ChangeNotification_m.o \
    $O/messages/OFP_Packet_Out_m.o \
    $O/messages/OFP_Flow_Mod_m.o \
    $O/messages/OFP_Initialize_Handshake_m.o \
    $O/messages/OFP_Features_Request_m.o

# Message files
MSGFILES = \
    messages/Open_Flow_Message.msg \
    messages/OFP_Port_Mod.msg \
    messages/HF_ReportIn.msg \
    messages/HF_SyncReply.msg \
    messages/LLDP.msg \
    messages/OFP_Packet_In.msg \
    messages/KN_Packet.msg \
    messages/OFP_Features_Reply.msg \
    messages/OFP_Hello.msg \
    messages/HF_SyncRequest.msg \
    messages/HF_ChangeNotification.msg \
    messages/OFP_Packet_Out.msg \
    messages/OFP_Flow_Mod.msg \
    messages/OFP_Initialize_Handshake.msg \
    messages/OFP_Features_Request.msg

# Other makefile variables (-K)
INET_PROJ=/home/nicholas/omnetpp/samples/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f openflow_executable openflow_executable.exe libopenflow_executable.so libopenflow_executable.a libopenflow_executable.dll libopenflow_executable.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f controllerApps/*_m.cc controllerApps/*_m.h
	$(Q)-rm -f hostApps/*_m.cc hostApps/*_m.h
	$(Q)-rm -f hyperflow/*_m.cc hyperflow/*_m.h
	$(Q)-rm -f images/*_m.cc images/*_m.h
	$(Q)-rm -f kandoo/*_m.cc kandoo/*_m.h
	$(Q)-rm -f messages/*_m.cc messages/*_m.h
	$(Q)-rm -f modifiedInetFiles/*_m.cc modifiedInetFiles/*_m.h
	$(Q)-rm -f networks/*_m.cc networks/*_m.h
	$(Q)-rm -f nodes/*_m.cc nodes/*_m.h
	$(Q)-rm -f openflow/*_m.cc openflow/*_m.h
	$(Q)-rm -f openflow/controller/*_m.cc openflow/controller/*_m.h
	$(Q)-rm -f openflow/protocol/*_m.cc openflow/protocol/*_m.h
	$(Q)-rm -f openflow/switch/*_m.cc openflow/switch/*_m.h
	$(Q)-rm -f scenarios/*_m.cc scenarios/*_m.h
	$(Q)-rm -f scenarios/fattree/*_m.cc scenarios/fattree/*_m.h
	$(Q)-rm -f scenarios/hyperflow/*_m.cc scenarios/hyperflow/*_m.h
	$(Q)-rm -f scenarios/hyperflow/fattree/*_m.cc scenarios/hyperflow/fattree/*_m.h
	$(Q)-rm -f scenarios/hyperflow/usa/*_m.cc scenarios/hyperflow/usa/*_m.h
	$(Q)-rm -f scenarios/hyperflow/usa/results/*_m.cc scenarios/hyperflow/usa/results/*_m.h
	$(Q)-rm -f scenarios/hyperflow/usa/results/Scenario_USA_ARP_HF_Ping_5C.ini/*_m.cc scenarios/hyperflow/usa/results/Scenario_USA_ARP_HF_Ping_5C.ini/*_m.h
	$(Q)-rm -f scenarios/kandoo/*_m.cc scenarios/kandoo/*_m.h
	$(Q)-rm -f scenarios/kandoo/fattree/*_m.cc scenarios/kandoo/fattree/*_m.h
	$(Q)-rm -f scenarios/kandoo/fattree/results/*_m.cc scenarios/kandoo/fattree/results/*_m.h
	$(Q)-rm -f scenarios/kandoo/usa/*_m.cc scenarios/kandoo/usa/*_m.h
	$(Q)-rm -f scenarios/kandoo/usa/results/*_m.cc scenarios/kandoo/usa/results/*_m.h
	$(Q)-rm -f scenarios/testcases/*_m.cc scenarios/testcases/*_m.h
	$(Q)-rm -f scenarios/testcases/results/*_m.cc scenarios/testcases/results/*_m.h
	$(Q)-rm -f scenarios/testcases/results/Scenario_TestCase_Diamond.ini/*_m.cc scenarios/testcases/results/Scenario_TestCase_Diamond.ini/*_m.h
	$(Q)-rm -f scenarios/testcases/results/Scenario_TestCase_LearningSwitch.ini/*_m.cc scenarios/testcases/results/Scenario_TestCase_LearningSwitch.ini/*_m.h
	$(Q)-rm -f scenarios/topologyzoo/*_m.cc scenarios/topologyzoo/*_m.h
	$(Q)-rm -f scenarios/topologyzoo/results/*_m.cc scenarios/topologyzoo/results/*_m.h
	$(Q)-rm -f scenarios/usa/*_m.cc scenarios/usa/*_m.h
	$(Q)-rm -f scenarios/usa/results/*_m.cc scenarios/usa/results/*_m.h
	$(Q)-rm -f scenarios/usa/results/Scenario_USA_ARP_Ping_Drop.ini/*_m.cc scenarios/usa/results/Scenario_USA_ARP_Ping_Drop.ini/*_m.h
	$(Q)-rm -f utility/*_m.cc utility/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc controllerApps/*.cc hostApps/*.cc hyperflow/*.cc images/*.cc kandoo/*.cc messages/*.cc modifiedInetFiles/*.cc networks/*.cc nodes/*.cc openflow/*.cc openflow/controller/*.cc openflow/protocol/*.cc openflow/switch/*.cc scenarios/*.cc scenarios/fattree/*.cc scenarios/hyperflow/*.cc scenarios/hyperflow/fattree/*.cc scenarios/hyperflow/usa/*.cc scenarios/hyperflow/usa/results/*.cc scenarios/hyperflow/usa/results/Scenario_USA_ARP_HF_Ping_5C.ini/*.cc scenarios/kandoo/*.cc scenarios/kandoo/fattree/*.cc scenarios/kandoo/fattree/results/*.cc scenarios/kandoo/usa/*.cc scenarios/kandoo/usa/results/*.cc scenarios/testcases/*.cc scenarios/testcases/results/*.cc scenarios/testcases/results/Scenario_TestCase_Diamond.ini/*.cc scenarios/testcases/results/Scenario_TestCase_LearningSwitch.ini/*.cc scenarios/topologyzoo/*.cc scenarios/topologyzoo/results/*.cc scenarios/usa/*.cc scenarios/usa/results/*.cc scenarios/usa/results/Scenario_USA_ARP_Ping_Drop.ini/*.cc utility/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/controllerApps/ARPResponder.o: controllerApps/ARPResponder.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/ARPResponder.h \
	controllerApps/AbstractControllerApp.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/AbstractControllerApp.o: controllerApps/AbstractControllerApp.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/AbstractTCPControllerApp.o: controllerApps/AbstractTCPControllerApp.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/Hub.o: controllerApps/Hub.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/Hub.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/LLDPAgent.o: controllerApps/LLDPAgent.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/LLDPBalancedMinHop.o: controllerApps/LLDPBalancedMinHop.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPBalancedMinHop.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/LLDPForwarding.o: controllerApps/LLDPForwarding.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPForwarding.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/controllerApps/LLDPMib.o: controllerApps/LLDPMib.cc \
	controllerApps/LLDPMib.h
$O/controllerApps/LLDPMibGraph.o: controllerApps/LLDPMibGraph.cc \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h
$O/controllerApps/LearningSwitch.o: controllerApps/LearningSwitch.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/LearningSwitch.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/hostApps/LocalityPingAppRandom.o: hostApps/LocalityPingAppRandom.cc \
	$(INET_PROJ)/src/applications/pingapp/PingApp.h \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	hostApps/LocalityPingAppRandom.h
$O/hostApps/PingAppRandom.o: hostApps/PingAppRandom.cc \
	$(INET_PROJ)/src/applications/pingapp/PingApp.h \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	hostApps/PingAppRandom.h
$O/hostApps/TCPTrafficGeneratorApp.o: hostApps/TCPTrafficGeneratorApp.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hostApps/TCPTrafficGeneratorApp.h
$O/hostApps/TCPTrafficSinkApp.o: hostApps/TCPTrafficSinkApp.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hostApps/TCPTrafficSinkApp.h
$O/hyperflow/HF_ARPResponder.o: hyperflow/HF_ARPResponder.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/ARPResponder.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	hyperflow/HF_ARPResponder.h \
	hyperflow/HF_ReFire_Wrapper.h \
	hyperflow/HyperFlowAgent.h \
	hyperflow/HyperFlowStructs.h \
	messages/HF_ChangeNotification_m.h \
	messages/HF_ReportIn_m.h \
	messages/HF_SyncReply_m.h \
	messages/HF_SyncRequest_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/ARP_Wrapper.h
$O/hyperflow/HF_LLDPAgent.o: hyperflow/HF_LLDPAgent.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	hyperflow/HF_LLDPAgent.h \
	hyperflow/HF_ReFire_Wrapper.h \
	hyperflow/HyperFlowAgent.h \
	hyperflow/HyperFlowStructs.h \
	messages/HF_ChangeNotification_m.h \
	messages/HF_ReportIn_m.h \
	messages/HF_SyncReply_m.h \
	messages/HF_SyncRequest_m.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/LLDP_Wrapper.h
$O/hyperflow/HF_ReFire_Wrapper.o: hyperflow/HF_ReFire_Wrapper.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hyperflow/HF_ReFire_Wrapper.h \
	hyperflow/HyperFlowStructs.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/hyperflow/HyperFlowAgent.o: hyperflow/HyperFlowAgent.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	hyperflow/HF_ReFire_Wrapper.h \
	hyperflow/HyperFlowAgent.h \
	hyperflow/HyperFlowStructs.h \
	messages/HF_ChangeNotification_m.h \
	messages/HF_ReportIn_m.h \
	messages/HF_SyncReply_m.h \
	messages/HF_SyncRequest_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/hyperflow/HyperFlowSynchronizer.o: hyperflow/HyperFlowSynchronizer.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hyperflow/HyperFlowStructs.h \
	hyperflow/HyperFlowSynchronizer.h \
	messages/HF_ChangeNotification_m.h \
	messages/HF_ReportIn_m.h \
	messages/HF_SyncReply_m.h \
	messages/HF_SyncRequest_m.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/kandoo/KN_ARPResponder.o: kandoo/KN_ARPResponder.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/ARPResponder.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	kandoo/KN_ARPResponder.h \
	kandoo/KandooAgent.h \
	messages/KN_Packet_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/ARP_Wrapper.h \
	utility/KandooStructs.h
$O/kandoo/KN_LLDPAgent.o: kandoo/KN_LLDPAgent.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	kandoo/KN_LLDPAgent.h \
	kandoo/KandooAgent.h \
	messages/KN_Packet_m.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/KandooStructs.h \
	utility/LLDP_Wrapper.h
$O/kandoo/KN_LLDPBalancedMinHop.o: kandoo/KN_LLDPBalancedMinHop.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPBalancedMinHop.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	kandoo/KN_LLDPBalancedMinHop.h \
	kandoo/KandooAgent.h \
	messages/KN_Packet_m.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/KandooStructs.h
$O/kandoo/KN_LLDPForwarding.o: kandoo/KN_LLDPForwarding.cc \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage_m.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	controllerApps/LLDPAgent.h \
	controllerApps/LLDPForwarding.h \
	controllerApps/LLDPMib.h \
	controllerApps/LLDPMibGraph.h \
	kandoo/KN_LLDPForwarding.h \
	kandoo/KandooAgent.h \
	messages/KN_Packet_m.h \
	messages/LLDP_m.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/KandooStructs.h
$O/kandoo/KandooAgent.o: kandoo/KandooAgent.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	controllerApps/AbstractControllerApp.h \
	controllerApps/AbstractTCPControllerApp.h \
	kandoo/KandooAgent.h \
	messages/KN_Packet_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h \
	utility/KandooStructs.h
$O/messages/HF_ChangeNotification_m.o: messages/HF_ChangeNotification_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hyperflow/HyperFlowStructs.h \
	messages/HF_ChangeNotification_m.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/messages/HF_ReportIn_m.o: messages/HF_ReportIn_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	messages/HF_ReportIn_m.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/messages/HF_SyncReply_m.o: messages/HF_SyncReply_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	hyperflow/HyperFlowStructs.h \
	messages/HF_SyncReply_m.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/messages/HF_SyncRequest_m.o: messages/HF_SyncRequest_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	messages/HF_SyncRequest_m.h
$O/messages/KN_Packet_m.o: messages/KN_Packet_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	messages/KN_Packet_m.h \
	utility/KandooStructs.h
$O/messages/LLDP_m.o: messages/LLDP_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	messages/LLDP_m.h
$O/messages/OFP_Features_Reply_m.o: messages/OFP_Features_Reply_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Features_Reply_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Features_Request_m.o: messages/OFP_Features_Request_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Features_Request_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Flow_Mod_m.o: messages/OFP_Flow_Mod_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Hello_m.o: messages/OFP_Hello_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Hello_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Initialize_Handshake_m.o: messages/OFP_Initialize_Handshake_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Initialize_Handshake_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Packet_In_m.o: messages/OFP_Packet_In_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Packet_In_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Packet_Out_m.o: messages/OFP_Packet_Out_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/OFP_Port_Mod_m.o: messages/OFP_Port_Mod_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Port_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/messages/Open_Flow_Message_m.o: messages/Open_Flow_Message_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h
$O/openflow/controller/OF_Controller.o: openflow/controller/OF_Controller.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/base/ByteArray.h \
	$(INET_PROJ)/src/base/ByteArray_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/tcp/TCP.h \
	$(INET_PROJ)/src/transport/tcp/TCPConnection.h \
	$(INET_PROJ)/src/transport/tcp_common/TCPSegment.h \
	$(INET_PROJ)/src/transport/tcp_common/TCPSegment_m.h \
	controllerApps/AbstractControllerApp.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Features_Request_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Initialize_Handshake_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/controller/OF_Controller.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/openflow/controller/Switch_Info.o: openflow/controller/Switch_Info.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	openflow/controller/Switch_Info.h \
	openflow/protocol/openflow.h
$O/openflow/switch/Buffer.o: openflow/switch/Buffer.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	openflow/protocol/openflow.h \
	openflow/switch/Buffer.h
$O/openflow/switch/Flow_Table.o: openflow/switch/Flow_Table.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h \
	openflow/switch/Flow_Table.h \
	openflow/switch/Flow_Table_Entry.h
$O/openflow/switch/Flow_Table_Entry.o: openflow/switch/Flow_Table_Entry.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h \
	openflow/switch/Flow_Table_Entry.h
$O/openflow/switch/OF_Switch.o: openflow/switch/OF_Switch.cc \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/common/MACBase.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMAC.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACBase.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Hello_m.h \
	messages/OFP_Initialize_Handshake_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h \
	openflow/switch/Buffer.h \
	openflow/switch/Flow_Table.h \
	openflow/switch/Flow_Table_Entry.h \
	openflow/switch/OF_Switch.h
$O/utility/ARP_Wrapper.o: utility/ARP_Wrapper.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	utility/ARP_Wrapper.h
$O/utility/ControllerInvolvmentFilter.o: utility/ControllerInvolvmentFilter.cc \
	utility/ControllerInvolvementFilter.h
$O/utility/LLDP_Wrapper.o: utility/LLDP_Wrapper.cc \
	utility/LLDP_Wrapper.h
$O/utility/OpenFlowGraphAnalyzer.o: utility/OpenFlowGraphAnalyzer.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h \
	openflow/switch/Buffer.h \
	openflow/switch/Flow_Table.h \
	openflow/switch/Flow_Table_Entry.h \
	openflow/switch/OF_Switch.h \
	utility/OpenFlowGraphAnalyzer.h
$O/utility/StaticSpanningTree.o: utility/StaticSpanningTree.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow/protocol/openflow.h \
	openflow/switch/Buffer.h \
	openflow/switch/Flow_Table.h \
	openflow/switch/Flow_Table_Entry.h \
	openflow/switch/OF_Switch.h \
	utility/StaticSpanningTree.h

