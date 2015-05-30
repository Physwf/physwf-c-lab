#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "type.h"

#define MSG_REQ_LOGIN_0001				0001

#define MSG_NEW_PLAYER_1000				1000
#define MSG_DESTROY_PLAYER_1001			1001

#define MSG_REQ_ENTER_ROOM_1002			1002
#define MSG_REQ_LEAVE_ROOM_1003			1003
#define MSG_REQ_JOIN_GAME_1004			1004
#define MSG_REQ_LEAVE_GAME_1005			1005

#define MSG_ERR_ROOM_NOT_EXIST_1000		1000
#define MSG_ERR_ROOM_FULL_1001			1001
#define MSG_ERR_ALREADY_IN_1002			1002
#define MSG_ERR_NOT_IN_ROOM_1003		1003

#include "Message.h"

struct MSG_REQ_LOGIN : Message
{
	unsigned char accout_length;
	char* accout;
	char psd_hash[32];

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_NEW_PLAYER : Message
{
	pid_t pid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_DESTROY_PLAYER : Message
{
	pid_t pid;
	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_REQ_ENTER_ROOM : Message
{
	pid_t pid;
	rid_t rid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_REQ_LEAVE_ROOM : Message
{
	pid_t pid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_REQ_JOIN_GAME : Message
{
	pid_t pid;
	gid_t gid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_REQ_LEAVE_GAME : Message
{
	pid_t pid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};
/*
#include "Message.h"

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


struct MSG_NOTI_DEAL_RESULT : Message
{
	unsigned char count;
	char* cards;
	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};
//call
struct MSG_TURN_CALL : Message
{
	inline virtual void writeBody(char* input, size_t size){}
};

struct MSG_SUBM_CALL : Message
{
	inline virtual void readBody(char* input, size_t size){}
};

struct MSG_SUBM_NOT_CALL : Message
{
	inline virtual void readBody(char* input, size_t size){}
};

struct MSG_NOTI_CALL_OR_NOT : Message
{
	 char pid;
	 bool yes;
	 inline virtual void writeBody(char* output, size_t* size);
};
//loot
struct MSG_TURN_LOOT : Message
{
	inline virtual void writeBody(char* input, size_t size){}
};
struct MSG_SUBM_LOOT : Message
{
	inline virtual void readBody(char* input, size_t size){}
};
struct MSG_SUBM_NOT_LOOT : Message
{
	inline virtual void readBody(char* input, size_t size){}
};

struct MSG_NOTI_LOOT_OR_NOT : Message
{
	 char pid;
	 bool yes;
	 inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_NOTI_LOOT_RESULT : Message
{
	 char pid;
	 char cards[6];
	 inline virtual void writeBody(char* output, size_t* size);
};

//play
struct MSG_TURN_PLAY : Message
{
	unsigned char count;
	char* basecards;
	inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_SUBM_PLAY : Message
{
	unsigned char count;
	char* cards;
	inline virtual void readBody(char* input, size_t size);
};

struct MSG_NOTI_PLAY : Message
{
	 char pid;
	 unsigned char count;
	 char* cards;
	 inline virtual void writeBody(char* output, size_t* size);
};

struct MSG_SUBM_PASS : Message
{
	inline virtual void readBody(char* input, size_t size){}
};

struct MSG_NOTI_PASS : Message
{
	 char pid;
	 inline virtual void writeBody(char* output, size_t* size);
};
//game over
struct MSG_NOTI_WIN : Message
{
	inline virtual void writeBody(char* output, size_t* size){}
};

struct MSG_NOTI_LOSE : Message
{
	inline virtual void writeBody(char* output, size_t* size){}
};
//error
struct MSG_NOTI_OP_ILLEGAL : Message
{
	inline virtual void writeBody(char* output, size_t* size){}
};
*/
#endif
