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
	void handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
	gid_t tid() { return nTid; }
	
private:
	gid_t nTid;
	iid_t nIid;
};

#endif