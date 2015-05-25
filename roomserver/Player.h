#ifndef _PLAYER_H
#define _PLAYER_H

#include "Connection.h"
#include "Room.h"

class Room;

#include "type.h"

class Player
{
public:
	Player();
	~Player();
public:
	rid_t setRoomId(rid_t rid) { nRid = rid; }
	rid_t getRoomId() { return nRid; }
	tid_t setTableId(tid_t tid) { nTid = tid; }
	tid_t getTableId() { return nTid; }
	pid_t pid() { return nId; }
private:
	pid_t nId;
	rid_t nRid;
	rid_t nTid;
};
#endif