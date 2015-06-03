#ifndef _CHANEL_H
#define _CHANEL_H

#include "Message.h"
#include "SyncMsgConnection.h"

#include <map>

#include "Auth.h"

class Chanel
{
public:
	Chanel(cid_t id);
	~Chanel();
public:
	void broadcast(MSG_HEAD_GATE* head,char* body);
	void addClient(Client* front);
	void removeClient(Client* front);
private:
	cid_t nCid;
	std::map<cid_t, Client*> mClients;
};

#endif