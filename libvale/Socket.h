#ifndef _SOCKET_H
#define _SOCKET_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#define SOCKET_ERROR -1
#define SOCKET_OK 0

class Socket
{
public:
	Socket(int fd); 
	~Socket();

	int create(int domain);

public:
	int getFd() { return nFd; }
	int listen(struct sockaddr* addr,int len);
	int accpet(struct sockaddr* addr, int len);
	int connect(const char* addr, short port);
	int read(char* buffer,int size_t);
	int write(const char* buffer, int size_t);
	int close();
	int setNonBlock();
    int setReuseAddr();
    int setNonDelay();
	bool isValid() { return nFd == INVALID_SOCKET; }
private:
	int nFd;
	static int nCounter;
};

#endif