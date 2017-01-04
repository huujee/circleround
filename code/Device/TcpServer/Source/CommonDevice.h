#pragma once

// Variable
const int RCVBUFSIZE = 32;
const int TCPPORT = 8370;

// Viewer Protocol Type
const int MODE_DEFAULT = 0;
const int MODE_CONNECT = 1;
const int MODE_DISCONN = 2;
const int MODE_RESET = 3;

// Viewer Packet data
typedef struct TCPPacket
{
	int nMode;
	int nPort;
	char strIp[17];
}TCPPacket;
