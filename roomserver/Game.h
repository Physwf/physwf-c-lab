#ifndef _GAME_H
#define _GAME_H

#include "Message.h"

class Game : public Object
{
public:
	Game();
	~Game();
public:
	void start(GameConnection* con);
	void end();
	void send(MSG_HEAD_GAME* pHead, char* body);
	void setMessageHandler(EventHandler& cb) { cbMessageHandler = cb; };
	void handleMessage(GameConnection* con,MSG_HEAD_GAME* pHead, char* body);
	iid_t iid() { return nIid; }
	bool isIdle() { return bIdle; }
private:
	EventHandler cbMessageHandler;
private:
	GameConnection* pCon;
	iid_t nIid;
	static iid_t sIid;
	bool bIdle;
};
#endif