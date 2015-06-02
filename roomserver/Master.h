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
	void startServer();
	void onGatewayConnected(int fd, int event, void* data);
	void onGameMessage(ServiceConnection* conn, char* head, char* body);
private:
	Server* pServer;
	EventLoop* pLoop;
	SyncMsgConnection<mid_t, MSG_HEAD_BACK>* pGame;
	World* pWorld;
};

#endif