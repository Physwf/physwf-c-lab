#ifndef _MASTER_H
#define _MASTER_H

#include "Server.h"
#include "SyncMsgConnection.h"
#include "Hall.h"

class Master : public Object
{
public:
	Master();
	~Master();
public:
	void start();
	void connectGateWay();
	void connectGame();
	void run();

	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* game();
private:
	void startServer();
	void onGatewayConnected(int fd, int event, void* data);
private:
	Server* pServer;
	EventLoop* pLoop;
	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* pGame;
	Hall* pHall;
};

#endif