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
	Socket(); 
	~Socket();

	static Socket* create();

public:

	int getFd() { return nFd; }
	int listen(short port);
	int accpet();
	int connect(const char* addr, short port);
	int read(char* buffer,int len);
	int write(const char* buffer, int len);
	int close();
	int setNonBlock();

private:
	int nFd;
	static int nCounter;

};

#endif