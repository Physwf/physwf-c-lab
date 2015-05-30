#include "Auth.h"
#include "Protocol.h"

Auth::~Auth()
{

}

void Auth::addClientForAuth(ClientConnection* client)
{
	client->registerMsgHandler(MSG_REQ_LOGIN_0001, EV_CB(this, Auth::doClientAuth));
	EV_INVOKE(cbClientAuthHandler,client,true);
}

void Auth::addServiceForAuth(ServiceConnection* service)
{
	EV_INVOKE(cbServiceAuthHandler, service, true);
}

void Auth::removeClient(ClientConnection* client)
{

}

void Auth::removeService(ServiceConnection* service)
{

}

void Auth::doClientAuth(char* head, char*body)
{
	
}
