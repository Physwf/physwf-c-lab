#ifndef _SERVICE_H
#define _SERVICE_H

#include "Connection.h"

class Service
{
public:
	Service();
	~Service();
public:
	void connect();
	void call();
	void disconnect();
private:
    void onConnected();
    void onCallResponse();
    void onBroadcast();
private:
	Connection* pConnection;
};
#endif