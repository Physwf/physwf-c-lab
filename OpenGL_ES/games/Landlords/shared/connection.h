#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <windows.h>

typedef struct connection_t {
	SOCKET socket;
	char readBuffer[READ_BUFFER_SIZE];
	char writeBuffer[WRITE_BUFFER_SIZE];
	int readBufAvaliable;
	int writeBufAvaliable;
	int state;
} Connection,*PConnection;

init();
connect();
//rpc_select();
call();
add_msg_callback();

#endif