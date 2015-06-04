#ifndef _PLAYER_H
#define _PLAYER_H

#include "Connection.h"

#include "type.h"

class Player
{
public:
	Player();
	Player(pid_t id) :nId(id) { }
	~Player();
public:
	void enterRoom(rid_t which);
	void leaveRoom();
	void joinGame(tid_t which);
	void leaveGame();
public:
	void setRoomId(rid_t rid) { nRid = rid; }
	rid_t getRoomId() { return nRid; }
	void setTableId(tid_t tid) { nTid = tid; }
	tid_t getTableId() { return nTid; }
	void setChanelId(cid_t cid) { nCid = cid; }
	cid_t getChanelId() { return nCid; }
	pid_t pid() { return nId; }
private:
	pid_t nId;
	rid_t nRid;
	tid_t nTid;
	cid_t nCid;
};

#include <map>

typedef std::map<pid_t, Player*> map_player;

#endif