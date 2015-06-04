#include "Protocol.h"
#include "Room.h"

Room::Room(ServiceConnection* game) :nCid(0), Zone(game)
{
	pTables = (table_t*)malloc(sizeof(table_t)*ROOM_MAX_TABLES);
	memset(pTables, 0, sizeof(table_t)*ROOM_MAX_TABLES);
	for (int i = 0; i < ROOM_MAX_TABLES;i++)
	{
		pTables[i].tid = i;
		mTables.insert(std::map<tid_t, table_t*>::value_type(pTables[i].tid, &pTables[i]));
	}
}

Room::~Room()
{

}

err_t Room::enterPlayer(Player* player)
{
	Player* old = findAndRemove(player->pid());
	err_t err = 0;
	if (!old)
	{
		add(player);
	}
	else if (old == player)
	{
		err = MSG_ERR_ALREADY_IN_1002;
	}
	else//log in different places. to do
	{
		add(player);
		old;//to do something;
	}
	if (!err)
	{
		tryCreate();
		player->setChanelId(nCid);
	}
		
	return err;
}

err_t Room::leavePlayer(Player* player)
{
	Player* old = findAndRemove(player->pid());
	err_t err = 0;
	if (!old)
	{
		err = MSG_ERR_NOT_IN_ROOM_1003;
	}
	else if (old != player)
	{
		//??
	}
	else
	{
	}
	return err;
}

void Room::add(Player* player)
{
	mPlayers.insert(std::map<pid_t, Player*>::value_type(player->pid(), player));
	player->setRoomId(nRid);
}

void Room::remove(Player* player)
{
	std::map<pid_t, Player*>::iterator target = mPlayers.find(player->pid());
	if (target != mPlayers.end())
	{
		mPlayers.erase(target);
	}
}


Player* Room::find(pid_t pid)
{

}


Player* Room::findAndRemove(pid_t pid)
{
	std::map<pid_t, Player*>::iterator target = mPlayers.find(pid);
	if (target != mPlayers.end())
	{
		mPlayers.erase(target);
		return target->second;
	}
	return NULL;
}

int Room::capacity()
{

}

int Room::avaliable()
{

}
