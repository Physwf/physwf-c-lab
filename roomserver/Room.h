#ifndef _ROOM_H
#define _ROOM_H

#include <map>
#include <stdlib.h>

#include "Player.h"
#include "Zone.h"
#include "Table.h"

#include "type.h"

class Room : public Zone
{
public:
	Room();
	~Room();
public:
	int capacity();
	int avaliable();
	rid_t rid() { return nRid; }
public:
	void handleWorldMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	err_t enterPlayer(Player* player);
	err_t leavePlayer(Player* player);
	err_t tryEnterTable(tid_t tid, Player* player);
	err_t tryLeaveTable(tid_t tid, Player* player);
	err_t startNewGame();
	err_t destroyGame();
private:
	void onReqJoinGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	void onReqLeaveGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	void doForward(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
private:
	void enterGameSuccess(ServiceConnection* conn, Player* player, err_t reason);
	void enterGameFailed(ServiceConnection* conn, Player* player, err_t reason);
	void leaveGameSuccess(ServiceConnection* conn, Player* player, err_t reason);
	void leaveGameFailed(ServiceConnection* conn, Player* player, err_t reason);
private:
	Table* table(tid_t gid);
private:
	rid_t nRid;
	std::map<tid_t, Table*> mTables;
};

typedef std::map<tid_t, Table*> map_table;

#endif