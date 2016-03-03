/* Jacob Dickinson
 *jdickins
 *CIS 415 Project 2
 * This is my work
 */

#include "networkdriver.h"
#include "networkdevice.h"
#include "freepacketdescriptorstore__full.h"
#include "packetdescriptorcreator.h"
#include "packetdescriptor.h"
#include "BoundedBuffer.h"
#include "pid.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*universal ints*/
#define NETBUFFERSIZE 22
#define APPBUFFERSIZE 2

/*networl to use in functions*/
NetworkDevice *net;

/*buffers for send and recieve*/
BoundedBuffer **fromNet;
BoundedBuffer *toNet;

/*fpds to hold packets*/
FreePacketDescriptorStore *fpds;

/*thread functions for main*/
void *getthrd();
void *sendthrd();

/*take pd to network*/
void *getthrd(){
	int i;
	PacketDescriptor *pd;

	while(1){
		pd = blockingReadBB(toNet);
		for(i = 0; i < 8; i++){
			if((send_packet(net, pd))== 1){
				break;
			}
		}
	}

	blocking_put_pd(fpds, pd);
	return NULL;
}

/*get pd from net*/
void *sendthrd(){
	PacketDescriptor *pd;
	blocking_get_pd(fpds, &pd);
	init_packet_descriptor(pd);
	register_receiving_packetdescriptor(net, pd);
	await_incoming_packet(net);

	if(nonblocking_get_pd(fpds, &pd) == 0){
		printf("Driver: paket dropped\n");
	}
	return NULL;
}

/*main makes fpds, an array of buffers to hold pd's for apps, and threads to run for the network*/
void init_network_driver(NetworkDevice *nd, void *mem_start, unsigned long mem_length, FreePacketDescriptorStore **fpds_ptr){
	pthread_t sendthrd_id;
	pthread_t getthrd_id;
	
	int i;

	net = nd;
	
	/*free packet descriptor store*/
	*fpds_ptr = create_fpds();
	create_free_packet_descriptors(*fpds_ptr, mem_start, mem_length);
	fpds = *fpds_ptr;

	/*bounded buffers*/
	fromNet = malloc((sizeof(BoundedBuffer *)*(MAX_PID+1)));
	for(i = 0; i < (MAX_PID+1); i++){
		fromNet[i] = createBB(APPBUFFERSIZE);
	} 
	toNet = createBB(NETBUFFERSIZE);

	pthread_create(&sendthrd_id, NULL, &sendthrd, NULL);
	pthread_create(&getthrd_id, NULL, &getthrd, NULL);


	
}

void blocking_send_packet(PacketDescriptor *pd){
	blockingWriteBB(toNet, pd);
}

int  nonblocking_send_packet(PacketDescriptor *pd){
	return nonblockingWriteBB(toNet, (void *)pd);
}

void blocking_get_packet(PacketDescriptor **pd, PID pid){
	*pd = blockingReadBB(fromNet[pid]);
}

int nonblocking_get_packet(PacketDescriptor **pd, PID pid){
	return nonblockingReadBB(fromNet[pid], (void **)pd);
}


