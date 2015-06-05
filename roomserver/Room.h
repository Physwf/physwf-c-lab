#ifndef _ROOM_H
#define _ROOM_H

#include <map>
#include <stdlib.h>

#include "Player.h"
#include "Zone.h"
#include "Game.h"

#include "type.h"

class Room : public Zone
{
public:
	Room(ServiceConnection* game);
	~Room();
public:
	int capacity();
	int avaliable();
	rid_t rid() { return nRid; }
public:
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
	err_t tryEnterGame(gid_t tid, Player* player);
	err_t tryLeaveGame(gid_t tid, Player* player);
	err_t startNewGame();
	err_t destroyGame();
private:
	Game* findGame(gid_t gid);
private:
	rid_t nRid;
	std::map<gid_t, Game*> mGames;
};

typedef std::map<gid_t, Game*> map_game;

#endif