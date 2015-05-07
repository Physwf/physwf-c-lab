#ifndef _SOCKET_H
#define _SOCKET_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifdef WIN32
#include <WinSock2.h>
#endif

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
	int read(char* buffer,int len);
	int write(const char* buffer, int len);
	int close();
	int setNonBlock();
	bool isValid() { return nFd == INVALID_SOCKET; }
private:
	int nFd;
	static int nCounter;
};

#endif