#include "Gate.h"


Gate::Gate()
{

}

Gate::~Gate()
{

}

void Gate::start()
{
	pLoop = new EventLoop();
	pRouter = new Router();

	connectMaster();

	pLoop->run();
}

void Gate::connectMaster()
{
	ServiceConnection* master = ServiceConnection::create(pLoop);
	master->setConnectHandler(EV_CB(this, Gate::onMasterConnect));
	master->setTest(1024);
	master->connect("127.0.0.1",1234);
}

void Gate::onMasterConnect(ServiceConnection* con)
{
	pRouter->setMaster(con);
	initServer();
}

void Gate::initServer()
{
	pAuth = new Auth();
	pAuth->setClientAuthResultHandler(EV_CB(this, Gate::onClientAuthResult));
	//pAuth->setServiceAuthResultHandler(EV_CB(this, Gate::onServiceAuthResult));

	pFront = new Server(pLoop);
	//pBack = new Server(pLoop);

	pFront->createTcpServer(2345);
	//pBack->createTcpServer(1234);

	pFront->setConnectionHandler(EV_IO_CB(this, Gate::onClientConnect));
	//pBack->setConnectionHandler(EV_IO_CB(this, Gate::onBackConnect));

	pFront->start();
	//pBack->start();
}

void Gate::onClientConnect(int fd, int event, void* data)
{
	ClientConnection* fCon = new ClientConnection(pLoop, fd);
	pAuth->addClientForAuth(fCon);
}

void Gate::onClientClose(ClientConnection* con)
{
	pAuth->removeClient(con);
	delete con;
	con = NULL;
}

void Gate::onBackConnect(int fd, int event, void* data)
{
	ServiceConnection* bCon = new ServiceConnection(pLoop, fd);
	pAuth->addServiceForAuth(bCon);
}

void Gate::onBackClose(ServiceConnection* con)
{
	pAuth->removeService(con);
	delete con;
	con = NULL;
}

void Gate::onClientAuthResult(Client* client, bool success)
{
	pRouter->addClientForRoute(client);
}

void Gate::onServiceAuthResult(ServiceConnection* service, bool success)
{
	pRouter->setMaster(service);
}

int main(int argc, char**argv)
{
	Gate *gate = new Gate();
	gate->start();
}