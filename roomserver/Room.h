#ifndef _ROOM_H
#define _ROOM_H

#include <map>
#include <stdlib.h>

#include "Player.h"

#include "type.h"

#define TABLE_MAX_PLAYERS 5
#define ROOM_MAX_TABLES 10

typedef struct s_table
{
	rid_t tid;
	pid_t players[TABLE_MAX_PLAYERS];
} table_t;

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
	table_t* pTables;
	std::map<tid_t, table_t*> mTables;

};
#endif