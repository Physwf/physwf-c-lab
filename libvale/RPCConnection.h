#ifndef _RPC_CONNECTION_H
#define _RPC_CONNECTION_H

#include "Connection.h"
#include "Message.h"
#include <map>

class RPCConnection : public Object
{
public:
	RPCConnection();
	~RPCConnection();
public:
	void connect(const char* host, short port);
	void call(MID mid, char* data, size_t len);
	void run();
	void registerMsgHandler(MID mid,EventHandler handler);
private:
	void onConnected();
	void onClose();
	void onSocketData();
private:
	EventLoop* pLoop;
	Connection* pConnection;
	Buffer rBuffer;
	Buffer wBuffer;
	std::map<MID, EventHandler> mCallbacks;
};

#endif