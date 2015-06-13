#include "Game.h"

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
}

void Game::end()
{
	bIdle = true;
}

void Game::send(MSG_HEAD_GAME* pHead, char* body)
{
	char buffer[32] = { 0 };
	int size = pack_game_msg2(buffer, pHead, body);
	pCon->send(buffer,size);
}

void Game::handleMessage(GameConnection* con,MSG_HEAD_GAME* pHead, char* body)
{
	EV_INVOKE(cbMessageHandler,con,pHead,body);
}

iid_t Game::sIid=0;

