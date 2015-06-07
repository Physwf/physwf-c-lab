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
	void broadcast(mid_t mid, char* body, size_t size);
protected:
	static cid_t getNextId();
	void tryCreate(ServiceConnection* conn);
	inline Player* addPlayer(pid_t pid, Player* player);
	inline Player* findPlayer(pid_t pid);
	inline Player* removePlayer(pid_t pid);
	inline int addToCounter(ServiceConnection* conn);
protected:
	cid_t nCid;
	std::map<pid_t, Player*> mPlayers;
	std::map<ServiceConnection*, int> mCounter;
private:
	static cid_t nIncreaser;
};

typedef std::map<ServiceConnection*, int> map_counter;
#endif