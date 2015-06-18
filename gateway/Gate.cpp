#include "Gate.h"
#include "Log.h"
#include "Protocol.h"

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
	pAuth->setClientAuthResultHandler(EV_AH_CB(this, Gate::onClientAuthResult));
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
	Log::info("client connected! fd = %d", fd);
	ClientConnection* fCon = ClientConnection::create(pLoop, fd);
	fCon->setCloseHandler(EV_CB(this, Gate::onClientClose));
	pAuth->addClientForAuth(fCon);
}

void Gate::onClientClose(ClientConnection* con)
{
	Log::info("client closed!");
	if (!pAuth->removeClient(con))
	{
		Client* client = pRouter->findClient(con);
		destroyPlayer(client);
	}
	
	ClientConnection::destory(con);
	con = NULL;
}

void Gate::onBackConnect(int fd, int event, void* data)
{
	ServiceConnection* bCon = ServiceConnection::create(pLoop, fd);
	pAuth->addServiceForAuth(bCon);
}

void Gate::onBackClose(ServiceConnection* con)
{
	pAuth->removeService(con);
	ServiceConnection::destroy(con);
	con = NULL;
}

void Gate::onClientAuthResult(Client* client, bool success)
{
	if (success)
	{
		pRouter->addClientForRoute(client);
		createPlayer(client);
	}
}

void Gate::onServiceAuthResult(ServiceConnection* service, bool success)
{
	pRouter->setMaster(service);
}


void Gate::createPlayer(Client* client)
{
	MSG_HEAD_BACK bHead;
	bHead.id = MSG_CREATE_PLAYER_100;
	bHead.pid = client->pid;
	bHead.type = MSG_TYPE_PLAYER;
	bHead.rid = 0;
	bHead.tid = 0;
	bHead.cid = 0;
	bHead.err = 0;
	MSG_REQ_CREATE_PLAYER msg;
	msg.pid = client->pid;
	
	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &bHead, &msg);
	Log::debug("send create player,pid:%d",msg.pid);
	client->master->send(buffer, size);
}


void Gate::destroyPlayer(Client* client)
{
	MSG_HEAD_BACK bHead;
	bHead.id = MSG_DESTROY_PLAYER_101;
	bHead.pid = client->pid;
	bHead.type = MSG_TYPE_PLAYER;
	bHead.rid = 0;
	bHead.tid = 0;
	bHead.cid = 0;

	MSG_REQ_DESTROY_PLAYER msg;
	msg.pid = client->pid;

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &bHead, &msg);
	Log::debug("send destroy player,pid:%d",msg.pid);
	client->master->send(buffer, size);
}

int main(int argc, char**argv)
{
	Gate *gate = new Gate();
	gate->start();
}