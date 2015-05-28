#include "Auth.h"

Auth::Auth()
{

}

Auth::~Auth()
{

}

void Auth::addClientForAuth(ClientConnection* client)
{
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
