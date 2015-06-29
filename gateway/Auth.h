#ifndef _AUTH_H
#define _AUTH_H

#include "Message.h"
#include "Session.h"
#include "ClientConnection.h"
#include "ServiceConnection.h"

typedef void(Object::*AuthCallBack)(void*,bool);
typedef struct
{
	Object* object;
	AuthCallBack method;
} AuthHandler;

#define EV_AH_CB(_obj,_func) AuthHandler {_obj,(AuthCallBack)&_func}
struct Client
{
	ClientConnection* connection;
	ServiceConnection* master;
	Session* session;
	rid_t rid;
	tid_t tid;
	pid_t pid;
};

struct Service
{
	ServiceConnection* connection;
	char type;
};

#include <set>

typedef std::set<ClientConnection*> ClientBuffer;
typedef std::set<ServiceConnection*> ServiceBuffer;

class Auth : public Object
{
public:
	Auth();
	~Auth();
public:
	void addClientForAuth(ClientConnection* client);
	void addServiceForAuth(ServiceConnection* service);
	bool removeClient(ClientConnection* client);
	void removeService(ServiceConnection* service);
	
	void setClientAuthResultHandler(AuthHandler &cb) { cbClientAuthHandler = cb; }
	void setServiceAuthResultHandler(AuthHandler &cb) { cbServiceAuthHandler = cb; }
private:
	void doClientAuth(ClientConnection* conn, MSG_HEAD_GATE* head, char*body);
	void authSuccess(Client* conn);
	void authFailed(Client* conn);
private:
	int cheat_pid;
	ClientBuffer cBuffer;
	ServiceBuffer sBuffer;
	AuthHandler cbClientAuthHandler;
	AuthHandler cbServiceAuthHandler;
	
};
#endif