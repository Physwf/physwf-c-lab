#ifndef _ZONE_H
#define _ZONE_H

#include "type.h"
#include "Object.h"
#include "Message.h"
#include "Player.h"

class Zone : public Object
{
public:
	Zone(GameConnection* game) :pGame(game) { }
	~Zone();
public:
	void enterZone(ServiceConnection* conn, Player* player);
	void leaveZone(ServiceConnection* conn, Player* player);
	void broadcast(mid_t mid, char* body, size_t size);
protected:
	static cid_t getNextId();
	void tryCreate();
	inline Player* addPlayer(pid_t pid, Player* player);
	inline Player* findPlayer(pid_t pid);
	inline Player* removePlayer(pid_t pid);
protected:
	cid_t nCid;
	GameConnection* pGame;
	std::map<pid_t, Player*> mPlayers;
private:
	static cid_t nIncreaser;
};

#endif