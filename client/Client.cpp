#include "Client.h"
#include "Log.h"
#include "Protocol.h"

Client::Client()
{

}

Client::~Client()
{

}

void Client::start()
{
	pLoop = new EventLoop();

	pConnection = ClientConnection::create(pLoop);
	pConnection->setConnectHandler(EV_CB(this,Client::onConnected));
	pConnection->connect("127.0.0.1",2345);

	pLoop->run();
}

void Client::onConnected(ClientConnection* con)
{
	Log::info("connected to gateway"); 
	login();
}

void Client::login()
{
	char buffer[128] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_REQ_LOGIN_0001;
	head.err = 0;
	
	MSG_REQ_LOGIN body;
	body.accout = "physwf";
	body.accout_length = strlen(body.accout);
	size_t size = pack_gate_msg(buffer, &head, &body);
	
	pConnection->send(buffer, size);
}

int main(int argc, char**argv)
{
	auto client = new Client();
	client->start();

}