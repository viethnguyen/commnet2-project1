#include "common.h"
#include "newport.h"
#include "message.h"
#include <iostream>
using namespace std;

/**
 * @param: argv[1] destination host address
 * 			argv[2] destination port address
 * 			argv[3] listening port address
 * 			argv[4] filename
 */
int main(int argc, const char * argv[])
{
 try {

  const char* hname = "localhost";       
  Address * my_tx_addr = new Address(hname, 3000);

  //configure sending port
  Address * dst_addr =  new Address(argv[1], (short)(atoi(argv[2])));
  mySendingPort *my_port = new mySendingPort();
  my_port->setAddress(my_tx_addr);
  my_port->setRemoteAddress(dst_addr);
  my_port->init();

  //configure receiving port to listen to ACK frames
  Address * my_rx_addr = new Address(hname, (short)(atoi(argv[3])));
  LossyReceivingPort *my_rx_port = new LossyReceivingPort(0.2);
  my_rx_port->setAddress(my_rx_addr);
  my_rx_port->init();

  //create a single packet
  Packet * my_packet;
  my_packet = new Packet();
  my_packet->setPayloadSize(100);
  PacketHdr *hdr = my_packet->accessHeader();
  hdr->setOctet('D',0);
  hdr->setOctet('A',1);
  hdr->setOctet('T',2);
  hdr->setIntegerInfo(1,3);

  //init a file transfer session
  Message *m;
  Packet *init_packet = m->make_init_packet(argv[4]);
 
  //sending it
  my_port->sendPacket(init_packet);
  my_port->lastPkt_ = init_packet;
  cout << "Init packet is sent!" <<endl;
  my_port->setACKflag(false);
  //schedule retransmit
  my_port->timer_.startTimer(2.5);  

  cout << "begin waiting for ACK..." <<endl;
  Packet *pAck;
  while (!my_port->isACKed()){
        pAck = my_rx_port->receivePacket();
        if (pAck!= NULL)
	{
	     my_port->setACKflag(true);
	     my_port->timer_.stopTimer();
             cout << "The last sent packet has been acknowledged." <<endl;
    
	}
  };  
    
 } catch (const char *reason ) {
    cerr << "Exception:" << reason << endl;
    exit(-1);
  }  

 return 0;
}
