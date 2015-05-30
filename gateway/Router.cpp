#include "Router.h"
#include "Protocol.h"

Router::Router()
{

}

Router::~Router()
{

}

void Router::addClientForRoute(ClientConnection* client)
{
	client->registerMsgHandler(MSG_REQ_ENTER_ROOM_1000, EV_CB(this, Router::doRoute));
	client->registerMsgHandler(MSG_REQ_LEAVE_ROOM_1001, EV_CB(this, Router::doRoute));
	client->registerMsgHandler(MSG_REQ_JOIN_GAME_1002, EV_CB(this, Router::doRoute));
	client->registerMsgHandler(MSG_REQ_LEAVE_GAME_1003, EV_CB(this, Router::doRoute));
}

void Router::addServiceForRoute(ServiceConnection* service)
{

}

void Router::doRoute(char* head, char* body)
{

}

