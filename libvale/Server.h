#ifndef _SERVER_H
#define _SERVER_H

#include "EventLoop.h"
#include "Socket.h"

class Server : public Object
{
public:
	Server(EventLoop* loop,int fd);
	~Server();
public:
	int createTcpServer(int port);
	void start();
	void stop();
	Socket& getSocket();
private:
	void initSocket();
	void onConnection(int fd, int event, void* data);
private:
	EventLoop* pLoop;
	IOEventHandler cbConnection;
	Socket sSocket;
};
#endif