#ifndef _SERVICE_CONNECTION_H
#define _SERVICE_CONNECTION_H

#include "Message.h"
#include "Connection.h"

class VALE_DLL ServiceConnection : public Object
{
public:
	ServiceConnection(EventLoop* loop, int fd = INVALID_SOCKET);
	~ServiceConnection();
	static ServiceConnection* create(EventLoop* loop);
	static ServiceConnection* create(EventLoop* loop, int fd);
	static void destroy(ServiceConnection* con);
private:
	ServiceConnection(Connection* con);
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
	void setTest(int i);
protected:

private:
	Connection* pConnection;
	Buffer bufRead;
	MessageHandler cbMessageHandler;
	EventHandler cbCloseHandler;
	EventHandler cbConnectHandler;
	int nTest;

};
#endif