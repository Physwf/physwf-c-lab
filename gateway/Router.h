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
	Router();
	~Router();
public:
	void addClientForRoute(ClientConnection* client);
	void addServiceForRoute(ServiceConnection* service);
private:
	void doRoute(char* head, char* body);
private:

private:
};
#endif