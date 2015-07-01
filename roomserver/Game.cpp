#include "Game.h"
#include "Protocol.h"

Game::Game()
{
	nIid = sIid++;
}

Game::~Game()
{

}

void Game::start(GameConnection* con)
{
	pCon = con;
	bIdle = false;

	MSG_HEAD_GAME head;
	head.id = MSG_CREATE_GAME_105;
	head.type = MSG_TYPE_GAME;
	head.pid = 0;
	head.tid = 0;
	head.sid = 0;
	head.rid = 0;
	head.cid = 0;
	head.iid = nIid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	char buffer[32] = { 0 };
	int size = pack_game_msg(buffer, &head, &msg);
	pCon->send(buffer,size);
}

void Game::end()
{
	bIdle = true;

	MSG_HEAD_GAME head;
	head.id = MSG_DESTROY_GAME_106;
	head.type = MSG_TYPE_GAME;
	head.pid = 0;
	head.tid = 0;
	head.rid = 0;
	head.cid = 0;
	head.iid = nIid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	char buffer[32] = { 0 };
	int size = pack_game_msg(buffer, &head, &msg);

	pCon->send(buffer, size);
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

iid_t Game::sIid = 0;

