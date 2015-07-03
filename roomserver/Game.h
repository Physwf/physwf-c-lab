#ifndef _GAME_H
#define _GAME_H

#include "Message.h"
#include "GameConnection.h"

class Game : public Object
{
public:
	Game();
	~Game();
public:
	void create(GameConnection* con);
	void destory();
	void start();
	void send(MSG_HEAD_GAME* pHead, char* body);
	void send(MSG_HEAD_GAME* pHead, Message* msg);
	void setMessageHandler(MessageHandler& cb) { cbMessageHandler = cb; };
	void handleMessage(GameConnection* con,MSG_HEAD_GAME* pHead, char* body);
	iid_t iid() { return nIid; }
	bool isIdle() { return bIdle; }
	void initStatus(unsigned char status, unsigned int value);
	void updateStatus(unsigned char status, unsigned int value);
private:
	void forwardToGate(MSG_HEAD_GAME* head, char* body);
	void handleInternal(MSG_HEAD_GAME* head, char* body);
private:
	GameConnection* pCon;
	MessageHandler cbMessageHandler;
	iid_t nIid;
	static iid_t sIid;
	bool bIdle;
	char aStatus[3];
};
#endif