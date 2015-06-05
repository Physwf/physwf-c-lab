#ifndef _TABLE_H
#define _TABLE_H

#include "type.h"

#include "Zone.h"

class Game : public Zone
{
public:
	Game();
	~Game();
public:
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
	gid_t tid() { return nTid; }
private:
	gid_t nTid;
};

#endif