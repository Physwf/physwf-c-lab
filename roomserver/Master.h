#ifndef _MASTER_H
#define _MASTER_H

#include "RPCConnection.h"

class Master : public Object
{
public:
	Master();
	~Master();
public:
	void start();
	void run();
private:

private:
	RPCConnection* pGateWay;
};

#endif