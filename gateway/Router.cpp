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
	client->connection->setMessageHandler(EV_CB(this, Router::doClientRoute));
}

void Router::addServiceForRoute(ServiceConnection* service)
{
	service->setMessageHandler(EV_CB(this, Router::onMasterMessage));
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


Chanel* Router::addToChanel(cid_t cid, Client* client)
{
	Chanel* chanel = findChanel(cid);
	if (chanel)
	{
		chanel->addClient(client);
	}
}


Chanel* Router::removeFromChanel(cid_t cid, Client* client)
{
	Chanel* chanel = findChanel(cid);
	if (chanel)
	{
		chanel->removeClient(client);
	}
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
	Client *client = findClient(conn);
	MSG_HEAD_GATE* pHead = (MSG_HEAD_GATE*)head;
	Client* client = findClient(conn);
	MSG_HEAD_BACK pBack;
	pBack.id = pHead->id;
	pBack.length = pHead->length;
	pBack.rid = client->rid;
	pBack.tid = client->tid;
	pBack.pid = client->pid;
	//pBack.cid = client->
	pMaster->send((char*)&pBack, sizeof(MSG_HEAD_BACK), body, pHead->length);
	//pMaster->send(pBuffer->data(), pBuffer->bytesAvaliable());
	//pMaster->send();
}


void Router::onMasterMessage(ServiceConnection* conn, char* head, char* body)
{
	MSG_HEAD_BACK* pBack = (MSG_HEAD_BACK*)head;
	switch (pBack->type)
	{
	case MSG_TYPE_PLAYER:
	{
		doServiceRoute(conn, pBack, body);
		break;
	}
	case MSG_TYPE_CHANEL:
	{
		onChanelMessage(conn, pBack, body);
		break;
	}
	case MSG_TYPE_BROADCAST:
	{
		onBroadcastMessage(conn, pBack, body);
		break;
	}
	default:
		break;
	}
}

void Router::doServiceRoute(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_HEAD_GATE pGate;
	pGate.id = head->id;
	pGate.length = head->length;
	pGate.err = head->err;
	Client* client = findClient(head->pid);
	if (client)
	{
		client->connection->send((char*)&pGate, sizeof(MSG_HEAD_GATE), body, head->length);
	}
}

void Router::onChanelMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	switch (head->id)
	{
	case MSG_CREATE_CHANEL_100:
	{
		MSG_CREATE_CHANEL msg;
		msg.readBody(body, head->length);
		createChanel(msg.cid);
	}
	case MSG_CHANEL_STATUS_102:
	{
		MSG_CHANEL_STATUS msg;
		Chanel* chanel = findChanel(head->cid);
		Client* client = findClient(msg.value);
		if (msg.status_type == CHANEL_STATUS_ADD_PLAYER)
		{
			if (chanel && client)
			{
				chanel->addClient(client);
				client->rid = head->cid;
				client->tid = head->tid;
			}
		}
		else if (msg.status_type == CHANEL_STATUS_RMV_PLAYER)
		{
			if (chanel && client)
			{
				chanel->removeClient(client);
				client->rid = head->cid;
				client->tid = head->tid;
			}
		}
		break;
	}
	default:
		break;
	}
}

void Router::onBroadcastMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Chanel* chanel = findChanel(head->cid);
	MSG_HEAD_GATE hGate;
	hGate.id = head->id;
	hGate.length = head->length;
	hGate.err = 0;
	chanel->broadcast(&hGate, body);
}

