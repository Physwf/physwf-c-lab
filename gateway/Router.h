#ifndef _ROUTER_H
#define _ROUTER_H

#include "Server.h"
#include "Connection.h"

class Router : public Object
{
public:
	Router();
	~Router();
public:
	void start();
private:
	void onConnection(int fd, int event, void* data);
	void onMessage(Connection* conn);
	void onClose(Connection* conn);
private:
	Connection* pAllClients;

private:
	EventLoop *pLoop;
	Server* pServer;
};
#endif