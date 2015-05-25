#ifndef _ROOM_H
#define _ROOM_H

#include <map>
#include <stdlib.h>

#include "Player.h"

#include "type.h"

#define TABLE_MAX_PLAYERS 5

typedef struct s_room
{
	rid_t rid;
	pid_t players[TABLE_MAX_PLAYERS];
} room_t;
class Room
{
public:
	Room();
	~Room();
public:
	void add(Player* player);
	void remove(Player* player);
	int capacity();
	int avaliable();

	rid_t rid() { return nRid; }
private:
	rid_t nRid;
	std::map<pid_t, Player*> mPlayers;

};
#endif