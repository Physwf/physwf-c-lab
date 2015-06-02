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
	void connectMaster();
	void connectAuth();
private:
	void onClientConnect(int fd, int event,void* data);
	void onClientClose(ClientConnection* con);
	void onMasterConnect(ServiceConnection* con);

	void onBackConnect(int fd, int event, void* data);
	void onBackClose(ServiceConnection* con);
	void onAuthConnected(ServiceConnection* con);

	void onClientAuthResult(Client* client, bool success);
	void onServiceAuthResult(ServiceConnection* service, bool success);

private:
	EventLoop* pLoop;
	Server* pFront;
	Server* pBack;

	ServiceConnection* pMaster;

	Auth* pAuth;
	Router* pRouter;

	int nMode;
	
};

#endif