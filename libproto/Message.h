#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "type.h"

typedef struct s_msg_head_back
{
	unsigned short length;
	mid_t id;
} MSG_HEAD_BACK;

typedef struct s_msg_head_gate
{
	unsigned short length;
	mid_t id;
	pid_t pid;
	err_t err;
} MSG_HEAD_GATE;


int read_head(char* buff, MSG_HEAD_BACK* head);

#define C_SIZE sizeof(char)
#define S_SIZE sizeof(short)
#define I_SIZE sizeof(int)
#define L_SIZE sizeof(long)

struct Message
{
	Message();
	Message(mid_t mid);

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t size);

	inline char readByte(char* input);
	inline unsigned char readUnsignedByte(char* input);
	inline void writeByte();
	inline void writeUnsigndByte();

	inline short readShort(char* input);
	inline unsigned short readUnsignedShort(char* input);

	inline char* readBytes(char* input, size_t size);
protected:
	char aBuffer[512];
	size_t nOffset;
};
#include "SyncMsgConnection.h"
#include <set>
typedef SyncMsgConnection<mid_t, MSG_HEAD_GATE> ClientConnection;
typedef SyncMsgConnection<mid_t, MSG_HEAD_BACK> ServiceConnection;
typedef std::set<ClientConnection*> ClientBuffer;
typedef std::set<ServiceConnection*> ServiceBuffer;

#endif