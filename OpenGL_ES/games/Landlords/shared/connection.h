#ifndef _CONNECTION_H
#define _CONNECTION_H

#define STATE_FREE 0
#define STATE_HOLD 1
#define STATE_CLOSED 2

#define READ_BUFFER_SIZE 512
#define WRITE_BUFFER_SIZE 512

#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct connection_t {
	SOCKET socket;
	char readBuffer[READ_BUFFER_SIZE];
	char writeBuffer[WRITE_BUFFER_SIZE];
	int readBufAvaliable;
	int writeBufAvaliable;
	int state;
} Connection,*PConnection;

#endif