# SMPP_CLUSTER
smpp cluster, handles hundreds of esme connections and huge traffic load 

<image src="smppcluster.png" />

The SMPP Cluster is combination of SMPP Cluster Application + SMPP Agents

SMSC Server connected to one or multiple SMPP Cluster Application, either Active or standby from SMSC point of view

Multiple SMPP Agents can be deployed and connected to SMPP Cluster Application, all SMPP Agents are connected to SMPP Cluster Application.

The SMPP Cluster Applications will Sync ESME Client Information to all SMPP Agents.

The ESME Client will connect to any of the SMPP Agents, either in Active or stanby mode.

The SMPP Agent will does connection management with ESME Clients.

The A2P Message will be delivered to SMSC, througth SMPPAgent -> SMPP Cluster Application -> SMSC

The P2A Messages will be delivered to EMSE through SMSC -> SMPP Cluster Application -> SMPPAgent

Supported ESME Connections.

Its dependens on messages per second by ESME Client, 

if Each ESME will sends 10 messages per second, then it can support 1000 Connections Per SMPP Agent,  
if Each ESME will sends 100 messages per second, then it can support 100 Connections Per SMPP Agent,  

Multiple SMPP Agents can be deployed according to the requirements.

Mutiple SMPP Cluster Applications Can be deployed connected to multiple instances of SMPP Agents.















