#include "Master.h"
#include "Message.h"
#include "GamePool.h"

#include "Log.h"

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
	pServer->createTcpServer(1234);
	pServer->setConnectionHandler(EV_IO_CB(this, Master::onGatewayConnected));
	pServer->start();

	pWorld = new World();
}

void Master::onGatewayConnected(int fd, int event, void* data)
{
	Log::info("GateWay Connected : fd = %d",fd);
	ServiceConnection* service = ServiceConnection::create(pLoop, fd);
	pWorld->addGateWay(service);
	//ServiceConnection
}

void Master::run()
{
	pLoop->run();
}

int main(int argc, char** argv)
{
	Master* master = new Master();
	master->start();
	master->run();
}