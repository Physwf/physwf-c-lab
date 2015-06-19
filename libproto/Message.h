#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "type.h"
#include "platform.h"

typedef struct
{
	unsigned short length;//2
	unsigned short type;//2
	mid_t id;//4
	pid_t pid;//4
	rid_t rid;//2
	tid_t tid;//2
	cid_t cid;//2
	err_t err;//2
} MSG_HEAD_BACK;

typedef struct 
{
	unsigned short length;//2
	unsigned short type;//2
	mid_t id;//4
	pid_t pid;//4
	iid_t iid;//4
	rid_t rid;//2
	tid_t tid;//2
	cid_t cid;//2
	err_t err;//4
} MSG_HEAD_GAME;

struct MSG_HEAD_GATE
{
	unsigned short length;
	mid_t id;
	err_t err;
};

#define HEAD_LENGTH_GATE sizeof(unsigned short)+sizeof(mid_t)+sizeof(err_t)
#define HEAD_LENGTH_BACK sizeof(unsigned short)\
							+ sizeof(unsigned short)\
							+ sizeof(mid_t)\
							+ sizeof(pid_t)\
							+ sizeof(rid_t)\
							+ sizeof(tid_t)\
							+ sizeof(cid_t)\
							+ sizeof(err_t)

#define HEAD_LENGTH_GAME sizeof(unsigned short)\
							+ sizeof(unsigned short)\
							+ sizeof(mid_t)\
							+ sizeof(pid_t)\
							+ sizeof(iid_t)\
							+ sizeof(rid_t)\
							+ sizeof(tid_t)\
							+ sizeof(cid_t)\
							+ sizeof(err_t)

#define MAX_MSG_LENGTH 512

#define MSG_TYPE_PLAYER			1
#define MSG_TYPE_CHANEL			2
#define MSG_TYPE_BROADCAST		3

VALE_DLL inline int read_head_gate(char* buff, MSG_HEAD_GATE* head);
VALE_DLL inline int read_head_back(char* buff, MSG_HEAD_BACK* head);
VALE_DLL inline int read_head_game(char* buff, MSG_HEAD_GAME* head);

VALE_DLL inline int write_head_gate(char* buff, MSG_HEAD_GATE* head);
VALE_DLL inline int write_head_back(char* buff, MSG_HEAD_BACK* head);
VALE_DLL inline int write_head_game(char* buff, MSG_HEAD_GAME* head);

struct Message;

VALE_DLL inline int pack_back_msg(char* buff, MSG_HEAD_BACK* head, Message* body);
VALE_DLL inline int pack_back_msg2(char* buff, MSG_HEAD_BACK* head, char* body);
VALE_DLL inline int pack_gate_msg(char* buff, MSG_HEAD_GATE* head, Message* body);
VALE_DLL inline int pack_gate_msg2(char* buff, MSG_HEAD_GATE* head, char* body);
VALE_DLL inline int pack_game_msg(char* buff, MSG_HEAD_GAME* head, Message* body);
VALE_DLL inline int pack_game_msg2(char* buff, MSG_HEAD_GAME* head, char* body);


#define C_SIZE sizeof(char)
#define B_SIZE sizeof(bool)
#define S_SIZE sizeof(short)
#define I_SIZE sizeof(int)
#define L_SIZE sizeof(long)

struct VALE_DLL  Message
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

#endif