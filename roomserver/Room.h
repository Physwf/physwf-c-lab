#ifndef _ROOM_H
#define _ROOM_H

#include <map>
#include <stdlib.h>

#include "Player.h"

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
private:
	std::map<unsigned long, Player*> mPlayers;

};
#endif