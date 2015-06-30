#include "Protocol.h"
#include "Room.h"
#include "Log.h"

Room::Room()
{
	
}


Room::Room(rid_t id)
{
	nRid = id;
	mTables.insert(map_table::value_type(1,new Table(1)));
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
		player->setRoomId(nRid);
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
	else
	{
		Table* table = findTable(player->getTableId());
		if (table)
		{
			table->leavePlayer(player);
		}
	}
	return err;
}


void Room::handleWorldMessage(ServiceConnection* conn, MSG_HEAD_BACK* pHead, char* body)
{
	switch (pHead->id)
	{
	case MSG_JOIN_TABLE_1004:
		onReqJoinTable(conn, pHead, body);
		break;
	case MSG_LEAVE_TABLE_1005:
		onReqLeaveTable(conn, pHead, body);
		break;
	default:
		doForward(conn, pHead, body);
		break;
	}
}

void Room::onReqJoinTable(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_JOIN_TABLE msg;
	msg.readBody(body,head->length);
	Player* player = findPlayer(head->pid);
	err_t err = tryEnterTable(msg.tid, player,msg.seat);
	if (err) enterGameFailed(conn, player, err);
	else
	{
		enterGameSuccess(conn, player, err);
		notifyEnterTable(conn, player);
	}
}


void Room::enterGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	Log::info("player join table success,pid:%d", player->pid());
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_TABLE_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.pid = player->pid();
	head.err = reason;

	MSG_RES_JOIN_TABLE msg;
	msg.tid = player->getTableId();
	msg.seat = player->getSeatId();
	msg.state = player->getStatus();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}

void Room::enterGameFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	Log::info("player join table failed,pid:%d", player->pid());
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_TABLE_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.pid = player->pid();
	head.length = 0;

	char buffer[sizeof MSG_HEAD_BACK] = { 0 };
	int size = write_head_back(buffer, &head);
	conn->send(buffer, size);
}

void Room::onReqLeaveTable(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Player* player = findPlayer(head->pid);
	err_t err = tryLeaveTable(head->tid, player);
	if (err) leaveGameFailed(conn, player, err);
	else
	{
		leaveGameSuccess(conn, player, err);
		notifyLeaveTable(conn, player);
	}
}

void Room::leaveGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_JOIN_TABLE_1004;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();

	MSG_RES_LEAVE_TABLE msg;
	msg.tid = player->getTableId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}

void Room::leaveGameFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_LEAVE_TABLE_1005;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.length = 0;

	char buffer[32] = { 0 };
	int size = write_head_back(buffer, &head);
	conn->send(buffer, size);
}


void Room::notifyEnterTable(ServiceConnection* conn, Player* player)
{
	MSG_HEAD_BACK head;
	head.id = MSG_NOTI_JOIN_TABLE_1010;
	head.type = MSG_TYPE_BROADCAST;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.pid = player->pid();

	MSG_NOTI_JOIN_TABLE msg;
	msg.pid = player->pid();
	msg.sid = player->getSeatId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);
	conn->send(buffer, size);
}


void Room::notifyLeaveTable(ServiceConnection* conn, Player* player)
{
	MSG_HEAD_BACK head;
	head.id = MSG_NOTI_LEAVE_TABLE_1011;
	head.type = MSG_TYPE_BROADCAST;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.pid = player->pid();

	MSG_NOTI_LEAVE_TABLE msg;
	msg.pid = player->pid();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);
	conn->send(buffer, size);
}

err_t Room::tryEnterTable(tid_t tid, Player* player, unsigned char seat)
{
	Table* game = findTable(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->enterPlayer(player,seat);
}

err_t Room::tryLeaveTable(tid_t tid, Player* player)
{
	Table* game = findTable(tid);
	if (game == NULL)
	{
		return MSG_ERR_TABLE_FULL_1004;
	}
	return game->leavePlayer(player);
}

void Room::doForward(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Table* game = findTable(head->tid);
	if (game)
	{
		game->handleRoomMessage(conn, head, body);
	}
}

Table* Room::findTable(tid_t gid)
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
	return 10;
}

int Room::avaliable()
{
	return 1;
}
