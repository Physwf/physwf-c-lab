#ifndef _SYNC_MSG_CONNECTION_H
#define _SYNC_MSG_CONNECTION_H

#include "Connection.h"

#include "platform.h"

template <typename TMID, typename TMSG_HEAD>
class VALE_DLL SyncMsgConnection : public Connection
{
public:
	SyncMsgConnection(EventLoop* loop, int fd = INVALID_SOCKET) :Connection(loop, fd)
	{
		//Connection::setReadHandler(EV_CB(this, SyncMsgConnection::onSocketData));
	}
	~SyncMsgConnection()
	{

	}
public:
	void send(char* head, size_t head_len, char* body, size_t body_len)
	{

	}
	void send(char* data, size_t size)
	{

	}
	void setMessageHandler(EventHandler &handler) { onMessage = handler; }
private:
	void onConnected()
	{

	}
	void onClose()
	{

	}
	void onSocketData(SyncMsgConnection* conn)
	{

	}
private:
	EventHandler onMessage;
};

#endif