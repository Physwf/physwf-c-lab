#ifndef _ROUTER_H
#define _ROUTER_H

#include "Message.h"
#include "Session.h"

struct Client
{
	ClientConnection* connection;
	Session* session;
};

struct Service
{
	ServiceConnection* connection;
	char type;
};

class Router : public Object
{
public:
	Router(ServiceConnection* service);
	~Router();
public:
	void addClientForRoute(ClientConnection* client);
	void addServiceForRoute(ServiceConnection* service);
private:
	void doRoute(mid_t mid, char* head, size_t hsize, char* body, size_t bsize);
private:
	ServiceConnection* pMaster;
	Buffer* pBuffer;
private:
};
#endif