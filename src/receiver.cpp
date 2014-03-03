#include "common.h"
#include "newport.h"
#include "message.h"
#include <iostream>
using namespace std;

//state of the receiver
const int WAITING_STATE = 0;
const int RECEIVING_STATE = 1;

/**
 * @param argv[1] receiving port number
 * 			argv[2] destination address
 * 			argv[3]
 */
int main(int argc, const char * argv[])
{

	int state = WAITING_STATE;

try {
  const char* hname = "localhost";  

  //configure receiving port     
  Address * my_addr = new Address(hname, (short)(atoi(argv[1])));
  
  LossyReceivingPort *my_port = new LossyReceivingPort(0.2);
  my_port->setAddress(my_addr);
  my_port->init();

  //configure a sending port to send ACK
  Address * my_tx_addr = new Address(hname, 3005);
  Address * dst_addr =  new Address(argv[2], (short)(atoi(argv[3])));
  mySendingPort *my_tx_port = new mySendingPort();
  my_tx_port->setAddress(my_tx_addr);
  my_tx_port->setRemoteAddress(dst_addr);
  my_tx_port->init();
  
  Message *m;

  
  cout << "begin receiving..." <<endl;
  Packet *p;
  while (1)
  {
    p = my_port->receivePacket(); 
    if (p !=NULL)
    {  
    	switch(state){
    	case WAITING_STATE:
    		//TODO: if there is an init packet coming, ACK and change to RECEVING_STATE
    		int seqNum = p->accessHeader()->getIntegerInfo(m->SEQNUM_POS);
    		Packet * ack_packet = m->make_ack_packet(seqNum);
    		break;
    	case RECEIVING_STATE:
    		//TODO: keeps receiving data packets and store into buffer. If end of file, close buffer and change to WAITING_STATE

    		break;
    	}
       int i = p->accessHeader()->getIntegerInfo(3);
       cout << "receiving a packet of seq num " << i << "...sending ACK" << endl; 
       hdr->setIntegerInfo(i,3);
       my_tx_port->sendPacket(my_ack_packet);       
    }
  } 
} catch (const char *reason ) {
    cerr << "Exception:" << reason << endl;
    exit(-1);
}  

return 0;
}
