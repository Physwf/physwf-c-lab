#ifndef _GATE_H
#define _GATE_H

#define MODE_NEGATIVE 2
#define MODE_POSITIVE 4

#include "Server.h"
#include "Auth.h"
#include "Router.h"
#include "Chanel.h"

#include <set>

class Gate : public Object
{
public:
	Gate();
	~Gate();
public:
	void start();
	void setMode(int mode) { nMode &= mode; }
private:
	void onFrontConnect(int fd, int event,void* data);
	void onFrontClose(ClientConnection* con);
	void onBackConnect(int fd, int event, void* data);
	void onBackClose(ServiceConnection* con);
	void onClientAuthResult(ClientConnection* client, bool success);
	void onServiceAuthResult(ServiceConnection* service, bool success);

private:
	EventLoop* pLoop;
	Server* pFront;
	Server* pBack;
	ServiceConnection* pRoomService;
	ServiceConnection* pAuthService;

	Auth* pAuth;
	Router* pRouter;

	int nMode;
};

#endif