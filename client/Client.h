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
	void onMessage(ClientConnection* con,MSG_HEAD_GATE* head,char* body);
	void login();
	void enterRoom();
	void leaveRoom();
	void joinTable();
	void leaveTable();
	void startGame();
	void leaveGame();
private:
	EventLoop* pLoop;
	ClientConnection* pConnection;
};
#endif
