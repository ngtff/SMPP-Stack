# NGTFF SMPP Stack

NGTFF smpp stack, handles large no of esme sessions with huge traffic load, and has internal implementation of SMPP Routing Entity.

### High Lights

* SMPP 5.0 version.
* Handles Many ESME (TCP/IP) Connections.
* Auto Scale Up.
* Asynchronous processing. 
* SMPP Routing Entity.
* Circular Buffers.
* Handles SMPP Binding Operations.
* ESME Session Management.
* Handles 3000 Messages Per Second.



### P2A Messages

MC devlivers deliver-sm to any of SMPP Nodes, **SMPP Routing Entity** inside NGTFF smpp stack routes to Peer SMPP and delivers message to Target EMSE. 

<image src="smpp_stack.png" />

NGTFF SMPP Stack has been developed in Linux C.

The NGTFF smpp stack manages sessions and session operations (bind/enquire-link) internally., an callback event will raised to application for authenticating ESME.

Circular buffer will be used for allocating and freeing up messages, which will boost performance of stack and application.

 <image src="smpp_routing_entity.png" />


please contact ngtff@hotmail.com


 


















