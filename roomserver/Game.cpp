#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_HEAD_GAME gHead;
	gHead.id = head->id;
	gHead.pid = head->pid;
	gHead.type = head->type;
	gHead.rid = head->id;
	gHead.tid = nTid;
	gHead.cid = head->cid;
	gHead.iid = nIid;
	gHead.length = head->length;

	char buffer[64] = { 0 };
	int size = pack_game_msg(buffer, &gHead, body);
	pGame->send(buffer, size);
}

err_t Game::enterPlayer(Player* player)
{
	Player* old = findPlayer(player->pid());
	if (old)
	{
		removePlayer(player->pid());
		addPlayer(player->pid(), player);
	}
	else
	{
		addPlayer(player->pid(), player);
	}
	return 0;
}

err_t Game::leavePlayer(Player* player)
{

}
