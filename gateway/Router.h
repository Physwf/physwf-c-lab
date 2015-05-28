#ifndef _ROUTER_H
#define _ROUTER_H

#include "Message.h"

class Router : public Object
{
public:
	Router();
	~Router();
public:
	void addClientForRoute(ClientConnection* client);
	void addServiceForRoute(ServiceConnection* service);
private:
private:

private:
};
#endif