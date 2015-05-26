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

	static SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* gateway();
	static SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* game();
private:
	static SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* pGateWay;
	static SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* pGame;
private:
	EventLoop* pLoop;
	
};

#endif