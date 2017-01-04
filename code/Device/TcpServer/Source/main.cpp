/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include "CommonDevice.h"
#include <iostream>           // For cout, cerr
#include <cstdlib>            // For atoi()
#include <pthread.h>          // For POSIX threads
#include <string.h>
#include <map>

/*
// for bluetooth
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


int s, client;
void ctrl_c_handler(int signal);
void close_sockets();
void *readMsg(void* temp);
void *sendMsg(void* temp);
*/


using namespace std;

std::map<TCPSocket*, TCPPacket*> clientSocket;

void* ThreadAccepted(void *arg);               // Main program of a thread

int main()
{
	cout << "[main] Main Started" << endl;
//  if (argc != 2) {                 // Test for correct number of arguments
//    cerr << "Usage: " << argv[0] << " <Server Port> " << endl;
//    exit(1);
//  }
/*
	// bluetooth
	(void) signal(SIGINT, ctrl_c_handler);
	pthread_t readT, writeT;
	char *message1 = "Read thread\n";
	char *message2 = "Write thread\n";
	int iret1, iret2;

	struct sockaddr_rc loc_addr={0}, client_addr={0};
	char buf[18] = {0};

	unsigned int opt = sizeof(client_addr);

	// allocate socket
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	// bind socket to port 1 of the first available
	loc_addr.rc_family = AF_BLUETOOTH;
	str2ba("00:1F:81:00:00:01", &loc_addr.rc_bdaddr); // hci0; server device address is given
	loc_addr.rc_channel = 1; // port (maximum should be 30 for RFCOMM)

	bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
	cout << "Binding success" << endl;

	//put socket into listen mode
	listen(s,1);
	cout << "socket in listen mode" << endl;
	//accept one connection

	client = accept(s, (struct sockaddr*)&client_addr, &opt);
	ba2str(&client_addr.rc_bdaddr, buf);
	fprintf(stdout, "Connection accepted from %s\n", buf);

	// Create independent threads each of which will execute function

	iret1 = pthread_create(&readT, NULL, readMsg, (void*) message1);
	iret2 = pthread_create(&writeT, NULL, sendMsg, (void*) message2);

	pthread_join(readT, NULL);
	pthread_join(writeT, NULL);

	close_sockets();
*/
  try {
    TCPServerSocket servSock(TCPPORT);   // Socket descriptor for server

    while (true) {      // Run forever
      cout << "[main] Waiting a client" << endl;

      // Create separate memory for client argument
      TCPSocket *clntSock = servSock.accept();

      // Create client thread
      pthread_t threadID;              // Thread ID from pthread_create()
      if (pthread_create(&threadID, NULL, ThreadAccepted, (void *) clntSock) != 0)
      {
        cerr << "[main] Unable to create TCP thread" << endl;
      }
      else
      {
        cout << "[main] Created TCP Thread" << endl;

        TCPPacket* clntPacket = new TCPPacket();

        clientSocket.insert(std::map<TCPSocket*, TCPPacket*>::value_type(clntSock, clntPacket));

        // Order to connect
        if (clientSocket.size() > 1)
        {
            clntPacket->nMode = MODE_CONNECT;
            clntPacket->nPort = TCPPORT;

            string strIp = clientSocket.begin()->first->getForeignAddress();
            if (strIp != "")
            {
            	strcpy(clntPacket->strIp,strIp.c_str());
            }

            cout << "Connect IP : " << strIp.c_str() << " " << strIp.size() << endl;

            //clntSock->send(strIp.c_str(), strIp.size());
        	clntSock->send(clntPacket, sizeof(TCPPacket));
        }
      }
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
  // NOT REACHED

  return 0;
}

// Accepted Client Handling
void *ThreadAccepted(void *clntSock) {
  // Guarantees that thread resources are deallocated upon return
  pthread_detach(pthread_self());

  TCPSocket *sock = (TCPSocket *) clntSock;

  cout << "[ThreadAccepted] Handling client ";
  try {
    cout << sock->getForeignAddress() << ":";
  } catch (SocketException &e) {
    cerr << "[ThreadAccepted] Unable to get foreign address" << endl;
  }
  try {
    cout << sock->getForeignPort() << endl;
  } catch (SocketException &e) {
    cerr << "[ThreadAccepted] Unable to get foreign port" << endl;
  }
  cout << "[ThreadAccepted] with thread " << pthread_self() << endl;


  try
  {
	  // Send received string and receive again until the end of transmission
	  char echoBuffer[RCVBUFSIZE];
	  int recvMsgSize;
	  while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
															 // end of transmission
		// Echo message back to client
		sock->send(echoBuffer, recvMsgSize);
	  }
  }
  catch(SocketException &e)
  {
	    cerr << "[ThreadAccepted] recv exception : " << e.what() << endl;
  }


  //////////// Must modify!! Don't do this in a separated thread ///////////////////////////////////////
  std::map<TCPSocket*, TCPPacket*>::iterator iter = clientSocket.begin();

  for(;iter != clientSocket.end();iter++)
  {
	  if (iter->first == clntSock)
	  {
		  clientSocket.erase(iter);
	  }
  }
  ////////////////////////////////////////////////////////////////////////////////////////

  delete (TCPSocket *) clntSock;

  cout << "[ThreadAccepted] Terminating " << endl;
  return NULL;
}

/*

void *sendMsg(void* temp)
{
	char msg[25];
	int status;

	do
	{
		memset(msg, 0, sizeof(msg));
		fgets(msg, 24, stdin);
		if (strncmp("EXIT", msg,4) == 0 || strncmp("exit", msg, 4) == 0)
			break;
		status = send(client, msg, strlen(msg), 0);
		fprintf(stdout, "Status = %d\n", status);
	}while(status > 0);
}

void *readMsg(void* temp)
{
	int bytes_read;
	char buf[1024] = {0};
	do
	{
		memset(buf, 0, sizeof(buf));
		// read data from the client
		bytes_read = recv(client, buf, sizeof(buf), 0);
		fprintf(stdout, "Bytes read = %d\n", bytes_read);
		if(bytes_read <= 0)
			break;
		fprintf(stdout, "<<>> %s", buf);
	}while(1);
}

void close_sockets()
{
	// close connection
	close(client);
	close(s);
	cout << "sockets closed" << endl;
}

void ctrl_c_handler(int signal)
{
	cout << "Catched signal : " << signal << "... !!" << endl;
	close_sockets();
	exit(0);
	//(void) signal(SIGINT, SIG_DFL)
}

*/
