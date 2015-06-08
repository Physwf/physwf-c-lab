#include "Chanel.h"

Chanel::Chanel(cid_t id) :nCid(id)
{

}

Chanel::~Chanel()
{

}

void Chanel::broadcast(MSG_HEAD_GATE* head, char* body)
{
	char buffer[32] = { 0 };
	int size = pack_gate_msg2(buffer, head, body);
	for (set_client::iterator it = mClients.begin(); it != mClients.end(); it++)
	{
		(**it).connection->send(buffer,size);
	}
}

void Chanel::addClient(Client* front)
{
	mClients.insert(set_client::value_type(front));
}

void Chanel::removeClient(Client* front)
{
	mClients.erase(front);
}
