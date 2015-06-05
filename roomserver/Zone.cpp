#include "Zone.h"
#include "Protocol.h"

Zone::~Zone()
{

}

cid_t Zone::nIncreaser = 0;

cid_t Zone::getNextId()
{
	return ++nIncreaser;
}

void Zone::tryCreate()
{
	if (!nCid)
	{
		nCid = getNextId();
		MSG_HEAD_BACK head;
		head.id = MSG_CREATE_CHANEL_100;
		head.type = MSG_TYPE_CHANEL;
		head.rid = head.tid = head.pid = 0;
		head.err = 0;
		MSG_CREATE_CHANEL body;
		body.cid = nCid;
		char data[4] = { 0 };
		size_t bSize = 0;
		body.writeBody(data, &bSize);
		pGame->send((char*)&head, sizeof(MSG_HEAD_BACK), data,bSize);
	}
}

Player* Zone::addPlayer(pid_t pid, Player* player)
{
	mPlayers.insert(map_player::value_type(pid, player));
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
		mPlayers.erase(it);
		return it->second;
	}
	return NULL;
}

void Zone::enterZone(ServiceConnection* conn, Player* player)
{
	MSG_HEAD_BACK head;
	head.id = MSG_CHANEL_STATUS_101;
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
	MSG_HEAD_BACK head;
	head.id = MSG_CHANEL_STATUS_101;
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

void Zone::broadcast(mid_t mid, char* body, size_t size)
{
	MSG_HEAD_BACK head;
	head.id = mid;
	head.type = MSG_TYPE_BROADCAST;
	head.err = 0;
	char body[32];
	pGame->send((char*)&head, sizeof(MSG_HEAD_BACK), body, size);
}


