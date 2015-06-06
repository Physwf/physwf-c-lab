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

	pGame = new GameConnection(pLoop);
	pGame->setConnectHandler(EV_CB(this,Master::startServer));
	pGame->setMessageHandler(EV_CB(this,Master::onGameMessage));
}

void Master::startServer()
{
	pServer = new Server(pLoop);
	pServer->start();
	pServer->setConnectionHandler(EV_IO_CB(this,Master::onGatewayConnected));
	pWorld = new World(pGame);
}


void Master::onGatewayConnected(int fd, int event, void* data)
{
	ServiceConnection* service = new ServiceConnection(pLoop, fd);
	pWorld->addGateWay(service);
	//ServiceConnection
}


void Master::onGameMessage(GameConnection* conn, char* head, char* body)
{

}

void Master::run()
{
	pLoop->run();
}
