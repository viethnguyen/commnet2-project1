/*
 * message.cpp
 *
 *  Created on: Mar 2, 2014
 *      Author: vietnguyen
 *
 *      Define message types used
 */

#include "common.h"
#include "newport.h"
#include "message.h"
#include <iostream>

#define INIT_SIZE 500
#define DATA_SIZE 500
#define SENDER_ID 15
#define RECEIVER_ID 20

/**
 * Create a new init message, with the name of the file being transfered
 */
Packet *Message::make_init_packet(const char *filename){
	  Packet * init_packet;
	  init_packet = new Packet();
	  init_packet->setPayloadSize(INIT_SIZE);

	  //Header
	  PacketHdr *hdr = init_packet->accessHeader();
	  hdr->setIntegerInfo(SENDER_ID, ID_POS);
	  hdr->setOctet('I',TYPE_POS);
	  hdr->setOctet('N',TYPE_POS + 1);
	  hdr->setOctet('I',TYPE_POS + 2);
	  hdr->setOctet('T',TYPE_POS + 3);
	  hdr->setIntegerInfo(0,SEQNUM_POS); //sequence number

	  //Payload
	  init_packet->fillPayload(INIT_SIZE, filename);
	  return init_packet;
}

/**
 * Create an ACK message
 */
Packet *Message::make_ack_packet(int seqNum){
	Packet *ack_packet;
	ack_packet = new Packet();
	ack_packet->setPayloadSize(0);

	//Header
	PacketHdr *hdr = ack_packet->accessHeader();
	hdr->setIntegerInfo(RECEIVER_ID, ID_POS);
	hdr->setOctet('A', TYPE_POS);
	hdr->setOctet('C', TYPE_POS + 1);
	hdr->setOctet('K', TYPE_POS + 2);
	hdr->setIntegerInfo(seqNum, SEQNUM_POS); // sequence number being ACKED

	return ack_packet;
}
