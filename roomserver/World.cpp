#include "World.h"
#include "Master.h"
#include "Protocol.h"
#include "Message.h"
#include "Log.h"

World::World()
{

}

World::~World()
{

}

void World::initialize()
{
	mRooms.insert(map_room::value_type(1, new Room(1)));
}


void World::addGateWay(ServiceConnection* conn)
{
	conn->setMessageHandler(EV_M_CB(this, World::onGatewayMessage));
	conn->setCloseHandler(EV_CB(this,World::onGatewayClose));
}


void World::onGatewayMessage(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	switch (head->id)
	{
	case MSG_CREATE_PLAYER_100:
		onNewPlayer(conn, head, body);
		break;
	case MSG_DESTROY_PLAYER_101:
		onDestroyPlayer(conn, head, body);
		break;
	case MSG_ENTER_ROOM_1002:
		onReqEnterRoom(conn, head, body);
		break;
	case MSG_LEAVE_ROOM_1003:
		onReqLeaveRoom(conn, head, body);
		break;
	default:
		doForword(conn, head, body);
		break;
	}
}


void World::onGatewayClose(ServiceConnection* con)
{
	Log::info("Gateway closed!");
}

void World::onNewPlayer(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_CREATE_PLAYER msg;
	msg.readBody(body,head->length);
	Player* player = findPlayer(msg.pid);
	if (!player)
	{
		player = new Player(msg.pid);
		Log::debug("new player enter world,pid:%d", msg.pid);
		addPlayer(player->pid(), player);

		enterZone(conn, player);
	}
	player->init();
	player->setChanelId(nCid);
	player->setGate(conn);
}

void World::onDestroyPlayer(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_DESTROY_PLAYER msg;
	msg.readBody(body, head->length);
	
	Player* player = removePlayer(msg.pid);
	if (player)
	{
		Log::debug("player left world,pid:%d", msg.pid);
		leaveZone(conn, player);

		Room* room = findRoom(head->rid);
		if (room)
		{
			room->leavePlayer(player);
		}
	}
}

void World::onReqEnterRoom(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_ENTER_ROOM msg;
	msg.readBody(body,head->length);
	Player* player = findPlayer(head->pid);
	Room* room = findRoom(msg.rid);
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

void World::doForword(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	Room* room = findRoom(head->rid);
	if (room)
	{
		room->handleWorldMessage(conn, head, body);
	}
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

