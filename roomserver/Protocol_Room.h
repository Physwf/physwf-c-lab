#include "Message.h"

#define MSG_NEW_PLAYER_0001				0001
#define MSG_DESTROY_PLAYER_0002			0002

#define MSG_REQ_ENTER_ROOM_1000			1000
#define MSG_REQ_LEAVE_ROOM_1001			1001
#define MSG_REQ_JOIN_GAME_1002			1002
#define MSG_REQ_LEAVE_GAME_1003			1003

#define MSG_ERR_ROOM_NOT_EXIST_1000		1000
#define MSG_ERR_ROOM_FULL_1001			1001
#define MSG_ERR_ALREADY_IN_1002			1002
#define MSG_ERR_NOT_IN_ROOM_1003		1003

struct MSG_NEW_PLAYER : Message
{
	pid_t pid;

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);
};