                         Client Server Programs
                         ======================
                        
These are simple programs to transmit data from the client to the
server.  You need to appropriately modify the message signal to transmit
the data that you want.

There are two modes of transmission - TCP and UDP.  We use UDP which
is an UNRELIABLE connectionless data transfer protocol.  The communication
channel is identified by defining the server IP address, server Port Number,
client IP address and client Port Number.

Reference: Richard Stevens, Unix Network Programming - PHI - Vol 1, 1997

1. First untar the tarball
2. Change the paths in the Makefile
3. To compile: make -f Makefile

To run server:

../bin/Server ServerIPAddress, ServerPortNumber

To run client:

../bin/Client ServerIPAddress, ServerPortNumber, ClientIPAddress, ClientPortNumber

First start the server

Next start the client

This is only a sample program.  You have to appropriately  fill the 
sendMsg array with PCM data.  Remember that a character is represented
by 8-bits.
