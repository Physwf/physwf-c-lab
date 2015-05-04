#ifndef _SOCKET_H
#define _SOCKET_H

#ifdef WIN32
#include <WinSock2.h>
#endif

class Socket
{
public:
	Socket() :nFd(INVALID_SOCKET){}
	~Socket();

	static int create();

public:
	int getFd() { return nFd; }
	int listen();
	int accpet();
	int connect();
	int read();
	int write();
	int close();
	int setNonBlock();

private:
	int nFd;

};

#endif