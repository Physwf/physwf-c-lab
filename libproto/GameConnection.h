#ifndef _GAME_CONNECTION_H
#define _GAME_CONNECTION_H

#include "Message.h"
#include "Connection.h"

class VALE_DLL GameConnection : public Object
{
public:
	GameConnection(EventLoop* loop, int fd = INVALID_SOCKET);
	~GameConnection();
	static GameConnection* create(EventLoop* loop);
	static GameConnection* create(EventLoop* loop, int fd);
	static void destory(GameConnection* con);
private:
	GameConnection(Connection* con);
	void init();
	void onConnected(Connection* con);
	void onRead(Connection* con);
	void onClosed(Connection* con);
public:
	void connect(const char* host, short port);
	void send(char* head, size_t head_len, char* body, size_t body_len);
	void send(char* data, size_t size);
	void setMessageHandler(const MessageHandler &cb);
	void setCloseHandler(const EventHandler &cb);
	void setConnectHandler(const EventHandler &cb);
protected:

private:
	Connection* pConnection;
	Buffer bufRead;
	MessageHandler cbMessageHandler;
	EventHandler cbCloseHandler;
	EventHandler cbConnectHandler;
};
#endif