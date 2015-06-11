#pragma once
/*
#ifndef _SYNC_MSG_CONNECTION_H
#define _SYNC_MSG_CONNECTION_H

#include "Connection.h"

#include "platform.h"

template <typename TMID, typename TMSG_HEAD>
class SyncMsgConnection : public Object
{
public:
	SyncMsgConnection(EventLoop* loop, int fd = INVALID_SOCKET)
	{
		pConnection = new Connection(loop, fd);
		init();
	}
	SyncMsgConnection(Connection* conn) :pConnection(conn)
	{
		init();
	}
	~SyncMsgConnection()
	{

	}
public:
	static SyncMsgConnection* create(EventLoop* loop)
	{
		Connection* conn = new Connection(loop);
		conn->createTcp(loop);
		return new SyncMsgConnection(conn);
	}
	void connect(const char* host, short port) { pConnection->connect(host, port); }
	void send(char* head, size_t head_len, char* body, size_t body_len)
	{

	}
	void send(char* data, size_t size)
	{

	}
	void setTest(int *t) { test = t; }
	void setCloseHandler(const EventHandler &cb) { pConnection->setCloseHandler(cb); }
	void setConnectHandler(const EventHandler &cb) { pConnection->setConnectHandler(cb); }
	void setMessageHandler(EventHandler &handler) { onMessage = handler; }
private:
	void init()
	{
		pConnection->setConnectHandler(EV_CB(this, SyncMsgConnection::onConnected));
		pConnection->setReadHandler(EV_CB(this, SyncMsgConnection::onSocketData));
	}
	void onConnected(Connection* con)
	{
		EV_INVOKE( cbConnectHandler, this);
	}
	void onClose()
	{

	}
	void onSocketData(SyncMsgConnection* conn)
	{

	}
private:
	EventHandler onMessage;
	Connection* pConnection;
	EventHandler cbConnectHandler;
	EventHandler cbReadHandler;
	EventHandler cbCloseHandler;
	int *test;
	
	EventHandler cbWriteCompleteHandler;
};


#endif
*/