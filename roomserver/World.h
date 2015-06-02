#ifndef _HALL_H
#define _HALL_H

#include <map>

#include "type.h"
#include "Protocol.h"
#include "Room.h"
#include "Zone.h"

class World : public Zone
{
public:
	World(ServiceConnection* game);
	~World();
public:
	void initialize();
	void addGateWay(ServiceConnection* conn);
private:
	void onNewPlayer(ServiceConnection* conn, void* head, void* body);
	void onDestroyPlayer(ServiceConnection* conn, void* head, void* body);
	void onReqEnterRoom(ServiceConnection* conn, void* head, void* body);
	void onReqLeaveRoom(ServiceConnection* conn, void* head, void* body);
private:
	void tryEnterRoom(rid_t rid,Player* player);
	void enterRoomSuccess(pid_t pid,err_t reason);
	void enterRoomFailed(pid_t pid, err_t reason);
	void tryLeaveRoom(rid_t rid, Player* player);
	void leaveRoomSuccess(pid_t pid, err_t reason);
	void leaveRoomFailed(pid_t pid, err_t reason);
private:
	inline Room* findRoom(rid_t rid);
	inline Player* addPlayer(pid_t pid, Player* player);
	inline Player* findPlayer(pid_t pid);
	inline Player* removePlayer(pid_t pid);
private:
	cid_t nCid;
	ServiceConnection* pGame;
	std::map<rid_t, Room*> mRooms;
	std::map<pid_t, Player*> mPlayers;

};
#endif