#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define ETCPSOCK_BIND -1;
#define ETCPSOCK_LISTEN -2;
#define ETCPSOCK_CONNECT -3;
#define ETCPSOCK_LOOP -4;

struct {
	int sockfd;
	struct sockaddr_in address;
} _tcpsock;

typedef tcpsock _tcpsock;

int tcpsock_server_init(tcpsock *tsock,short port);

int tcpsock_client_init(tcpsock *tsock);

int tcpsock_client_connect(tcpsock *tsock,char *addr,short port);

int tcpsock_server_accept(tcpsock *tsock,tcpsock *client,struct timeval *t);

int tcpsock_read(tcpsock tsocks[],int len,struct timeval *t);

int tcpsock_write(tcpsock tsocks[],int len,struct timeval *t);

