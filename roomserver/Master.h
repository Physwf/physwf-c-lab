#ifndef _MASTER_H
#define _MASTER_H

#include "Server.h"
#include "SyncMsgConnection.h"
#include "World.h"

class Master : public Object
{
public:
	Master();
	~Master();
public:
	void start();
	void run();
private:
	void onGatewayConnected(int fd, int event, void* data);
private:
	Server* pServer;
	EventLoop* pLoop;
	GameConnection* pGame;
	World* pWorld;
};

#endif