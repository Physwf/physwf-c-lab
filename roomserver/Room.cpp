#include "Protocol.h"
#include "Room.h"

Room::Room()
{
	
}

Room::~Room()
{

}

err_t Room::enterPlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		addPlayer(player->pid(),player);
	}
	else if (old == player)
	{
		err = MSG_ERR_ALREADY_IN_1002;
	}
	else//log in different places. to do
	{
		addPlayer(player->pid(), player);
		old;//to do something;
	}
	if (!err)
	{
		player->setChanelId(nCid);
	}
	return err;
}

err_t Room::leavePlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		err = MSG_ERR_NOT_IN_ROOM_1003;
	}
	else if (old != player)
	{
		//??
	}
	else
	{
	}
	return err;
}


void Room::handleWorldMessage(ServiceConnection* conn, MSG_HEAD_BACK* pHead, char* body)
{
	switch (pHead->id)
	{
	case MSG_JOIN_GAME_1004:
		onReqJoinGame(conn, pHead, body);
		break;
	case MSG_LEAVE_GAME_1005:
		onReqLeaveGame(conn, pHead, body);
		break;
	default:
		//doReqRoute(conn, pHead, body);
		break;
	}
}

void Room::onReqJoinGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Player* player = findPlayer(head->pid);
	err_t err = tryEnterTable(head->tid, player);
	if (err) enterGameFailed(conn, player, err);
	else enterGameSuccess(conn, player, err);
}


void Room::enterGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_GAME_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();

	MSG_RES_JOIN_GAME msg;
	msg.gid = player->getTableId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}

void Room::enterGameFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_GAME_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.length = 0;

	char buffer[sizeof MSG_HEAD_BACK] = { 0 };
	int size = write_head_back(buffer, &head);
	conn->send(buffer, size);
}

void Room::onReqLeaveGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Player* player = findPlayer(head->pid);
	err_t err = tryLeaveTable(head->tid, player);
	if (err) leaveGameFailed(conn, player, err);
	else leaveGameSuccess(conn, player, err);
}

void Room::leaveGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_GAME_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();

	MSG_RES_LEAVE_GAME msg;
	msg.gid = player->getTableId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}

void Room::leaveGameFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_LEAVE_GAME_1005;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.length = 0;

	char buffer[sizeof MSG_HEAD_BACK] = { 0 };
	int size = write_head_back(buffer, &head);
	conn->send(buffer, size);
}

err_t Room::tryEnterTable(tid_t tid, Player* player)
{
	Table* game = table(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->enterPlayer(player);
}

err_t Room::tryLeaveTable(tid_t tid, Player* player)
{
	Table* game = table(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->leavePlayer(player);
}

void Room::doForward(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Table* game = table(head->tid);
	if (game)
	{
		game->handleRoomMessage(conn, head, body);
	}
}

Table* Room::table(tid_t gid)
{
	map_table::iterator it = mTables.find(gid);
	if (it != mTables.end())
	{
		return it->second;
	}
	return NULL;
}

int Room::capacity()
{

}

int Room::avaliable()
{

}
