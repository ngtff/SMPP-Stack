# NGTFF SMPP Stack

NGTFF smpp stack, handles large no of esme sessions with huge traffic load, and has internal implementation of SMPP Routing Entity.

<u>A2P Messages</u>




<image src="smpp_stack.png" />

NGTFF SMPP Stack has been developed in Linux C.

The NGTFF smpp stack manages sessions and session operations (bind/enquire-link) internally., an callback event will raised to application for authenticating ESME.

Circular buffer will be used for allocating and freeing up messages, which will boost performance of stack and application.

 <image src="smpp_routing_entity.png" />





 


















