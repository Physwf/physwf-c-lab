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
	pConnection->setMessageHandler(EV_M_CB(this,Client::onMessage));
	pConnection->connect("127.0.0.1",2345);

	pLoop->run();
}

void Client::onConnected(ClientConnection* con)
{
	Log::info("connected to gateway"); 
	login();
	enterRoom();
	return;
	joinTable();
	startGame();
}


void Client::onMessage(ClientConnection* con, MSG_HEAD_GATE* head, char* body)
{
	switch (head->id)
	{
	case MSG_ENTER_ROOM_1002:
		Log::info("enter room success");
		break;
	case MSG_LEAVE_ROOM_1003:
		Log::info("leave room success");
		break;
	case MSG_JOIN_TABLE_1004:
		Log::info("join table success");
		break;
	case MSG_LEAVE_TABLE_1005:
		Log::info("leave table success");
		break;
	case MSG_START_GAME_1006:
		Log::info("start game success");
		break;
	case MSG_END_GAME_1007:
		Log::info("end game success");
		break;
	default:
		break;
	}
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


void Client::enterRoom()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_ENTER_ROOM_1002;
	head.err = 0;

	MSG_REQ_ENTER_ROOM msg;
	msg.rid = 1;

	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}


void Client::leaveRoom()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_LEAVE_ROOM_1003;
	head.err = 0;

	MSG_REQ_LEAVE_ROOM msg;
	msg.rid = 1;

	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}


void Client::joinTable()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_JOIN_TABLE_1004;
	head.err = 0;

	MSG_REQ_JOIN_TABLE msg;
	msg.tid = 1;

	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}


void Client::leaveTable()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_LEAVE_TABLE_1005;
	head.err = 0;

	MSG_REQ_LEAVE_TABLE msg;
	msg.tid = 1;

	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}

void Client::startGame()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_START_GAME_1006;
	head.err = 0;

	MSG_REQ_START_GAME msg;
	msg.gid = 2;
	
	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}


void Client::leaveGame()
{
	char buffer[52] = { 0 };
	MSG_HEAD_GATE head;
	head.id = MSG_END_GAME_1007;
	head.err = 0;

	MSG_REQ_DESTROY_GAME msg;
	msg.gid = 2;

	int size = pack_gate_msg(buffer, &head, &msg);

	pConnection->send(buffer, size);
}

int main(int argc, char**argv)
{
	auto client = new Client();
	client->start();

}