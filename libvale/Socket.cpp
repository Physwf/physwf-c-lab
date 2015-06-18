#include "Socket.h"

#ifdef WIN32
int Socket::nCounter = 0;
#endif
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
#if (defined DEBUG) && (defined WIN32)
		printf("Create Socket Error:%d!\n", WSAGetLastError());
#else
        printf("create socket error:%d!\n",errno);
#endif
	}
	return nFd;
}

int Socket::listen(sockaddr* addr,int len)
{
	int iResult = bind(nFd, (sockaddr*)addr, len);
	if (iResult == SOCKET_ERROR)
	{
#if (defined DEBUG) && (defined WIN32)
		printf("bind failed with error:%d!\n",WSAGetLastError());
#else
        printf("bind failed with error:%d!\n",errno);
#endif
		return iResult;
	}
	iResult = ::listen(nFd, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
#if (defined DEBUG) && (defined WIN32)
		printf("listen failed with error:%d!", WSAGetLastError());
#else
        printf("listen failed with error:%d!", errno);
#endif
	}
	return iResult;
}

int Socket::accpet(struct sockaddr* addr, int *len)
{
    int conn;
    while (true) {
        conn = ::accept(nFd, addr, (socklen_t*)len);
        if (conn == -1) {
#ifdef WIN32
			return SOCKET_ERROR;
#else
            if (errno == EINTR) {
				continue;
			}
			else{
				return SOCKET_ERROR;
			}
#endif
        }
        break;
    }
    return conn;
}


int Socket::connect(const char* addr, short port)
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
#ifdef WIN32
	//sa.sin_addr.s_addr = inet_pton(AF_INET, addr, new IN_ADDR);
	sa.sin_addr.s_addr = inet_addr(addr);
#else
	sa.sin_addr.s_addr = inet_addr(addr);
#endif // WIN32

	sa.sin_port = htons(port);
	int iResult = ::connect(nFd, (sockaddr*)&sa, sizeof sa);
	if (iResult == SOCKET_ERROR)
	{
#if (defined DEBUG) && (defined WIN32)
		printf("connect failed with error:%d!\n", WSAGetLastError());
#else
        printf("connect failed with error:%d!\n", errno);
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
	else if (iRecv == 0)
	{
	}
	return iRecv;
#else
    int nread = ::read(nFd,buffer,len);
    if (nread == -1) {
        if (errno == EAGAIN) {
            return 0;
        }
        return SOCKET_ERROR;
    }else if(nread == 0){
        return SOCKET_ERROR;
    }
    return nread;
    
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
    int nwrite = ::write(nFd, buffer, len);
    if (nwrite == -1) {
        return SOCKET_ERROR;
    }else if(nwrite == 0){
        return SOCKET_ERROR;
    }
    return nwrite;
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
#else
    ::close(nFd);
#endif
    return SOCKET_OK;
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
	if ((flags = fcntl(nFd, F_GETFL) == -1))
		return -1;
	if (fcntl(nFd, F_SETFL, flags | O_NONBLOCK))
		return -1;
#endif
	return 0;
}

int Socket::setNonDelay()
{
    return SOCKET_OK;
}


int Socket::setKeepAlive()
{
	return SOCKET_OK;
}

int Socket::setReuseAddr()
{
    return SOCKET_OK;
}
