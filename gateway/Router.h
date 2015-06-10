#ifndef _ROUTER_H
#define _ROUTER_H

#include "Message.h"
#include "Session.h"
#include "Auth.h"
#include "Chanel.h"

#include <map>

typedef std::map<ClientConnection*, Client*> map_client;
typedef std::map<cid_t, Chanel*> map_chanel;

class Router : public Object
{
public:
	Router();
	~Router();
public:
	void addClientForRoute(Client* client);
	void setMaster(ServiceConnection* service);
private:
	inline Client* addClient(Client* client);
	inline Client* findClient(ClientConnection* conn);
	inline Client* findClient(pid_t pid);
	inline Client* removeClient(ClientConnection* conn);
	inline Chanel* createChanel(cid_t cid);
	inline Chanel* addToChanel(cid_t cid, Client* client);
	inline Chanel* removeFromChanel(cid_t cid, Client* client);
	inline Chanel* findChanel(cid_t cid);
private:
	void doClientRoute(ClientConnection* conn, char* head, char* body);
	void onMasterMessage(ServiceConnection* conn, char* head, char* body);
	void doServiceRoute(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	void onChanelMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
	void onBroadcastMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body);
private:
	ServiceConnection* pMaster;
	Buffer* pBuffer;
private:
	map_client mClients;
	map_chanel mChanels;
};
#endif