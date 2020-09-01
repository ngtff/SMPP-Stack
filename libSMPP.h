#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <poll.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h> 
#include <resolv.h>

#ifndef LIB_NGTFF_SMPP_H
#define LIB_NGTFF_SMPP_H

#include "jansson.h"

#define NFTFF_SMPP_BIND_TRANSMITTER							0x00000002
#define NFTFF_SMPP_BIND_TRANSMITTER_RESP       				0x80000002
#define NFTFF_SMPP_BIND_RECEIVER               				0x00000001
#define NFTFF_SMPP_BIND_RECEIVER_RESP          				0x80000001
#define NFTFF_SMPP_BIND_TRANSCEIVER            				0x00000009
#define NFTFF_SMPP_BIND_TRANSCEIVER_RESP       				0x80000009
#define NFTFF_SMPP_OUTBIND                     				0x0000000B
#define NFTFF_SMPP_UNBIND                      				0x00000006
#define NFTFF_SMPP_UNBIND_RESP                 				0x80000006
#define NFTFF_SMPP_GENERIC_NACK                				0x80000000
#define NFTFF_SMPP_SUBMIT_SM                   				0x00000004
#define NFTFF_SMPP_SUBMIT_SM_RESP              				0x80000004
#define NFTFF_SMPP_SUBMIT_MULTI                				0x00000021
#define NFTFF_SMPP_SUBMIT_MULTI_RESP           				0x80000021
#define NFTFF_SMPP_DELIVER_SM                  				0x00000005
#define NFTFF_SMPP_DELIVER_SM_RESP             				0x80000005
#define NFTFF_SMPP_DATA_SM                     				0x00000103
#define NFTFF_SMPP_DATA_SM_RESP                				0x80000103
#define NFTFF_SMPP_QUERY_SM                    				0x00000003
#define NFTFF_SMPP_QUERY_SM_RESP               				0x80000003
#define NFTFF_SMPP_CANCEL_SM                   				0x00000008
#define NFTFF_SMPP_CANCEL_SM_RESP              				0x80000008
#define NFTFF_SMPP_REPLACE_SM                  				0x00000007
#define NFTFF_SMPP_REPLACE_SM_RESP             				0x80000007
#define NFTFF_SMPP_ENQUIRE_LINK                				0x00000015
#define NFTFF_SMPP_ENQUIRE_LINK_RESP           				0x80000015
#define NFTFF_SMPP_ALERT_NOTIFICATION          				0x00000102
	
typedef struct ngtff_smpp_session
{
	struct ngtff_smpp_session * Next;
	
	uint8_t * siSocket;
	char system_id[17];
	uint8_t	interface_version;
	
	
} NGTFF__smpp_session_t;

typedef struct ngtff_smpp_sock_msg
{
	uint8_t * siSocket;
	u_char * data;
	int len;
	int pos;
	int decode_sts;
} NGTFF__socket_msg_t;

typedef struct ngtff_smpp_raw_pdu
{
	u_char buffer[5000];
	int pos;
	int len;
} NGTFF__raw_pdu_t;

typedef struct ngtff__smpp_command
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes	
} NGTFF_smpp_command_t;

/*
	smpp pdu messages are currently same for bind_transmitter(2), bind_receiver(1), bind_transceiver(9)
*/
typedef struct ngtff__bind
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes

	char system_id[17];			//max 16 + 1 for NULL  C-Octet-String 
	char password[10];			//max  9 + 1 for NULL  C-Octet-String
	char system_type[14];		//max 13 + 1 for NULL  C-Octet-String 

	uint8_t	interface_version;	//1 byte
	uint8_t addr_ton;			//1 byte 	Type of Number of the ESME address.	If not known set to NULL. 
	uint8_t addr_npi;			//Numbering Plan Indicator for ESME address.	If not known set to NULL
 	char address_range[42];		//max 41 + 1 for NULL  C-Octet-String 
	
} NGTFF__bind_t;

