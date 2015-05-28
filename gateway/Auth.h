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
	
	void setClientAuthResultHandler(EventHandler &cb) { cbClientAuthHandler = cb; }
	void setServiceAuthResultHandler(EventHandler &cb) { cbServiceAuthHandler = cb; }
private:
	ClientBuffer cBuffer;
	ServiceBuffer sBuffer;
	EventHandler cbClientAuthHandler;
	EventHandler cbServiceAuthHandler;
};
#endif