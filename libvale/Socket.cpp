#include "Socket.h"


Socket::Socket() : nFd(INVALID_SOCKET)
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

Socket* Socket::create()
{
	Socket* result = new Socket();
	int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
#ifdef DEBUG
		printf("Create Socket Error:%d!\n", WSAGetLastError());
#endif
	}
	result->nFd = fd;
	return result;
}

int Socket::listen(short port)
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa.sin_port = port;
	int iResult = bind(nFd, (SOCKADDR*)&sa, sizeof sa);
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

int Socket::accpet()
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