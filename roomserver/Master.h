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

	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* gateway();
	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* game();
private:
	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* pGateWay;
	static SyncMsgConnection<mid_t, MSG_HEAD_BACK>* pGame;
private:
	EventLoop* pLoop;
	
};

#endif