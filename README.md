# NGTFF SMPP Stack

NGTFF smpp stack, provides application programming interface to send and receive sm messages from ESME clients.

NGTFF smpp stack, handles large no of esme sessions (client connections) with huge traffic load.

NGTFF smpp stack, internal implementation of SMPP Routing Entity.  


### High Lights

* SMPP 5.0 version.
* Handles Many ESME (TCP/IP Client) Connections.
* Auto Scale Up.
* Asynchronous processing. 
* SMPP Routing Entity.
* Circular Buffers.
* Handles SMPP Binding Operations.
* ESME Session Management.
* Handles 5000 Messages Per Second.

### SMPP 5.0 version.

NGTFF smpp stack, implements latest version of SMPP.


### Handles Many ESME (TCP/IP Client) Connections

The Test Application - ESMEClient, Establishes 500 bind request with SMPP (only for connection capability demonstration), and each connection sends 10 requests per second.  

### Auto Scale Up.

NGTFF smpp stack, increases its processing threads and memory, to handle and support growing traffic. 


### SMPP Routing Entity

When deployed mutiple instances of SMPP, **SMPP Routing Entity** Maintains EMSE Session context across multiple instances of SMPP.

Lets Message Center deliver sm message to any SMPP instance, the sm message will routed to target ESME.




<image src="smpp_stack.png" />

NGTFF SMPP Stack has been developed in Linux C.

The NGTFF smpp stack manages sessions and session operations (bind/enquire-link) internally., an callback event will raised to application for authenticating ESME.

Circular buffer will be used for allocating and freeing up messages, which will boost performance of stack and application.

 <image src="smpp_routing_entity.png" />


please contact ngtff@hotmail.com


 


















