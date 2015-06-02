#ifndef _ZONE_H
#define _ZONE_H

#include "type.h"
#include "Object.h"
#include "Message.h"

class Zone : public Object
{
public:
	Zone(ServiceConnection* game) :pGame(game) { }
	~Zone();
protected:
	static cid_t getNextId();
	void tryCreate();
	void broadcast(mid_t mid, char* body, size_t size);
protected:
	cid_t nCid;
	ServiceConnection* pGame;
private:
	static cid_t nIncreaser;
};
#endif