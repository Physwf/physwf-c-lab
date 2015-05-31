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

	connectMaster();

	pLoop->run();
}



void Gate::connectMaster()
{
	pMaster = new ServiceConnection(pLoop);
	pMaster->setConnectHandler(EV_CB(this, Gate::onMasterConnect));
}

void Gate::onMasterConnect(ServiceConnection* con)
{
	connectAuth();
}

void Gate::connectAuth()
{
	ServiceConnection* authService = new ServiceConnection(pLoop);
	authService->setConnectHandler(EV_CB(this, Gate::onAuthConnected));
}


void Gate::onAuthConnected(ServiceConnection* con)
{
	pAuth = new Auth(con);
	pAuth->setClientAuthResultHandler(EV_CB(this, Gate::onClientAuthResult));
	//pAuth->setServiceAuthResultHandler(EV_CB(this, Gate::onServiceAuthResult));

	pFront = new Server(pLoop);
	//pBack = new Server(pLoop);

	pFront->createTcpServer(2345);
	//pBack->createTcpServer(1234);

	pFront->setConnectionHandler(EV_IO_CB(this, Gate::onFrontConnect));
	//pBack->setConnectionHandler(EV_IO_CB(this, Gate::onBackConnect));

	pFront->start();
	//pBack->start();

	pRouter = new Router();
}

void Gate::onFrontConnect(int fd, int event, void* data)
{
	ClientConnection* fCon = new ClientConnection(pLoop, fd);
	pAuth->addClientForAuth(fCon);
}

void Gate::onFrontClose(ClientConnection* con)
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

void Gate::onClientAuthResult(ClientConnection* client, bool success)
{
	pRouter->addClientForRoute(client);
}

void Gate::onServiceAuthResult(ServiceConnection* service, bool success)
{
	pRouter->addServiceForRoute(service);
}
