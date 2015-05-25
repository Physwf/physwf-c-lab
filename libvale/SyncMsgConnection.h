#ifndef _SYNC_MSG_CONNECTION_H
#define _SYNC_MSG_CONNECTION_H

#include "Connection.h"
#include "Message.h"
#include <map>

class SyncMsgConnection : public Object
{
public:
	SyncMsgConnection(EventLoop* loop);
	~SyncMsgConnection();
public:
	void connect(const char* host, short port);
	void send(mid_t mid, char* data, size_t len);
	void registerMsgHandler(mid_t mid, EventHandler handler);
private:
	void onConnected();
	void onClose();
	void onSocketData();
private:
	EventLoop* pLoop;
	Connection* pConnection;
	Buffer rBuffer;
	Buffer wBuffer;
	std::map<mid_t, EventHandler> mCallbacks;
};

#endif