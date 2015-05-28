#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "type.h"

#define MSG_NEW_PLAYER 0001
#define MSG_DESTROY_PLAYER 0002

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

#define MSG_CONNECTED 
#define MSG_NOTI_DEAL_RESULT_2001
#define MSG_TURN_CALL_2002
#define MSG_SUBM_CALL_2003
#define MSG_SUBM_NOT_CALL_2004
#define MSG_NOTI_CALL_2005
#define MSG_NOTI_NOT_CALL_2006
#define MSG_TURN_LOOT_2007
#define MSG_SUBM_LOOT_2008
#define MSG_SUBM_NOT_LOOT_2009
#define MSG_NOTI_LOOT_2010
#define MSG_NOTI_NOT_LOOT_2011
#define MSG_NOTI_LOOT_RESULT_2012
#define MSG_TURN_PLAY_2013
#define MSG_SUBM_PLAY_2014
#define MSG_NOTI_PLAY_2015
#define MSG_SUBM_PASS_2016
#define MSG_NOTI_PASS_2017
#define MSG_NOTI_WIN_2018
#define MSG_NOTI_LOSE_2019
#define MSG_NOTI_OP_ILLEGAL_2100 

#define MSG_JOIN_SUCCESS_1000 


struct MSG_NOTI_DEAL_RESULT
{
	unsigned char count;
	char cards[];
};
//call
struct MSG_TURN_CALL
{

};
struct MSG_SUBM_CALL
{

};

struct MSG_SUBM_NOT_CALL
{

};

struct MSG_NOTI_CALL_OR_NOT
{
	 char pid;
	 bool yes;
};
//loot
struct MSG_TURN_LOOT
{
};
struct MSG_SUBM_LOOT
{

};
struct MSG_SUBM_NOT_LOOT
{

};

struct MSG_NOTI_LOOT_OR_NOT
{
	 char pid;
	 bool yes;
};

struct MSG_NOTI_LOOT_RESULT
{
	 char pid;
	 char cards[6];
};

//play
struct MSG_TURN_PLAY
{
	unsigned char count;
	char basecards[];
};

struct MSG_SUBM_PLAY
{
	unsigned char count;
	char cards[];
};

struct MSG_NOTI_PLAY
{
	 char pid;
	 unsigned char count;
	 char cards[];
};

struct MSG_SUBM_PASS
{

};

struct MSG_NOTI_PASS
{
	 char pid;
};
//game over
struct MSG_NOTI_WIN
{
};

struct MSG_NOTI_LOSE
{
};
//error
struct MSG_NOTI_OP_ILLEGAL
{
};

#endif
