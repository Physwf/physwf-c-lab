#ifndef _AUTH_H
#define _AUTH_H

#include "Message.h"
#include "Session.h"

struct Client
{
	ClientConnection* connection;
	Session* session;
};

struct Service
{
	ServiceConnection* connection;
	char type;
};

class Auth : public Object
{
public:
	Auth(ServiceConnection* service):pAuthService(service) {}
	~Auth();
public:
	void addClientForAuth(ClientConnection* client);
	void addServiceForAuth(ServiceConnection* service);
	void removeClient(ClientConnection* client);
	void removeService(ServiceConnection* service);
	
	void setClientAuthResultHandler(EventHandler &cb) { cbClientAuthHandler = cb; }
	void setServiceAuthResultHandler(EventHandler &cb) { cbServiceAuthHandler = cb; }
private:
	void doClientAuth(ClientConnection* conn, char* head, char*body);
private:
	ServiceConnection* pAuthService;

	ClientBuffer cBuffer;
	ServiceBuffer sBuffer;
	EventHandler cbClientAuthHandler;
	EventHandler cbServiceAuthHandler;
	
};
#endif