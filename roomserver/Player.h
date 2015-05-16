#ifndef _PLAYER_H
#define _PLAYER_H

#include "Connection.h"

class Player
{
public:
	Player();
	Player(Connection* con);
	~Player();
private:
	Connection *pConnection;
};
#endif