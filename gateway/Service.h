#ifndef _SERVICE_H
#define _SERVER_H

#include "Connection.h"

class Service
{
public:
	Service();
	~Service();
public:
	void launch();
	void call();
	void close();
private:
	Connection* pConnection;
};
#endif