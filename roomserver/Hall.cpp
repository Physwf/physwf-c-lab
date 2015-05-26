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

}

void Hall::onDestroyPlayer(void* head, void* body)
{

}

void Hall::onReqEnterRoom(void* head, void* body)
{
	MSG_HEAD_ROOM* hd = (MSG_HEAD_ROOM*)head;
	MSG_REQ_ENTER_ROOM_1000* msg = (MSG_REQ_ENTER_ROOM_1000*)body;
	hd->pid;
}

void Hall::onReqLeaveRoom(void* head, void* body)
{

}

