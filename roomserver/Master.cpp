#include "Master.h"
#include "Message.h"

SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* Master::pGateWay = NULL;
SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* Master::pGame = NULL;

Master::Master()
{

}

Master::~Master()
{

}

SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* Master::gateway()
{
	return pGateWay;
}

SyncMsgConnection<mid_t, MSG_HEAD_ROOM>* Master::game()
{
	return pGame;
}

void Master::start()
{
	pLoop = new EventLoop();

	pGateWay = new SyncMsgConnection<mid_t,MSG_HEAD_ROOM>(pLoop);
	pGame = new SyncMsgConnection<mid_t, MSG_HEAD_ROOM>(pLoop);
}

void Master::run()
{
	pLoop->run();
}
