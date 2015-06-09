#pragma once
#ifndef _SERVER_H
#define _SERVER_H

#include <string.h>

#include "EventLoop.h"
#include "Socket.h"

#include "platform.h"

class VALE_DLL Server : public Object
{
public:
	Server(EventLoop* loop,int fd=INVALID_SOCKET);
	~Server();
public:
	int createTcpServer(int port);
	void setConnectionHandler(const IOEventHandler &cb) { cbConnection = cb; }
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
