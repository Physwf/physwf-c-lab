#ifndef _TABLE_H
#define _TABLE_H

#include "type.h"
#include "Game.h"
#include "Zone.h"

class Table : public Zone
{
public:
	Table();
	~Table();
public:
	void startGame();
	void endGame();
	void handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	void handleGameMessage(GameConnection* conn, MSG_HEAD_GAME* head, char* body);
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
	tid_t tid() { return nTid; }
private:
	void doForward(MSG_HEAD_BACK* head, char* body);
	void createGame(GameConnection* conn);
	void destoryGame(GameConnection* conn);
private:
	Game *pGame;
	tid_t nTid;
	bool isAlive;
};

#endif