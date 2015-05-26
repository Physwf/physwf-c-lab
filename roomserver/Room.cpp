#include "Room.h"

Room::Room()
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

int Room::capacity()
{

}

int Room::avaliable()
{

}
