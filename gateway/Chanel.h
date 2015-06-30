#ifndef _CHANEL_H
#define _CHANEL_H

#include "Message.h"
#include "SyncMsgConnection.h"

#include <set>

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
	cid_t cid() { return nCid; }
private:
	cid_t nCid;
	std::set<Client*> mClients;
};

typedef std::set<Client*> set_client;
#endif