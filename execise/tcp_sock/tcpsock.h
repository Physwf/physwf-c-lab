#include <sys/socket.h>
#include <sys/types.h>

struct {
	int sockfd;
	char buffer[1024];
} _tcpsock;

typedef tcpsock _tcpsock;


