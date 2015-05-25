#include "Room.h"

Room::Room()
{

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
