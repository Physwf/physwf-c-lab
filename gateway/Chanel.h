#ifndef _CHANEL_H
#define _CHANEL_H

#include "Message.h"
#include "SyncMsgConnection.h"

#include <map>

class Chanel
{
public:
	Chanel(cid_t id);
	~Chanel();
public:
	void broadcast();
	void addClient(FrontConnection* front);
private:
	cid_t nCid;
	std::map <cid_t, FrontConnection*> mFronts;
};

#endif