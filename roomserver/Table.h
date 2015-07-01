#ifndef _TABLE_H
#define _TABLE_H

#include "type.h"
#include "Game.h"
#include "Seat.h"

#include <map>

class Table : public Zone
{
public:
	Table();
	Table(tid_t tid);
	~Table();
public:
	void tryCreateGame();
	void endGame();
	void handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	err_t enterPlayer(Player* player,sid_t seat);
	err_t leavePlayer(Player* player);
	tid_t tid() { return nTid; }
private:
	void onGameMessage(GameConnection* conn, MSG_HEAD_GAME* head, char* body);
	void forwardToGame(MSG_HEAD_BACK* head, char* body);
	void notiGameStart();
	void notiGameEnd();
private:
	Seat* findSeat(sid_t sid);
private:
	Game *pGame;
	tid_t nTid;
	rid_t nRid;
	bool isAlive;
	std::map<sid_t, Seat*> mSeats;
};

typedef std::map<sid_t, Seat*> map_seat;

#endif