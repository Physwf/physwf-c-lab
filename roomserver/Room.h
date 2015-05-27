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
	int capacity();
	int avaliable();
	rid_t rid() { return nRid; }
public:
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
private:
	inline void add(Player* player);
	inline void remove(Player* player);
	inline Player* find(pid_t pid);
	inline Player* findAndRemove(pid_t pid);
private:
	rid_t nRid;
	std::map<pid_t, Player*> mPlayers;
	table_t* pTables;
	std::map<tid_t, table_t*> mTables;

};

typedef std::map<rid_t, Room*> map_room;

#endif