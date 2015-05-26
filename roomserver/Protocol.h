#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "type.h"

#define MSG_NEW_PLAYER 100
#define MSG_DESTROY_PLAYER 101
#define MSG_REQ_ENTER_ROOM 1000
#define MSG_REQ_LEAVE_ROOM 1001
#define MSG_REQ_JOIN_GAME 1002
#define MSG_REQ_LEAVE_GAME 1003

#define MSG_ERR_ROOM_NOT_EXIST 1000
#define MSG_ERR_ROOM_FULL 1001
#define MSG_ERR_ALREADY_IN 1002
#define MSG_ERR_NOT_IN_ROOM 1003

struct MSG_NEW_PLAYER_100
{
	pid_t player_id;
};

struct MSG_DESTROY_PLAYER_101
{
	pid_t player_id;
};

struct MSG_REQ_ENTER_ROOM_1000
{
	pid_t player_id;
	rid_t room_id;
};

struct MSG_REQ_LEAVE_ROOM_1001
{
	rid_t room_id;
};


#endif
