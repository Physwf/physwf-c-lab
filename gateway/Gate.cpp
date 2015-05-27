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

	pFront->start();
	if (nMode & MODE_NEGATIVE)
		pBack->start();
	else
	{
		pRoom = new BackConnection(pLoop);
		pAuth = new BackConnection(pLoop);
	}
}

void Gate::onFrontConnect(int fd, int event, void* data)
{
	FrontConnection* fCon = new FrontConnection(pLoop, fd);
	fBuffer.insert(fCon);
}

void Gate::onFrontClose(FrontConnection* con)
{
	fBuffer.erase(con);
	delete con;
	con = NULL;
}

void Gate::onBackConnect(int fd, int event, void* data)
{
	BackConnection* bCon = new BackConnection(pLoop, fd);
	bBuffer.insert(bCon);
}

void Gate::onBackClose(BackConnection* con)
{
	bBuffer.erase(con);
	delete con;
	con = NULL;
}
