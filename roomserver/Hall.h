#ifndef _HALL_H
#define _HALL_H

#include <map>

#include "type.h"
#include "Protocol.h"
#include "Room.h"

class Hall : public Object
{
public:
	Hall();
	~Hall();
public:
	void initialize();
private:
	void onNewPlayer(void* head, void* body);
	void onDestroyPlayer(void* head, void* body);
	void onReqEnterRoom(void* head, void* body);
	void onReqLeaveRoom(void* head, void* body);
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
	std::map<rid_t, Room*> mRooms;
	std::map<pid_t, Player*> mPlayers;

};
#endif