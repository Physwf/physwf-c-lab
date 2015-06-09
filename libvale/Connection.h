#pragma once
#ifndef _CONNECTION_H
#define _CONNECTION_H

#include "EventLoop.h"
#include "Socket.h"
#include "Buffer.h"

#include "platform.h"

class VALE_DLL Connection : public Object
{
public:
	Connection(EventLoop* loop, int fd = INVALID_SOCKET);
	~Connection();
public:
	int connect(const char* host, short port);
	int send(const char* data, size_t size);
	int send(Buffer& buf);
	void close();
	Socket& getSocket() { return sSocket; }
	Buffer* const getBuffer() { return &bufRead; }
	void setReadHandler(const EventHandler &cb) { cbReadHandler = cb; }
	void setCloseHandler(const EventHandler &cb) { cbCloseHandler = cb; }
	void setConnectHandler(const EventHandler &cb) { cbConnectHandler = cb; }
	void setWriteCompleteHandler(const EventHandler &cb) { cbWriteCompleteHandler = cb; }
private:
	void onConnect(int fd, int event, void* data);
	void onRead(int fd, int event, void* data);
	void onWrite(int fd, int event, void* data);
	void onClose();
protected:
	EventLoop* pLoop;
	Socket sSocket;
	Buffer bufWrite;
	Buffer bufRead;
	bool bWriting;
	EventHandler cbReadHandler;
	EventHandler cbCloseHandler;
	EventHandler cbConnectHandler;
	EventHandler cbWriteCompleteHandler;
};
#endif
