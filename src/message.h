/*
 * message.h
 *
 *  Created on: Mar 2, 2014
 *      Author: vietnguyen
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_



class Message {
private:

public:
	//define message format - byte position in the header of each field
	static const int ID_POS = 0;
	static const int TYPE_POS = 4;
	static const int SEQNUM_POS = 8;

	//'make' functions
	Packet *make_init_packet(const char *filename);
	Packet *make_ack_packet(int seqNum);
};

#endif /* MESSAGE_H_ */
