#include "World.h"
#include "Master.h"
#include "Protocol.h"
#include "Message.h"

World::World(ServiceConnection* game) :Zone(game)
{

}

World::~World()
{

}

void World::initialize()
{
	tryCreate();
}


void World::addGateWay(ServiceConnection* conn)
{
	conn->setMessageHandler(EV_CB(this, World::onGatewayMessage));
}


void World::onGatewayMessage(ServiceConnection* conn, char* head, char* body)
{
	MSG_HEAD_BACK* pHead = (MSG_HEAD_BACK*)head;
	switch (pHead->id)
	{
	case MSG_CREATE_PLAYER_1000:
		onNewPlayer(conn, pHead, body);
		break;
	case MSG_DESTROY_PLAYER_1001:
		onDestroyPlayer(conn, pHead, body);
		break;
	case MSG_ENTER_ROOM_1002:
		onReqEnterRoom(conn, pHead, body);
		break;
	case MSG_LEAVE_ROOM_1003:
		onReqLeaveRoom(conn, pHead, body);
		break;
	case MSG_JOIN_GAME_1004:
		break;
	case MSG_LEAVE_GAME_1005:
		break;
	default:
		break;
	}
}

void World::onNewPlayer(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_CREATE_PLAYER* msg = (MSG_REQ_CREATE_PLAYER*)body;
	Player* player = new Player(msg->pid);
	addPlayer(player->pid(), player);
	player->setChanelId(nCid);

	enterZone(conn, player);
}

void World::onDestroyPlayer(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_DESTROY_PLAYER* msg = (MSG_REQ_DESTROY_PLAYER*)body;
	Player* player = removePlayer(msg->pid);

	leaveZone(conn, player);
}

void World::onReqEnterRoom(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_ENTER_ROOM* msg = (MSG_REQ_ENTER_ROOM*)body;
	Player* player = findPlayer(head->pid);
	Room* room = findRoom(msg->rid);
	err_t err = tryEnterRoom(room, player);
	if (err) enterRoomFailed(conn, player, err);
	else
	{
		enterRoomSuccess(conn, player, err);
		room->enterZone(conn, player);
	}
}

err_t World::tryEnterRoom(Room* room, Player* player)
{
	if (!room) return MSG_ERR_ROOM_NOT_EXIST_1000;
	else if (!room->avaliable()) return MSG_ERR_ROOM_FULL_1001;
	else return room->enterPlayer(player);
}


void World::enterRoomSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK sHead;
	sHead.id = MSG_ENTER_ROOM_1002;
	sHead.type = MSG_TYPE_PLAYER;
	sHead.cid = player->getChanelId();
	sHead.rid = player->getRoomId();
	sHead.tid = player->getTableId();
	sHead.err = reason;
	sHead.pid = player->pid();

	MSG_RES_ENTER_ROOM msg;
	msg.rid = player->getRoomId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &sHead, &msg);

	conn->send(buffer, size);
}


void World::enterRoomFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK sHead;
	sHead.id = MSG_ENTER_ROOM_1002;
	sHead.type = MSG_TYPE_PLAYER;
	sHead.cid = player->getChanelId();
	sHead.rid = player->getRoomId();
	sHead.tid = player->getTableId();
	sHead.err = reason;
	sHead.pid = player->pid();
	sHead.length = 0;

	char buffer[sizeof MSG_HEAD_BACK] = { 0 };
	int size = write_head_back(buffer, &sHead);

	conn->send(buffer, size);
}

void World::onReqLeaveRoom(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_LEAVE_ROOM* msg = (MSG_REQ_LEAVE_ROOM*)body;
	Player* player = findPlayer(head->pid);
	Room* room = findRoom(head->rid);
	err_t err = tryLeaveRoom(room, player);
	if (err) leaveRoomFailed(conn, player, err);
	else
	{
		leaveRoomSuccess(conn, player, err);
		room->leaveZone(conn, player);
	}
}

err_t World::tryLeaveRoom(Room* room, Player* player)
{
	if (!room) return MSG_ERR_ROOM_NOT_EXIST_1000;
	else return room->leavePlayer(player);
}


void World::leaveRoomSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
	player->setChanelId(nCid);

	MSG_HEAD_BACK head;
	head.id = MSG_LEAVE_ROOM_1003;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = nCid;
	
	MSG_RES_LEAVE_ROOM msg;
	msg.rid = player->getRoomId();

	char buffer[32] = { 0 };
	int size = pack_back_msg(buffer, &head, &msg);

	conn->send(buffer, size);
}


void World::leaveRoomFailed(ServiceConnection* conn, Player* player, err_t reason)
{
	MSG_HEAD_BACK head;
	head.id = MSG_LEAVE_ROOM_1003;
	head.type = MSG_TYPE_PLAYER;
	head.rid = player->getRoomId();
	head.tid = player->getTableId();
	head.cid = player->getChanelId();
	head.length = 0;

	char buffer[sizeof MSG_HEAD_BACK] = { 0 };
	int size = write_head_back(buffer, &head);
	conn->send(buffer, size);
}


void World::onReqJoinGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Room* room = findRoom(head->rid);
	Player* player = findPlayer(head->pid);
	err_t err = room->tryEnterGame(head->tid, player);
	if (err) enterGameFailed(conn,player,err);
	else enterGameSuccess(conn, player, err);
}


void World::enterGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
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


void World::enterGameFailed(ServiceConnection* conn, Player* player, err_t reason)
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




void World::onReqLeaveGame(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Room* room = findRoom(head->rid);
	Player* player = findPlayer(head->pid);
	err_t err = room->tryLeaveGame(head->tid, player);
	if (err) leaveGameFailed(conn, player, err);
	else leaveGameSuccess(conn, player, err);
}


void World::leaveGameSuccess(ServiceConnection* conn, Player* player, err_t reason)
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


void World::leaveGameFailed(ServiceConnection* conn, Player* player, err_t reason)
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

Room* World::findRoom(rid_t rid)
{
	map_room::iterator it = mRooms.find(rid);
	if (it != mRooms.end())
	{
		return it->second;
	}
	return NULL;
}

