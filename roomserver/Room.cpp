#include "Protocol.h"
#include "Room.h"

Room::Room(ServiceConnection* game) : Zone(game)
{
	
}

Room::~Room()
{

}

err_t Room::enterPlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		addPlayer(player->pid(),player);
	}
	else if (old == player)
	{
		err = MSG_ERR_ALREADY_IN_1002;
	}
	else//log in different places. to do
	{
		addPlayer(player->pid(), player);
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
	Player* old = removePlayer(player->pid());
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


err_t Room::tryEnterGame(gid_t tid, Player* player)
{
	Game* game = findGame(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->enterPlayer(player);
}


err_t Room::tryLeaveGame(gid_t tid, Player* player)
{
	Game* game = findGame(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->leavePlayer(player);
}


Game* Room::findGame(gid_t gid)
{
	map_game::iterator it = mGames.find(gid);
	if (it != mGames.end())
	{
		return it->second;
	}
	return NULL;
}

int Room::capacity()
{

}

int Room::avaliable()
{

}
