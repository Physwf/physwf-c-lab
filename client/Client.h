#ifndef _CLIENT_H
#define _CLIENT_H

#include "ClientConnection.h"

class Client : public Object
{
public:
	Client();
	~Client();
public:
	void start();
private:
	void onConnected(ClientConnection* con);
	void login();
private:
	EventLoop* pLoop;
	ClientConnection* pConnection;
};
#endif
