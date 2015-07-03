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


void Table::checkGame()
{
	if (!isAlive && !mPlayers.empty())
	{
		pGame = GamePool::getInstance()->getGame();
		pGame->setMessageHandler(EV_M_CB(this, Table::onGameMessage));
		isAlive = true;
	}
	else if (isAlive && mPlayers.empty())
	{
		GamePool::getInstance()->recycle(pGame);
		isAlive = false;
	}
}


void Table::startGame()
{
	pGame->start();
}

void Table::handleRoomMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	switch (head->id)
	{
	case MSG_START_GAME_1006:
		startGame();
		break;
	case MSG_END_GAME_1007:
		
		break;
	case MSG_TAKE_SEAT_1014:
		onReqTakeSeat(conn, head, body);
		break;
	case MSG_STAND_UP_1016:
		onReqStandUp(conn, head, body);
		break;
	default:
		forwardToGame(head, body);
		break;
	}
}

err_t Table::enterPlayer(Player* player, sid_t seat)
{
	err_t err = 0;
	Seat* pSeat = findSeat(seat);
	if (!pSeat)
	{
		err = MSG_ERR_SEAT_NOT_EXIST_1007;
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
		checkGame();

		if (player->getStatus() == STATUS_SIT)
			pGame->initStatus(GAME_STATUS_SIT_DOWN, player->getSeatId());
	}
	return err;
}

err_t Table::leavePlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		err = MSG_ERR_NOT_IN_TABLE_1008;
	}
	else
	{
		Seat* seat = findSeat(player->getSeatId());
		if (seat)
		{
			seat->leavePlayer(player);
		}
		checkGame();
	}
	return err;
}


void Table::onGameMessage(GameConnection* conn, MSG_HEAD_GAME* head, char* body)
{
	switch (head->type & FILTER_TYPE_MSG)
	{
	case MSG_TYPE_BROADCAST:
	{
		if (CHANEL_TYPE_TABLE & head->type)
		{
			MSG_HEAD_BACK hBack = { 0 };
			hBack.id = head->id;
			hBack.type = head->type;
			hBack.id = head->id;
			hBack.length = head->length;
			broadcast(&hBack, body);
		}
		else
		{
			Seat* seat = findSeat(head->sid);
			if (seat)
			{
				seat->handleBroadcast(head, body);
			}
		}
		break;
	}
	case MSG_TYPE_PLAYER:
	{
		Seat* seat = findSeat(head->sid);
		if (seat)
		{
			seat->handlePlayerMessage(head, body);
		}
	}
		break;
	default:
		break;
	}
}

void Table::forwardToGame(MSG_HEAD_BACK* head, char* body)
{
	MSG_HEAD_GAME gHead;
	gHead.id = head->id;

	gHead.type = head->type;
	gHead.iid = pGame->iid();
	gHead.length = head->length;

	pGame->send(&gHead, body);
}


void Table::notiGameStart()
{
	MSG_HEAD_BACK head;
	head.id = MSG_NOTI_GAME_START_1012;
	head.pid = 0;
	head.rid = nRid;
	head.tid = nTid;

	MSG_NOTI_GAME_START msg;

	broadcast(&head, &msg);
}


void Table::notiGameEnd()
{
	MSG_HEAD_BACK head;
	head.id = MSG_NOTI_GAME_END_1013;
	head.pid = 0;
	head.rid = nRid;
	head.tid = nTid;

	MSG_NOTI_GAME_END msg;

	broadcast(&head, &msg);
}


void Table::onReqTakeSeat(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_TAKE_SEAT msg;
	msg.readBody(body, head->length);
	Seat* seat = findSeat(msg.sid);
	Player* player = findPlayer(head->pid);
	err_t err = tryTakeSeat(player, seat);
	if (err) takeSeatFailed(conn, player, err);
	else
	{
		takeSeatSuccess(conn, player, err);
		pGame->updateStatus(GAME_STATUS_SIT_DOWN, msg.sid);
		notiTakeSeat(conn, player);
	}
}


void Table::onReqStandUp(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Player* player = findPlayer(head->pid);
	err_t err = tryStandUp(player);
	if (err) standUpFailed(conn, player, err);
	else
	{
		standUpSuccess(conn, player, err);
		pGame->updateStatus(GAME_STATUS_STAND_UP, player->getSeatId());
		notiStandUp(conn, player);
	}
}


void Table::takeSeatFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_TAKE_SEAT_1014;
	head.type = MSG_TYPE_PLAYER;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.err = reason;
	
	char buffer[32] = { 0 };
	int size = write_head_back(buffer, &head);

	conn->send(buffer, size);
}


void Table::takeSeatSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_TAKE_SEAT_1014;
	head.type = MSG_TYPE_PLAYER;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.err = reason;

	MSG_RES_TAKE_SEAT msg;
	msg.sid = player->getSeatId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}


void Table::standUpFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_STAND_UP_1016;
	head.type = MSG_TYPE_PLAYER;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.err = reason;

	char buffer[32] = { 0 };
	int size = write_head_back(buffer, &head);

	conn->send(buffer, size);
}


void Table::standUpSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_STAND_UP_1016;
	head.type = MSG_TYPE_PLAYER;
	head.cid = nCid;
	head.pid = player->pid();
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.err = reason;

	MSG_RES_STAND_UP msg;
	msg.sid = player->getSeatId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}

err_t Table::tryTakeSeat(Player* player, Seat* seat)
{
	if (player->getStatus() == STATUS_SIT) return MSG_ERR_ALREADY_IN_SEAT_1013;

	if (!seat) return MSG_ERR_SEAT_NOT_EXIST_1007;
	else return seat->take(player);
}


err_t Table::tryStandUp(Player* player)
{
	err_t err = 0;
	if (!player) err = MSG_ERR_PLAYER_NOT_AT_TABLE_1011;
	if (player->getStatus() == STATUS_STAND) err = MSG_ERR_ALREADY_STAND_1014;
	if (player->getStatus() == STATUS_SIT)
	{
		Seat* seat = findSeat(player->getSeatId());
		if (!seat) return MSG_ERR_SEAT_NOT_EXIST_1007;
		err = seat->stand(player);
	}
	return err;
}


void Table::notiTakeSeat(ServiceConnection* conn, Player* player)
{
	MSG_HEAD_BACK head = { 0 };
	head.id = MSG_NOTI_TAKE_SEAT_1015;
	head.err = 0;
	
	MSG_NOTI_TAKE_SEAT msg;
	msg.pid = player->pid();
	msg.sid = player->getSeatId();

	broadcast(&head, &msg);
}


void Table::notiStandUp(ServiceConnection* conn, Player* player)
{
	MSG_HEAD_BACK head = { 0 };
	head.id = MSG_NOTI_STAND_UP_1017;
	head.err = 0;

	MSG_NOTI_STAND_UP msg;
	msg.pid = player->pid();
	msg.sid = player->getSeatId();

	broadcast(&head, &msg);
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
