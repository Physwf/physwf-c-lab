#ifndef _PLAYER_H
#define _PLAYER_H

#include "Message.h"

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
	void joinGame(gid_t which);
	void leaveGame();
public:
	void setGate(ServiceConnection* gate);
	//void setGame(GameConnection* game);
public:
	void setRoomId(rid_t rid) { nRid = rid; }
	rid_t getRoomId() { return nRid; }
	void setTableId(gid_t tid) { nTid = tid; }
	gid_t getTableId() { return nTid; }
	void setChanelId(cid_t cid) { nCid = cid; }
	cid_t getChanelId() { return nCid; }
	pid_t pid() { return nId; }
private:
	pid_t nId;
	rid_t nRid;
	gid_t nTid;
	cid_t nCid;
private:
	ServiceConnection* pGate;
	GameConnection* pGame;
};

#include <map>

typedef std::map<pid_t, Player*> map_player;

#endif