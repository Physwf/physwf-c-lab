#include <winsock2.h>
#include "../shared/common.h"

#pragma comment(lib,"ws2_32.lib")

#define MAX_CONN 3

#define STATE_FREE 0
#define STATE_HOLD 1
#define STATE_CLOSED 2

#define READ_BUFFER_SIZE 512
#define WRITE_BUFFER_SIZE 512

typedef struct connection_t {
	SOCKET socket;
	char readBuffer[READ_BUFFER_SIZE];
	char writeBuffer[WRITE_BUFFER_SIZE];
	int readBufAvaliable;
	int writeBufAvaliable;
	int state;
} Connection,*PConnection;

void net_init();
void net_run();