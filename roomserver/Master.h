#ifndef _MASTER_H
#define _MASTER_H

#include "SyncMsgConnection.h"

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

	static SyncMsgConnection* gateway();
	static SyncMsgConnection* game();
private:
	static SyncMsgConnection* pGateWay;
	static SyncMsgConnection* pGame;
private:
	EventLoop* pLoop;
	
};

#endif