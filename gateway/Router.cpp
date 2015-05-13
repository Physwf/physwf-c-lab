#include "Router.h"

void Router::start()
{
	pLoop = new EventLoop();

	pServer = new Server(pLoop);
	pServer->setConnectionHandler(EV_IO_CB(this,Router::onConnection));
	pServer->createTcpServer(3456);
	pServer->start();
}

void Router::onConnection(int fd, int event, void* data)
{

}

void Router::onClose(Connection* conn)
{

}
