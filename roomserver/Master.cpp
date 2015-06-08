#include "Master.h"
#include "Message.h"
#include "GamePool.h"

Master::Master()
{

}

Master::~Master()
{

}

void Master::start()
{
	pLoop = new EventLoop();

	GamePool::getInstance()->initialize(pLoop);

	pServer = new Server(pLoop);
	pServer->start();
	pServer->setConnectionHandler(EV_IO_CB(this, Master::onGatewayConnected));
	pWorld = new World();
}

void Master::onGatewayConnected(int fd, int event, void* data)
{
	ServiceConnection* service = new ServiceConnection(pLoop, fd);
	pWorld->addGateWay(service);
	//ServiceConnection
}

void Master::run()
{
	pLoop->run();
}
