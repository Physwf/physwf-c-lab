#include "Zone.h"
#include "Protocol.h"


Zone::Zone()
{
	nCid = getNextId();
}

Zone::~Zone()
{

}

cid_t Zone::nIncreaser = 0;

cid_t Zone::getNextId()
{
	return ++nIncreaser;
}

void Zone::tryCreate(ServiceConnection* conn)
{
	if (addGate(conn) == 1)
	{
		MSG_HEAD_BACK head;
		head.id = MSG_CREATE_CHANEL_102;
		head.type = MSG_TYPE_CHANEL;
		head.pid =head.rid = head.tid = 0;
		head.err = 0;
		MSG_CREATE_CHANEL body;
		body.cid = nCid;
		char data[4] = { 0 };
		size_t bSize = 0;
		body.writeBody(data, &bSize);
		conn->send((char*)&head, sizeof(MSG_HEAD_BACK), data, bSize);
	}
}


void Zone::tryDestroy(ServiceConnection* conn)
{
	if (removeGate(conn) <= 0)
	{
		MSG_HEAD_BACK head;
		head.id = MSG_DESTROY_CHANEL_103;
		head.type = MSG_TYPE_CHANEL;
		head.rid = 0;
		head.tid = 0;
		head.pid = 0;
		head.err = 0;
		MSG_CREATE_CHANEL body;
		body.cid = nCid;
		char data[4] = { 0 };
		size_t bSize = 0;
		body.writeBody(data, &bSize);
		conn->send((char*)&head, sizeof(MSG_HEAD_BACK), data, bSize);
	}
}

Player* Zone::addPlayer(pid_t pid, Player* player)
{
	mPlayers.insert(map_player::value_type(pid, player));
	return player;
}

Player* Zone::findPlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		return it->second;
	}
	return NULL;
}

Player* Zone::removePlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		Player* ret = it->second;
		mPlayers.erase(it);
		return ret;
	}
	return NULL;
}


int Zone::addGate(ServiceConnection* conn)
{
	map_gates::iterator it = mGates.find(conn);
	if (it != mGates.end())
	{
		return it->second++;
	}
	else
	{
		mGates.insert(map_gates::value_type(conn, 1));
		return 1;
	}
}


int Zone::removeGate(ServiceConnection* conn)
{
	map_gates::iterator it = mGates.find(conn);
	if (it != mGates.end())
	{
		if (it->second <= 1)
		{
			mGates.erase(it);
		}
		else
		{
			return it->second--;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

void Zone::enterZone(ServiceConnection* conn, Player* player)
{
	tryCreate(conn);

	MSG_HEAD_BACK head;
	head.id = MSG_CHANEL_STATUS_104;
	head.type = MSG_TYPE_CHANEL;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = head.tid = 0;

	MSG_CHANEL_STATUS msg;
	msg.status_type = CHANEL_STATUS_ADD_PLAYER;
	msg.value = player->pid(); 

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);
	conn->send(buffer, size);
}

void Zone::leaveZone(ServiceConnection* conn, Player* player)
{
	tryDestroy(conn);

	MSG_HEAD_BACK head;
	head.id = MSG_CHANEL_STATUS_104;
	head.type = MSG_TYPE_CHANEL;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = head.tid = 0;

	MSG_CHANEL_STATUS msg;
	msg.status_type = CHANEL_STATUS_RMV_PLAYER;
	msg.value = player->pid();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);
	conn->send(buffer, size);
}

void Zone::broadcast(MSG_HEAD_BACK* head, char* body)
{
	head->type = MSG_TYPE_BROADCAST;
	head->err = 0;
	head->cid = nCid;

	char buffer[32] = {0};
	int size = pack_back_msg2(buffer, head, body);
	for (map_gates::iterator it = mGates.begin(); it != mGates.end(); it++)
	{
		it->first->send(buffer, size);
	}
}


