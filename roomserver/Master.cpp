#include "Master.h"
#include "Message.h"

SyncMsgConnection* Master::pGateWay = NULL;
SyncMsgConnection* Master::pGame = NULL;

Master::Master()
{

}

Master::~Master()
{

}

SyncMsgConnection* Master::gateway()
{
	return pGateWay;
}

SyncMsgConnection* Master::game()
{
	return pGame;
}

void Master::start()
{
	pLoop = new EventLoop();

	pGateWay = new SyncMsgConnection(pLoop);
	pGame = new SyncMsgConnection(pLoop);
}

void Master::run()
{
	pLoop->run();
}
