#include "Router.h"
#include "Protocol.h"


Router::Router(ServiceConnection* service) :pMaster(service)
{
	pBuffer = new Buffer(1024 * 1024);
}

Router::~Router()
{

}

void Router::addClientForRoute(Client* client)
{
	addClient(client);
	client->connection->setMessageHandler(EV_CB(this, Router::onMasterMessage));
}

void Router::addServiceForRoute(ServiceConnection* service)
{
	service->setMessageHandler(EV_CB(this,Router::doServiceRoute));
}


Client* Router::addClient(Client* client)
{
	mClients.insert(map_client::value_type(client->connection, client));
}


Client* Router::findClient(ClientConnection* conn)
{
	map_client::iterator it = mClients.find(conn);
	if (it != mClients.end())
		return it->second;
	return NULL;
}


Client* Router::findClient(pid_t pid)
{

}

Client* Router::removeClient(ClientConnection* conn)
{
	map_client::iterator it = mClients.find(conn);
	if (it != mClients.end())
	{
		mClients.erase(it);
		return it->second;
	}
	return NULL;
}


Chanel* Router::createChanel(cid_t cid)
{
	mChanels.insert(map_chanel::value_type(cid, new Chanel(cid)));
}


Chanel* Router::findChanel(cid_t cid)
{
	map_chanel::iterator it = mChanels.find(cid);
	if (it != mChanels.end())
	{
		return it->second;
	}
	return NULL;
}

void Router::doClientRoute(ClientConnection* conn, char* head, char* body)
{
	//pBuffer->append(head, hsize);
	//pBuffer->append(body, bsize);
	//
	MSG_HEAD_GATE* pHead = (MSG_HEAD_GATE*)head;
	Client* client = findClient(conn);
	MSG_HEAD_BACK pBack;
	pBack.id = pHead->id;
	pBack.length = pHead->length;
	//pBack.rid = 
	//pBack.tid
	pMaster->send((char*)&pBack, sizeof(MSG_HEAD_BACK), body, pHead->length);
	//pMaster->send(pBuffer->data(), pBuffer->bytesAvaliable());
	//pMaster->send();
}


void Router::onMasterMessage(ServiceConnection* conn, char* head, char* body)
{
	MSG_HEAD_BACK* pBack = (MSG_HEAD_BACK*)head;
}

void Router::doServiceRoute(ServiceConnection* conn, char* head, char* body)
{
	MSG_HEAD_BACK* pBack = (MSG_HEAD_BACK*)head;
	MSG_HEAD_GATE pGate;
	pGate.id = pBack->id;
	pGate.length = pBack->length;
	pGate.err = pBack->err;
}

