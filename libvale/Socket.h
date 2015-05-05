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
#ifdef WIN32
	static Socket* create();
#else
	static int create();
#endif

public:
#ifdef WIN32
	SOCKET getFd() { return nFd; }
#else
	int getFd() { return nFd; }
#endif
	int listen(short port);
	int accpet();
	int connect(const char* addr, short port);
	int read(char* buffer,int len);
	int write(const char* buffer, int len);
	int close();
	int setNonBlock();

private:
#ifdef WIN32
	SOCKET nFd;
#else
	int nFd;
#endif
	static int nCounter;

};

#endif