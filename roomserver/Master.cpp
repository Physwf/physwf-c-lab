#include "Master.h"
#include "Message.h"

Master::Master()
{

}

Master::~Master()
{

}

void Master::start()
{
	pLoop = new EventLoop();

	pGame = new SyncMsgConnection<mid_t, MSG_HEAD_BACK>(pLoop);
	pGame->setConnectHandler(EV_CB(this,Master::startServer));
	pGame->setMessageHandler(EV_CB(this,Master::onGameMessage));
}

void Master::startServer()
{
	pServer = new Server(pLoop);
	pServer->start();
	pServer->setConnectionHandler(EV_IO_CB(this,Master::onGatewayConnected));
	pWorld = new World();
}


void Master::onGatewayConnected(int fd, int event, void* data)
{
	ServiceConnection* service = new ServiceConnection(pLoop, fd);
	pWorld->addGateWay(service);
	//ServiceConnection
}


void Master::onGameMessage(ServiceConnection* conn, char* head, char* body)
{

}

void Master::run()
{
	pLoop->run();
}
