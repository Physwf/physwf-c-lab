#include "Master.h"
#include "Message.h"




SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::pGame = NULL;

Master::Master()
{

}

Master::~Master()
{

}


SyncMsgConnection<mid_t, MSG_HEAD_BACK>* Master::game()
{
	return pGame;
}

void Master::start()
{
	pLoop = new EventLoop();

	
	pGame = new SyncMsgConnection<mid_t, MSG_HEAD_BACK>(pLoop);
	pGame->setConnectHandler(EV_CB(this,Master::startServer));
	pGame->setMessageHandler();
}

void Master::startServer()
{
	pServer = new Server(pLoop);
	pServer->start();
	pServer->setConnectionHandler(EV_IO_CB(this,Master::onGatewayConnected));
	pHall = new Hall();
}


void Master::onGatewayConnected(int fd, int event, void* data)
{
	ServiceConnection* service = new ServiceConnection(pLoop, fd);
	pHall->addGateWay(service);
	//ServiceConnection
}

void Master::run()
{
	pLoop->run();
}
