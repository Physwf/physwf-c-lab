#include "Server.h"
#include <string.h>

Server::Server(EventLoop* loop, int fd) :pLoop(loop), sSocket(fd)
{

}

Server::~Server()
{

}

void Server::initSocket()
{
	sSocket.setNonBlock();
}

int Server::createTcpServer(int port)
{
	if (sSocket.create(AF_INET) == SOCKET_ERROR)
	{
		return -1;
	}
	sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);
	if (sSocket.listen((sockaddr*)&sa, sizeof sa) == SOCKET_ERROR)
	{
		sSocket.close();
		return -1;
	}
	initSocket();
	return 0;
}

void Server::start()
{
	pLoop->addEventListener(sSocket.getFd(), EV_IO_READ, EV_IO_CB(this, Server::onConnection), NULL);
}

void Server::stop()
{
	pLoop->removeEventListener(sSocket.getFd(), EV_IO_READ);
}

Socket& Server::getSocket()
{
	return sSocket;
}


void Server::onConnection(int fd, int event, void* data)
{
	sockaddr_in sa;
	int len = sizeof sa;
	int conn = sSocket.accpet((sockaddr*)&sa, len);
	if (conn == SOCKET_ERROR)
	{
#ifdef DEBUG
		printf("accept failed with error\n");
#endif
	}
	EV_INVOKE(cbConnection, conn,fd,data);
}
