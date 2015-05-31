#ifndef _SYNC_MSG_CONNECTION_H
#define _SYNC_MSG_CONNECTION_H

#include "Connection.h"
#include <map>

template <typename mid, typename MSG_HEAD>
class SyncMsgConnection : public Connection
{
public:
	SyncMsgConnection(EventLoop* loop, int fd = INVALID_SOCKET);
	~SyncMsgConnection();
public:
	void send(char* head, size_t head_len, char* body, size_t body_len);
	void setMessageHandler(EventHandler &handler) { onMessage = handler; }
private:
	void onConnected();
	void onClose();
	void onSocketData();
private:
	EventHandler onMessage;
};

#endif