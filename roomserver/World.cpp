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


void World::onGatewayMessage(ServiceConnection* conn, void* head, void* body)
{

}

void World::onNewPlayer(ServiceConnection* conn, void* head, void* body)
{
	MSG_REQ_CREATE_PLAYER* msg = (MSG_REQ_CREATE_PLAYER*)body;
	Player* player = new Player(msg->pid);
	addPlayer(player->pid(), player);
}

void World::onDestroyPlayer(ServiceConnection* conn, void* head, void* body)
{
	MSG_REQ_DESTROY_PLAYER* msg = (MSG_REQ_DESTROY_PLAYER*)body;
	Player* player = removePlayer(msg->pid);
}

void World::onReqEnterRoom(ServiceConnection* conn, void* head, void* body)
{
	MSG_HEAD_BACK* hd = (MSG_HEAD_BACK*)head;
	MSG_REQ_ENTER_ROOM* msg = (MSG_REQ_ENTER_ROOM*)body;
	Player* player = findPlayer(msg->pid);
	tryEnterRoom(msg->rid,player);
}

void World::tryEnterRoom(rid_t rid, Player* player)
{
	Room* room = findRoom(rid);
	if (!room)
	{
		enterRoomFailed(player->pid(), MSG_ERR_ROOM_NOT_EXIST_1000);
	}
	else if (!room->avaliable())
	{
		enterRoomFailed(player->pid(), MSG_ERR_ROOM_FULL_1001);
	}
	else
	{
		err_t err;
		if (err = room->enterPlayer(player))
			enterRoomFailed(player->pid(), err);
		else
			enterRoomSuccess(player->pid(), 0);
	}
}

void World::tryLeaveRoom(rid_t rid, Player* player)
{
	Room* room = findRoom(rid);
	if (!room)
	{
		leaveRoomFailed(player->pid(), MSG_ERR_ROOM_NOT_EXIST_1000);
	}
	else
	{
		err_t err;
		if (err = room->leavePlayer(player))
			leaveRoomFailed(player->pid(), err);
		else
			leaveRoomSuccess(player->pid(), 0);
	}
}

void World::onReqLeaveRoom(ServiceConnection* conn, void* head, void* body)
{
	MSG_HEAD_BACK* hd = (MSG_HEAD_BACK*)head;
	MSG_REQ_LEAVE_ROOM* msg = (MSG_REQ_LEAVE_ROOM*)body;
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

