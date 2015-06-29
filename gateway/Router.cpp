#include "Router.h"
#include "Protocol.h"
#include "Log.h"

Router::Router()
{
	pBuffer = new Buffer(1024 * 1024);
}

Router::~Router()
{

}

void Router::addClientForRoute(Client* client)
{
	addClient(client);
	client->master = pMaster;
	client->connection->setMessageHandler(EV_M_CB(this, Router::doClientRoute));

}

void Router::setMaster(ServiceConnection* service)
{
	pMaster = service;
	pMaster->setMessageHandler(EV_M_CB(this, Router::onMasterMessage));
}


Client* Router::addClient(Client* client)
{
	mClients.insert(map_client::value_type(client->connection, client));
	return client;
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
	for (map_client::iterator it = mClients.begin(); it != mClients.end();it++)
	{
		if (it->second->pid == pid)
			return it->second;
	}
	return NULL;
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
	Chanel* chanel = new Chanel(cid);
	mChanels.insert(map_chanel::value_type(cid, chanel));
	return chanel;
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

void Router::doClientRoute(ClientConnection* conn, MSG_HEAD_GATE* head, char* body)
{
	Client *client = findClient(conn);
	MSG_HEAD_BACK pBack;
	pBack.id = head->id;
	pBack.length = head->length;
	pBack.type = MSG_TYPE_PLAYER;
	pBack.rid = client->rid;
	pBack.tid = client->tid;
	pBack.pid = client->pid;

	char buffer[MAX_MSG_LENGTH] = { 0 };
	int size = pack_back_msg2(buffer, &pBack, body);
	client->master->send(buffer, size);
}


void Router::onMasterMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	switch (head->type)
	{
	case MSG_TYPE_PLAYER:
	{
		doServiceRoute(conn, head, body);
		break;
	}
	case MSG_TYPE_CHANEL:
	{
		onChanelMessage(conn, head, body);
		break;
	}
	case MSG_TYPE_BROADCAST:
	{
		onBroadcastMessage(conn, head, body);
		break;
	}
	default:
		break;
	}
}

void Router::doServiceRoute(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Log::debug("service msg,id:%d", head->id);

	Client* client = findClient(head->pid);
	if (client == NULL)
	{
		LOG_DEBUG("failed to find client,mid:%d",head->id);
		return;
	}
		
	switch (head->id)
	{
	case MSG_ENTER_ROOM_1002:
		client->rid = head->rid;
		break;
	case MSG_LEAVE_ROOM_1003:
		client->rid = 0;
		break;
	case MSG_JOIN_TABLE_1004:
		client->tid = head->tid;
		break;
	case MSG_LEAVE_TABLE_1005:
		client->tid = 0;
		break;
	default:
		break;
	}

	MSG_HEAD_GATE gHead;
	gHead.id = head->id;
	gHead.length = head->length;
	gHead.err = head->err;
	char buffer[32] = { 0 };
	int size = pack_gate_msg2(buffer, &gHead, body);
	client->connection->send(buffer, size);
}

void Router::onChanelMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{

	switch (head->id)
	{
	case MSG_CREATE_CHANEL_102:
	{
		MSG_CREATE_CHANEL msg;
		msg.readBody(body, head->length);
		createChanel(msg.cid);
		break;
	}
	case MSG_CHANEL_STATUS_104:
	{
		MSG_CHANEL_STATUS msg;
		msg.readBody(body,head->length);
		Log::info("msg chanel status,cid:%d,status:%d,value:%d", head->cid, msg.status_type, msg.value);
		Chanel* chanel = findChanel(head->cid);
		Client* client = findClient(msg.value);
		if (msg.status_type == CHANEL_STATUS_ADD_PLAYER)
		{
			if (chanel && client)
			{
				chanel->addClient(client);
				client->rid = head->rid;
				client->tid = head->tid;
			}
		}
		else if (msg.status_type == CHANEL_STATUS_RMV_PLAYER)
		{
			if (chanel && client)
			{
				chanel->removeClient(client);
				client->rid = head->rid;
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

