#include "World.h"
#include "Master.h"
#include "Protocol.h"
#include "Message.h"

World::World(ServiceConnection* game) :Zone(game), nCid(0)
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
}

void World::onDestroyPlayer(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_DESTROY_PLAYER* msg = (MSG_REQ_DESTROY_PLAYER*)body;
	Player* player = removePlayer(msg->pid);
}

void World::onReqEnterRoom(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_ENTER_ROOM* msg = (MSG_REQ_ENTER_ROOM*)body;
	Player* player = findPlayer(head->pid);
	Room* room = findRoom(msg->rid);
	err_t err = tryEnterRoom(room, player);
	if (err) enterRoomFailed(conn, player, err);
	else enterRoomSuccess(conn, player, err);
}

err_t World::tryEnterRoom(Room* room, Player* player)
{
	if (!room) return MSG_ERR_ROOM_NOT_EXIST_1000;
	else if (!room->avaliable()) return MSG_ERR_ROOM_FULL_1001;
	else return room->enterPlayer(player);
}


void World::enterRoomSuccess(ServiceConnection* conn, Player* player, err_t reason)
{
}


void World::enterRoomFailed(ServiceConnection* conn, Player* player, err_t reason)
{

}

void World::onReqLeaveRoom(ServiceConnection* conn, MSG_HEAD_BACK* head, char* body)
{
	MSG_REQ_LEAVE_ROOM* msg = (MSG_REQ_LEAVE_ROOM*)body;
	Player* player = findPlayer(head->pid);
	Room* room = findRoom(head->rid);
	err_t err = tryLeaveRoom(room, player);
	if (err) leaveRoomFailed(conn, player, err);
	else leaveRoomSuccess(conn, player, err);
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
	char body[4] = { 0 };
	size_t size = 0;
	msg.writeBody(body, &size);
	head.length = size;

	conn->send((char*)&head, sizeof(MSG_HEAD_BACK), body, size);
}


void World::leaveRoomFailed(ServiceConnection* conn, Player* player, err_t reason)
{

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

Player* World::addPlayer(pid_t pid, Player* player)
{
	mPlayers.insert(map_player::value_type(pid, player));
}

Player* World::findPlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		return it->second;
	}
	return NULL;
}

Player* World::removePlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		mPlayers.erase(it);
		return it->second;
	}
	return NULL;
}

