#include <sys/socket.h>
#include <sys/types.h>

struct {
	int sockfd;
	char buffer[1024];
	int position;
} _tcpsock;

typedef tcpsock _tcpsock;