/*
	smpp pdu messages are currently same for bind_transmitter_resp(0x80000002), bind_receiver_resp(0x80000001), bind_transceive_resp(0x80000009)
*/
typedef struct ngtff__bind_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes

	char system_id[17];			//max 16 + 1 for NULL  C-Octet-String 

	//Optional TLVs:
		//sc_interface_version                   TLV                   SMPP                   version supported by MC
} NGTFF__bind_resp_t;


typedef struct ngtff__outbind
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x0000000B 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
	
	char system_id[17];			//max 16 + 1 for NULL  C-Octet-String  MC identifier., Identifies the MC to the ESME. 
	char password[10];			//max  9 + 1 for NULL  C-Octet-String
								/*
									The password may be used by the ESME for security reasons to authenticate the MC originating the outbind
								*/
} NGTFF__outbind_t;


typedef struct ngtff__unbind
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x00000006 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
} NGTFF__unbind_t;


typedef struct ngtff__unbind_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000006 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
} NGTFF__unbind_resp_t;


typedef struct ngtff__enquire_link
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x00000015 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
} NGTFF__enquire_link_t;


typedef struct ngtff__enquire_link_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000015 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
} NGTFF__enquire_link_resp_t;

typedef struct ngtff__alert_notification
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x00000102 
	uint32_t command_status;	//4 bytes
	uint32_t sequence_number;	//4 bytes
	
	uint8_t source_addr_ton;	//1 byte	Type of Number for alert SME. 
	uint8_t source_addr_npi;	//1 byte	Numbering Plan Indicator for alert SME.
	char source_addr[66];		//max 65 	Address of alert SME. 
	
	uint8_t esme_addr_ton;
	uint8_t esme_addr_npi;
	char esme_addr[66];			//max 65 	Address of alert SME. 
	
	//Optional TLVs: 
	//ms_availability_status   //status of the mobile station     	
} NGTFF__alert_notification_t;

typedef struct ngtff__generic_nack
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
} NGTFF__generic_nack_t;


typedef struct ngtff__submit_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes

	char service_type[7];		//max 6
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char 	source_addr[22];	//max 21
	
	uint8_t dest_addr_ton;
	uint8_t dest_addr_npi;
	char destination_addr[22];	//max 21
	
	uint8_t esm_class;
	uint8_t protocol_id;
	uint8_t priority_flag;
	
	char schedule_delivery_time[18];	//max 17, 1 or 17 	The short message is to be scheduled by the MC for delivery.
															//Set to NULL for immediate message delivery 

	char validity_period[18];			//max 17, 1 or 17 	The validity period of this message..
															//Set to NULL to request the MC default validity period 

	uint8_t registered_delivery;
	uint8_t replace_if_present_flag;
	uint8_t data_coding;
	uint8_t sm_default_msg_id;
	
	uint8_t sm_length;
	char short_message[255];			//0-255, max 255	Up to 255 octets of short message user data. 

	//Message Submission TLVs 
} NGTFF__submit_sm_t;


typedef struct NGTFF__submit_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];		//max 66	
	//Message Submission Response TLVs
	
} NGTFF__submit_sm_resp_t;

typedef struct NGTFF__data_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes

	char service_type[7];		//max 6
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char 	source_addr[22];	//max 21
	
	uint8_t dest_addr_ton;
	uint8_t dest_addr_npi;
	char destination_addr[22];	//max 21
	
	uint8_t esm_class;
	uint8_t data_coding;
	
	uint8_t sm_length;
	char short_message[255];			//0-255, max 255	Up to 255 octets of short message user data. 

	//Message Submission TLVs 	
} NGTFF__data_sm_t;


typedef struct NGTFF__data_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];		//max 66	
	//Message Submission Response TLVs
	
} NGTFF__data_sm_resp_t;

typedef struct NGTFF__submit_multi
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes

	char service_type[7];		//max 6
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char 	source_addr[22];	//max 21

	uint8_t number_of_dests;

	//dest_address

	uint8_t esm_class;
	uint8_t protocol_id;
	uint8_t priority_flag;
	char schedule_delivery_time[18];		//max 17
	char validity_period[18];				//max 17
		
	uint8_t registered_delivery;
	uint8_t replace_if_present_flag;
	uint8_t data_coding;
	uint8_t sm_default_msg_id;
	uint8_t sm_length;
	char short_message[256];
	
	//Message Submission TLVs 
	
} NGTFF__submit_multi_t;

