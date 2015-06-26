#ifndef _PLAYER_H
#define _PLAYER_H

#include "Message.h"
#include "ServiceConnection.h"
#include "GameConnection.h"
#include "type.h"

class Player
{
public:
	Player();
	Player(pid_t id) :nId(id) { }
	~Player();
public:
	void init();
	void enterRoom(rid_t which);
	void leaveRoom();
	void joinGame(tid_t which);
	void leaveGame();
public:
	void setGate(ServiceConnection* gate);
	void send(MSG_HEAD_BACK* head, char* body);
	//void setGame(GameConnection* game);
public:
	void setRoomId(rid_t rid) { nRid = rid; }
	rid_t getRoomId() { return nRid; }
	void setTableId(tid_t tid) { nTid = tid; }
	tid_t getTableId() { return nTid; }
	void setChanelId(cid_t cid) { nCid = cid; }
	cid_t getChanelId() { return nCid; }
	void setSeatId(sid_t sid) { nSid = sid; }
	sid_t getSeatId() { return nSid; }
	void setStatus(unsigned char status) { nStatus = status; }
	unsigned char getStatus() { return nStatus; }
	pid_t pid() { return nId; }
private:
	pid_t nId;
	rid_t nRid;
	tid_t nTid;
	cid_t nCid;
	sid_t nSid;
	unsigned char nStatus;
private:
	ServiceConnection* pGate;
	GameConnection* pGame;
};

#include <map>

typedef std::map<pid_t, Player*> map_player;

#endif