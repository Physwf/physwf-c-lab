#include "Auth.h"
#include "Protocol.h"
#include "Log.h"

Auth::Auth()
{
	cheat_pid = 0;
}

Auth::~Auth()
{

}

void Auth::addClientForAuth(ClientConnection* client)
{
	client->setMessageHandler(EV_M_CB(this, Auth::doClientAuth));
	cBuffer.insert(client);
}

void Auth::addServiceForAuth(ServiceConnection* service)
{
	EV_INVOKE(cbServiceAuthHandler, service, true);
}

bool Auth::removeClient(ClientConnection* client)
{
	return cBuffer.erase(client) > 0;
}

void Auth::removeService(ServiceConnection* service)
{

}

void Auth::doClientAuth(ClientConnection* conn,MSG_HEAD_GATE* head, char*body)
{
	switch (head->id)
	{
	case MSG_LOGIN_0001:
	{
		Log::info("Client Auth Message");
		Client* client = new Client();
		client->connection = conn;
		client->session = new Session();
		client->pid = ++cheat_pid;
		removeClient(conn);
		authSuccess(client);
		EV_INVOKE(cbClientAuthHandler, client, true);
		break;
	}
	default:
		Log::info("Wrong Auth Message");
		break;
	}
	
}

void Auth::authSuccess(Client* client)
{
	MSG_HEAD_GATE head;
	head.id = MSG_LOGIN_0001;
	head.err = 0;

	MSG_RES_LOGIN body;
	body.pid = client->pid;

	char buffer[32] = { 0 };
	int size = pack_gate_msg(buffer, &head, &body);
	client->connection->send(buffer, size);
}

void Auth::authFailed(Client* client)
{
	MSG_HEAD_GATE head;
	head.id = MSG_LOGIN_0001;
	head.err = MSG_ERR_AUTH_FAILED_0001;

	MSG_RES_LOGIN body;
	body.pid = client->pid;

	char buffer[32] = { 0 };
	int size = pack_gate_msg(buffer, &head, &body);
	client->connection->send(buffer, size);
}
