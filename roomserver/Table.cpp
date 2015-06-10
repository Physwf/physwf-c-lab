#include "Table.h"
#include "GamePool.h"
#include "Protocol.h"

Table::Table()
{
}

Table::~Table()
{
	
}


void Table::startGame()
{
	pGame = GamePool::getInstance()->getGame();
	pGame->setMessageHandler(EV_CB(this, Table::handleGameMessage));
}


void Table::endGame()
{
	GamePool::getInstance()->recycle(pGame);
}

void Table::handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	switch (head->id)
	{
	case MSG_START_GAME_1006:
		startGame();
	case MSG_END_GAME_1007:
		endGame();
	default:
		doForward(head, body);
		break;
	}
}


void Table::handleGameMessage(GameConnection* conn, MSG_HEAD_GAME* head, char* body)
{
	MSG_HEAD_BACK hBack;
	hBack.id = head->id;
	hBack.type = head->type;
	hBack.pid = head->pid;
	hBack.rid = head->rid;
	hBack.tid = head->tid;
	hBack.id = head->id;
	hBack.length = head->length;

	switch (head->type)
	{
	case MSG_TYPE_BROADCAST:
		broadcast(&hBack, body);
		break;
	case MSG_TYPE_PLAYER:
	{
		Player* player = findPlayer(head->pid);
		if (player) player->send(&hBack, body);
		break;
	}
	default:
		break;
	}
	
}

err_t Table::enterPlayer(Player* player)
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

err_t Table::leavePlayer(Player* player)
{
	return 0;
}

void Table::doForward(MSG_HEAD_BACK* head, char* body)
{
	MSG_HEAD_GAME gHead;
	gHead.id = head->id;
	gHead.pid = head->pid;
	gHead.type = head->type;
	gHead.rid = head->id;
	gHead.tid = nTid;
	gHead.cid = head->cid;
	gHead.iid = pGame->iid();
	gHead.length = head->length;

	pGame->send(&gHead, body);
}
