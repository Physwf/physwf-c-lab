#pragma once
#ifndef _SOCKET_H
#define _SOCKET_H


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "platform.h"

#ifdef WIN32
#include <Ws2tcpip.h>
#include <WinSock2.h>
typedef int socklen_t;
typedef SOCKET sock_t;
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
typedef int sock_t;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#define SOCKET_OK 0

class VALE_DLL Socket
{
public:
	Socket(int fd); 
	~Socket();

	int create(int domain);

public:
	int getFd() { return nFd; }
	int listen(struct sockaddr* addr,int len);
	int accpet(struct sockaddr* addr, int *len);
	int connect(const char* addr, short port);
	int read(char* buffer,int size_t);
	int write(const char* buffer, int size_t);
	int close();
	int setNonBlock();
    int setReuseAddr();
    int setNonDelay();
	int setKeepAlive();
	bool isValid() { return nFd != INVALID_SOCKET; }
private:
	int nFd;
#ifdef WIN32
	static int nCounter;
#endif
};

#endif
