#include "Game.h"
#include "Protocol.h"

Game::Game()
{
	nIid = sIid++;
	memset(aStatus, 0, sizeof aStatus);
}

Game::~Game()
{

}

void Game::create(GameConnection* con)
{
	pCon = con;

	MSG_HEAD_GAME head;
	head.id = MSG_CREATE_GAME_105;
	head.type = MSG_TYPE_GAME;
	head.sid = 0;
	head.iid = nIid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	char buffer[32] = { 0 };
	int size = pack_game_msg(buffer, &head, &msg);
	pCon->send(buffer,size);
}

void Game::destory()
{
	bIdle = true;

	MSG_HEAD_GAME head;
	head.id = MSG_DESTROY_GAME_106;
	head.type = MSG_TYPE_GAME;
	head.iid = nIid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	char buffer[32] = { 0 };
	int size = pack_game_msg(buffer, &head, &msg);

	pCon->send(buffer, size);
}


void Game::start()
{
	MSG_HEAD_GAME head;
	head.id = MSG_START_GAME_1006;
	head.iid = nIid;
	head.sid = 0;
	head.type = MSG_TYPE_GAME;
	head.err = 0;
	head.length = sizeof(aStatus);

	send(&head, aStatus);

	bIdle = false;
}

void Game::send(MSG_HEAD_GAME* pHead, char* body)
{
	char buffer[32] = { 0 };
	int size = pack_game_msg2(buffer, pHead, body);
	pCon->send(buffer,size);
}


void Game::send(MSG_HEAD_GAME* pHead, Message* msg)
{
	char buffer[52] = { 0 };
	int size = pack_game_msg(buffer, pHead, msg);
	pCon->send(buffer, size);
}


void Game::handleMessage(GameConnection* con, MSG_HEAD_GAME* head, char* body)
{
	unsigned short mtype = head->type & FILTER_TYPE_MSG;
	switch (mtype)
	{
	case MSG_TYPE_GAME:
		handleInternal(head, body);
		break;
	default:
		EV_INVOKE(cbMessageHandler,con, head, body);
		break;
	}
}


void Game::initStatus(unsigned char status, unsigned int value)
{
	aStatus[value] = status == GAME_STATUS_SIT_DOWN ? 1 : 0;
}

void Game::updateStatus(unsigned char status, unsigned int value)
{
	if (!bIdle)
	{
		MSG_HEAD_GAME head;
		head.id = MSG_GAME_STATUS_107;
		head.iid = nIid;
		head.type = MSG_TYPE_GAME;

		MSG_GAME_STATUS msg;
		msg.status_type = status;
		msg.value = value;

		send(&head, &msg);
	}
}

void Game::handleInternal(MSG_HEAD_GAME* head, char* body)
{
	switch (head->id)
	{
	case MSG_CREATE_GAME_105:
		nIid = head->iid;
		break;
	case MSG_DESTROY_GAME_106:
		break;
	default:
		break;
	}
}

iid_t Game::sIid = 1;

