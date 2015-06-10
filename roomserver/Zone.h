#ifndef _ZONE_H
#define _ZONE_H

#include "type.h"
#include "Object.h"
#include "Message.h"
#include "Player.h"

class Zone : public Object
{
public:
	Zone();
	~Zone();
public:
	void enterZone(ServiceConnection* conn, Player* player);
	void leaveZone(ServiceConnection* conn, Player* player);
	void broadcast(MSG_HEAD_BACK* head,char* body);
protected:
	static cid_t getNextId();
	void tryCreate(ServiceConnection* conn);
	void tryDestroy(ServiceConnection* conn);
	Player* addPlayer(pid_t pid, Player* player);
	Player* findPlayer(pid_t pid);
	Player* removePlayer(pid_t pid);
	inline int addGate(ServiceConnection* conn);
	inline int removeGate(ServiceConnection* conn);
protected:
	cid_t nCid;
	std::map<pid_t, Player*> mPlayers;
	std::map<ServiceConnection*, int> mGates;
private:
	static cid_t nIncreaser;
};

typedef std::map<ServiceConnection*, int> map_gates;
#endif