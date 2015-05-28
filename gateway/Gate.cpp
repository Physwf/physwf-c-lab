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
	pFront = new Server(pLoop);
	pBack = new Server(pLoop);

	pFront->createTcpServer(2345);
	pBack->createTcpServer(1234);

	pFront->setConnectionHandler(EV_IO_CB(this, Gate::onFrontConnect));
	pFront->setConnectionHandler(EV_IO_CB(this, Gate::onBackConnect));

	pAuth = new Auth();
	pAuth->setClientAuthResultHandler(EV_CB(this, Gate::onClientAuthResult));
	pRouter = new Router();
	pAuth->setServiceAuthResultHandler(EV_CB(this, Gate::onServiceAuthResult));

	pFront->start();
	if (nMode & MODE_NEGATIVE)
		pBack->start();
	else
	{
		pRoomService = new ServiceConnection(pLoop);
		pAuthService = new ServiceConnection(pLoop);
	}
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
