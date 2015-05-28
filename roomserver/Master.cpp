#include "Master.h"
#include "Message.h"

SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::pGateWay = NULL;
SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::pGame = NULL;

Master::Master()
{

}

Master::~Master()
{

}

SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::gateway()
{
	return pGateWay;
}

SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::game()
{
	return pGame;
}

void Master::start()
{
	pLoop = new EventLoop();

	pGateWay = new SyncMsgConnection<mid_t, MSG_HEAD_BACK>(pLoop);
	pGame = new SyncMsgConnection<mid_t, MSG_HEAD_BACK>(pLoop);
}

void Master::run()
{
	pLoop->run();
}
