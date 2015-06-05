#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "type.h"

union MyUnion
{

};
typedef struct s_msg_head_back
{
	size_t length;
	mid_t id;
	unsigned short type;
	rid_t rid;
	gid_t tid;
	pid_t pid;
	cid_t cid;
	err_t err;
} MSG_HEAD_BACK;

struct MSG_HEAD_GATE
{
	unsigned short length;
	mid_t id;
	err_t err;
};

#define MSG_TYPE_PLAYER			1
#define MSG_TYPE_CHANEL			2
#define MSG_TYPE_BROADCAST		3

inline int read_head_gate(char* buff, MSG_HEAD_GATE* head);
inline int read_head_back(char* buff, MSG_HEAD_BACK* head);

inline int write_head_gate(char* buff, MSG_HEAD_GATE* head);
inline int write_head_back(char* buff, MSG_HEAD_BACK* head);

inline int pack_back_msg(char* buff, MSG_HEAD_BACK* head, Message* body);
inline int pack_gate_msg(char* buff, MSG_HEAD_BACK* head, Message* body);

#define C_SIZE sizeof(char)
#define B_SIZE sizeof(bool)
#define S_SIZE sizeof(short)
#define I_SIZE sizeof(int)
#define L_SIZE sizeof(long)

struct Message
{
	Message();
	Message(mid_t mid);

	inline virtual void readBody(char* input, size_t size);
	inline virtual void writeBody(char* output, size_t* size);

	inline char readByte(char* input);
	inline unsigned char readUnsignedByte(char* input);
	inline void writeByte(char value);
	inline void writeUnsigndByte(unsigned char value);

	inline bool readBoolean(char* input);
	inline void writeBoolean(bool value);

	inline short readShort(char* input);
	inline unsigned short readUnsignedShort(char* input);
	inline void writeShort(short value);
	inline void writeUnsignedShort(unsigned short value);

	inline int readInt(char* input);
	inline unsigned int readUnsignedInt(char* input);
	inline void writeInt(int value);
	inline void writeUnsignedInt(unsigned int value);

	inline long readLong(char* input);
	inline unsigned long readUnsignedLong(char* input);
	inline void writeLong(long value);
	inline void writeUnsignedLong(unsigned long value);

	inline char* readBytes(char* input, size_t size);
	inline void writeBytes(char* bytes, size_t size);
	inline void readBytes(char*input, char* output, size_t size);

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