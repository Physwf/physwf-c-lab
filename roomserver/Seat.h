#ifndef _SEAT_H
#define _SEAT_H

#include "Player.h"
#include "Zone.h"

#define STATUS_SIT 1
#define STATUS_STAND 2

class Seat : public Zone
{
public:
	Seat();
	Seat(sid_t id);
	~Seat();
public:
	void handleGameMessage(MSG_HEAD_GAME* head, char* body);
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
private:
	sid_t sid();
private:
	sid_t nSid;
};
#endif