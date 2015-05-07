#include "Socket.h"


Socket::Socket(int fd) : nFd(fd)
{ 
#ifdef WIN32
	if (!nCounter)
	{
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		assert(iResult == 0);
	}
	nCounter++;
#endif
}

Socket::~Socket()
{
	//nCounter--;
}

int Socket::create(int domain)
{
	nFd = socket(domain, SOCK_STREAM, IPPROTO_TCP);
	if (nFd == INVALID_SOCKET)
	{
#ifdef DEBUG
		printf("Create Socket Error:%d!\n", WSAGetLastError());
#endif
	}
	return nFd;
}

int Socket::listen(sockaddr* addr,int len)
{
	int iResult = bind(nFd, (SOCKADDR*)addr, len);
	if (iResult == SOCKET_ERROR)
	{
#ifdef DEBUG
		printf("bind failed with error:%d!",WSAGetLastError());
#endif
		return iResult;
	}
	iResult = ::listen(nFd, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
#ifdef DEBUG
		printf("listen failed with error:%d!", WSAGetLastError());
#endif
	}
	return iResult;
}

int Socket::accpet(struct sockaddr* addr, int len)
{

}


int Socket::connect(const char* addr, short port)
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(addr);
	sa.sin_port = port;
	int iResult = ::connect(nFd, (SOCKADDR*)&sa, sizeof sa);
	if (iResult == SOCKET_ERROR)
	{
#ifdef DEBUG
		printf("connect failed with error:%d!", WSAGetLastError());
#endif
	}
	return iResult;
}

int Socket::read(char* buffer, int len)
{
#ifdef WIN32
	int iRecv = recv(nFd,buffer,len,0);
	if (iRecv < 0)
	{
#ifdef DEBUG
		printf("read failed with error:%d!", WSAGetLastError());
#endif
	}
	return iRecv;
#else
	//todo
#endif
}

int Socket::write(const char* buffer, int len)
{
#ifdef WIN32
	int iSend = send(nFd, buffer, len, 0);
	if (iSend == SOCKET_ERROR)
	{
#ifdef DEBUG
		printf("send failed with error:%d!", WSAGetLastError());
#endif
	}
	return iSend;
#else
	//todo
#endif
}

int Socket::close()
{
#ifdef WIN32
	closesocket(nFd);
	nCounter--;
	if (!nCounter)
	{
		WSACleanup();
	}
#endif
}

int Socket::setNonBlock()
{
	
#ifdef WIN32
	unsigned long non_block = 1;
	if (ioctlsocket(nFd, FIONBIO, &non_block) == SOCKET_ERROR)
	{
		return -1;
	}
#else
	int flags;
	if (flags = fcntl(nFd, F_GETFL) == -1)
		return -1;
	if (fcntl(nFd, F_SETFL, flags | O_NONBLOCK))
		return -1;
#endif
	return 0;
}
