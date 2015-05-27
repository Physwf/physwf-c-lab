#ifndef _ROUTER_H
#define _ROUTER_H

#include "Server.h"
#include "Gate.h"

class Router : public Object
{
public:
	Router();
	~Router();
public:
	void addToAuth(FrontConnection* front);
	void addToService(FrontConnection* front);
private:
private:

private:
};
#endif