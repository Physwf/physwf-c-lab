#ifndef _AUTH_H
#define _AUTH_H

#include "Message.h"

class Auth
{
public:
	Auth();
	~Auth();
public:
	void addClientForAuth(ClientConnection* client);
	void addServiceForAuth(ServiceConnection* service);
	void removeClient(ClientConnection* client);
	void removeService(ServiceConnection* service);
	
	void setClientAuthResultHandler(ClientConnection* client,bool success);
	void setServiceAuthResultHandler(ServiceConnection* client, bool success);
private:
	ClientBuffer cBuffer;
	ServiceBuffer sBuffer;
};
#endif