typedef struct NGTFF__submit_multi_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[65];				//max 17
	uint8_t no_unsuccess;
	char unsuccess_sme[28];				//max 28
	
	//Message Submission Response TLVs
} NGTFF__submit_multi_resp_t;

typedef struct NGTFF__deliver_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes

	char service_type[7];		//max 6
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
	
	uint8_t dest_addr_ton;
	uint8_t dest_addr_npi;
	char destination_addr[22];
	
	uint8_t esm_class;
	uint8_t protocol_id;
	uint8_t priority_flag;
	
	char schedule_delivery_time[18];
	char validity_period[18];
	
	uint8_t registered_delivery;
	uint8_t replace_if_present_flag;
	uint8_t data_coding;
	uint8_t sm_default_msg_id;
	uint8_t sm_length;
	char short_message[256];
	
	//Message Delivery Request TLVs 
	
} NGTFF__deliver_sm_t;

typedef struct NGTFF__deliver_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
} NGTFF__deliver_sm_resp_t;

typedef struct NGTFF__broadcast_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes

	char service_type[7];
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
	
	char message_id[66];
	uint8_t priority_flag;
	char schedule_delivery_time[18];
	char validity_period[18];
	
	uint8_t replace_if_present_flag;
	uint8_t data_coding;
	uint8_t sm_default_msg_id;
	
	//tlv
	//broadcast_area_identifier
	//broadcast_content_type
	//broadcast_rep_num
	//broadcast_frequency_interval
	
	//Broadcast Request Optional TLVs
		
} NGTFF__broadcast_sm_t;

typedef struct NGTFF__broadcast_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	
	//Broadcast Request Optional TLVs
	
} NGTFF__broadcast_sm_resp_t;

typedef struct NGTFF__cancel_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char service_type[7];
	char message_id[66];
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
	
	uint8_t dest_addr_ton;
	uint8_t dest_addr_npi;
	char destination_addr[22];
	
	
} NGTFF__cancel_sm_t;

typedef struct NGTFF__cancel_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
} NGTFF__cancel_sm_resp_t;

typedef struct NGTFF__query_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
} NGTFF__query_sm_t;

typedef struct NGTFF__query_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	char final_date[18];
	uint8_t message_state;
	uint8_t error_code;
} NGTFF__query_sm_resp_t;

typedef struct NGTFF__replace_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
	char schedule_delivery_time[18];
	char validity_period[18];
	uint8_t registered_delivery;
	uint8_t sm_default_msg_id;
	uint8_t sm_length;
	char short_message[256];
	
} NGTFF__replace_sm_t;

typedef struct NGTFF__replace_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
} NGTFF__replace_sm_resp_t;

typedef struct NGTFF__query_broadcast_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	char source_addr[22];
} NGTFF__query_broadcast_sm_t;


typedef struct NGTFF__query_broadcast_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char message_id[66];
	
	//TLV
	//message_state
	//broadcast_area_identifier
	//broadcast_area_success
	//Query Broadcast Response TLVs
	
	
} NGTFF__query_broadcast_sm_resp_t;

typedef struct NGTFF__cancel_broadcast_sm
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
	
	char service_type[7];
	char message_id[66];
	
	uint8_t source_addr_ton;
	uint8_t source_addr_npi;
	
	char source_addr[22];
	
} NGTFF__cancel_broadcast_sm_t;

typedef struct NGTFF__cancel_broadcast_sm_resp
{
	uint32_t command_length;	//4 bytes		
	uint32_t command_id;		//4 bytes	0x80000000  
	uint32_t command_status;	//4 bytes	Error code corresponding to reason for sending the generic_nack.
	uint32_t sequence_number;	//4 bytes
} NGTFF__cancel_broadcast_sm_resp_t;

	
void ngtff__smpp_set_command_length( NGTFF__raw_pdu_t * rpdu);

void ngtff__smpp_initalize( char * jsonconfigfile);
void ngtff__smpp_start();

json_t * ngtff__smpp_get_config_object();

void ngtff__smpp_add_esme( json_t * esme);


#endif








