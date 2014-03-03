
# Specify the compiler
CC = g++

#CCOPTS = -ansi -pedantic -Wall -g
CCOPTS = -g -Wall
LIBS = -pthread

# Make the source
all:	sender receiver

common.o : common.h common.cpp 
	$(CC) $(CCOPTS) -c common.cpp
 
sender:  sender.cpp common.o  
	$(CC) $(CCOPTS) $(LIBS) common.o sender.cpp -o sender

receiver: receiver.cpp common.o
	$(CC) $(CCOPTS) $(LIBS) common.o receiver.cpp -o receiver

clean :
	rm -f common.o sender receiver
