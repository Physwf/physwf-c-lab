#include "Auth.h"
#include "Protocol.h"
#include "Log.h"

Auth::Auth()
{

}

Auth::~Auth()
{

}

void Auth::addClientForAuth(ClientConnection* client)
{
	client->setMessageHandler(EV_M_CB(this, Auth::doClientAuth));
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

void Auth::doClientAuth(ClientConnection* conn,char* head, char*body)
{
	Log::info("Client Auth Message");
	Client* client = new Client();
	client->connection = conn;
	client->session = new Session();
	EV_INVOKE(cbClientAuthHandler, client, true);
}
