#include "Hall.h"
#include "Master.h"
#include "Protocol.h"
#include "Message.h"

Hall::Hall()
{

}

Hall::~Hall()
{

}

void Hall::initialize()
{
	Master::gateway()->registerMsgHandler(MSG_REQ_ENTER_ROOM, EV_CB(this, Hall::onReqEnterRoom));
	Master::gateway()->registerMsgHandler(MSG_REQ_LEAVE_ROOM, EV_CB(this, Hall::onReqLeaveRoom));
}

void Hall::onNewPlayer(void* head, void* body)
{
	MSG_NEW_PLAYER_100* msg = (MSG_NEW_PLAYER_100*)body;
	Player* player = new Player(msg->player_id);
	addPlayer(player->pid(), player);
}

void Hall::onDestroyPlayer(void* head, void* body)
{
	MSG_DESTROY_PLAYER_101* msg = (MSG_DESTROY_PLAYER_101*)body;
	Player* player = removePlayer(msg->player_id);
}

void Hall::onReqEnterRoom(void* head, void* body)
{
	MSG_HEAD_ROOM* hd = (MSG_HEAD_ROOM*)head;
	MSG_REQ_ENTER_ROOM_1000* msg = (MSG_REQ_ENTER_ROOM_1000*)body;
	Player* player = findPlayer(msg->player_id);
	tryEnterRoom(msg->room_id,player);
}

void Hall::tryEnterRoom(rid_t rid, Player* player)
{
	Room* room = findRoom(rid);
	if (!room)
	{
		enterRoomFailed(player->pid(), MSG_ERR_ROOM_NOT_EXIST);
	}
	else if (!room->avaliable())
	{
		enterRoomFailed(player->pid(), MSG_ERR_ROOM_FULL);
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

void Hall::tryLeaveRoom(rid_t rid, Player* player)
{
	Room* room = findRoom(rid);
	if (!room)
	{
		leaveRoomFailed(player->pid(), MSG_ERR_ROOM_NOT_EXIST);
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

void Hall::onReqLeaveRoom(void* head, void* body)
{
	MSG_HEAD_ROOM* hd = (MSG_HEAD_ROOM*)head;
	MSG_REQ_LEAVE_ROOM_1001* msg = (MSG_REQ_LEAVE_ROOM_1001*)body;
}

Room* Hall::findRoom(rid_t rid)
{
	map_room::iterator it = mRooms.find(rid);
	if (it != mRooms.end())
	{
		return it->second;
	}
	return NULL;
}

Player* Hall::addPlayer(pid_t pid, Player* player)
{
	mPlayers.insert(map_player::value_type(pid, player));
}

Player* Hall::findPlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		return it->second;
	}
	return NULL;
}

Player* Hall::removePlayer(pid_t pid)
{
	map_player::iterator it = mPlayers.find(pid);
	if (it != mPlayers.end())
	{
		mPlayers.erase(it);
		return it->second;
	}
	return NULL;
}

