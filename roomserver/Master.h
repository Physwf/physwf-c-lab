#ifndef _MASTER_H
#define _MASTER_H

#include "Connection.h"

class Master : public Object
{
public:
	Master();
	~Master();
public:
	void start();
	void run();
private:
	void onGateWayConnected(void* data);
	void onGateWayMessage(void* data);
private:
	EventLoop* pLoop;
	Connection* pGateWay;
	Buffer pBuffer;
};

#endif