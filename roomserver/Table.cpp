#include "Table.h"
#include "GamePool.h"
#include "Protocol.h"

Table::Table()
{
}


Table::Table(tid_t tid)
{
	nTid = tid;
	for (sid_t i = 1; i < 4;i++)
	{
		mSeats.insert(map_seat::value_type(i,new Seat(i)));
	}
}

Table::~Table()
{
	
}


void Table::startGame()
{
	pGame = GamePool::getInstance()->getGame();
	pGame->setMessageHandler(EV_M_CB(this, Table::handleGameMessage));
	if (!isAlive)
	{
		createGame();
	}
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

	unsigned short mtype = head->type & FILTER_TYPE_MSG;
	switch (mtype)
	{
	case MSG_TYPE_BROADCAST:
		if(CHANEL_TYPE_TABLE & head->type) broadcast(&hBack, body);
		else
		{
			Seat* seat = findSeat(head->sid);
			if (seat)
			{
				seat->handleGameMessage(conn, head, body);
			}
		}
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

err_t Table::enterPlayer(Player* player, sid_t seat)
{
	err_t err = 0;
	Seat* pSeat = findSeat(seat);
	if (!pSeat)
	{
		err = MSG_ERR_SEAT_NOT_EXIST_1006;
	}
	else
	{
		err = pSeat->enterPlayer(player);
	}
	if (!err)
	{
		Player* old = findPlayer(player->pid());
		if (old)
		{
			removePlayer(player->pid());
			player->setTableId(nTid);
			addPlayer(player->pid(), player);
		}
		else
		{
			player->setTableId(nTid);
			addPlayer(player->pid(), player);
		}
	}
	return err;
}

err_t Table::leavePlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		err = MSG_ERR_NOT_IN_TABLE_1007;
	}
	else
	{
		Seat* seat = findSeat(player->getSeatId());
		if (seat)
		{
			seat->leavePlayer(player);
		}
	}
	return err;
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

void Table::createGame()
{
	MSG_HEAD_GAME head;
	head.id = MSG_CREATE_GAME_105;
	head.type = MSG_TYPE_PLAYER;
	head.pid = 0;
	head.tid = nTid;
	head.rid = nRid;
	head.cid = nCid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	pGame->send(&head, &msg);
}

void Table::destoryGame()
{
	MSG_HEAD_GAME head;
	head.id = MSG_DESTROY_GAME_106;
	head.type = MSG_TYPE_PLAYER;
	head.pid = 0;
	head.tid = nTid;
	head.rid = nRid;
	head.cid = nCid;
	head.err = 0;

	MSG_REQ_CREATE_GAME msg;
	msg.gid = 2;

	pGame->send(&head, &msg);
}

Seat* Table::findSeat(sid_t sid)
{
	map_seat::iterator it = mSeats.find(sid);
	if (it != mSeats.end())
	{
		return it->second;
	}
	return NULL;
}
