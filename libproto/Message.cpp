#include "Message.h"
#include <string>

Message::Message()
{
	nOffset = 0;
}

Message::Message(mid_t mid)
{

}

void Message::readBody(char* input, size_t size)
{
	memcpy(aBuffer, input + nOffset, size);
	nOffset = 0;
}

void Message::writeBody(char* output, size_t* size)
{
	memcpy(output, aBuffer, nOffset);
	*size = nOffset;
}

char Message::readByte(char* input)
{
	char value;
	memcpy(&value, input + nOffset, C_SIZE);
	nOffset += C_SIZE;
	return value;
}

unsigned char Message::readUnsignedByte(char* input)
{
	unsigned char value;
	memcpy(&value, input + nOffset, C_SIZE);
	nOffset += C_SIZE;
	return value;
}

bool Message::readBoolean(char* input)
{
	bool value;
	memcpy(&value, input + nOffset, B_SIZE);
	nOffset += B_SIZE;
	return value;
}

void Message::writeBoolean(bool value)
{
	memcpy(&aBuffer[nOffset], &value, B_SIZE);
	nOffset += B_SIZE;
}

void Message::writeByte(char value)
{
	memcpy(&aBuffer[nOffset], &value, C_SIZE);
	nOffset += C_SIZE;
}

void Message::writeUnsigndByte(unsigned char value)
{
	writeByte(value);
}

short Message::readShort(char* input)
{
	short value;
	memcpy(&value, input + nOffset, S_SIZE);
	nOffset += S_SIZE;
	return value;
}

unsigned short Message::readUnsignedShort(char* input)
{
	unsigned short value;
	memcpy(&value, input + nOffset, S_SIZE);
	nOffset += S_SIZE;
	return value;
}

void Message::writeShort(short value)
{
	memcpy(&aBuffer[nOffset], &value, S_SIZE);
	nOffset += S_SIZE;
}

void Message::writeUnsignedShort(unsigned short value)
{
	writeShort(value);
}

int Message::readInt(char* input)
{
	int value;
	memcpy(&value, input + nOffset, I_SIZE);
	nOffset += I_SIZE;
	return value;
}

unsigned int Message::readUnsignedInt(char* input)
{
	unsigned int value;
	memcpy(&value, input+nOffset, I_SIZE);
	nOffset += I_SIZE;
	return value;
}

void Message::writeInt(int value)
{
	memcpy(&aBuffer[nOffset], &value, I_SIZE);
	nOffset += I_SIZE;
}

void Message::writeUnsignedInt(unsigned int value)
{
	writeInt(value);
}

long Message::readLong(char* input)
{
	long value;
	memcpy(&value, input + nOffset, L_SIZE);
	nOffset += L_SIZE;
	return value;
}

unsigned long Message::readUnsignedLong(char* input)
{
	unsigned long value;
	memcpy(&value, input + nOffset, L_SIZE);
	nOffset += L_SIZE;
	return value;
}

void Message::writeLong(long value)
{
	memcpy(&aBuffer[nOffset], &value, L_SIZE);
	nOffset += L_SIZE;
}

void Message::writeUnsignedLong(unsigned long value)
{
	writeLong(value);
}

char* Message::readBytes(char* input, size_t size)
{
	nOffset += size;
	return &aBuffer[nOffset-size];
}

void Message::readBytes(char*input, char* output, size_t size)
{

}

void Message::writeBytes(char* bytes, size_t size)
{
	memcpy(&aBuffer[nOffset], bytes, size);
	nOffset += size;
}

int read_head_gate(char* buff, MSG_HEAD_GATE* head)
{
	size_t size = 0;
	memcpy(&head->length, buff, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);
	memcpy(&head->id, buff, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);
	memcpy(&head->err, buff, sizeof(head->err));
	size += sizeof(head->err);
	return size;
}

int read_head_back(char* buff, MSG_HEAD_BACK* head)
{
	size_t size = 0;
	memcpy(&head->length, buff, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);

	memcpy(&head->type, buff, sizeof(head->type));
	size += sizeof(head->type);
	buff += sizeof(head->type);

	memcpy(&head->id, buff, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);

	memcpy(&head->pid, buff, sizeof(head->pid));
	size += sizeof(head->pid);
	buff += sizeof(head->pid);

	memcpy(&head->rid, buff, sizeof(head->rid));
	size += sizeof(head->rid);
	buff += sizeof(head->rid);

	memcpy(&head->tid, buff, sizeof(head->tid));
	size += sizeof(head->tid);
	buff += sizeof(head->tid);

	memcpy(&head->cid, buff, sizeof(head->cid));
	size += sizeof(head->cid);
	buff += sizeof(head->cid);

	memcpy(&head->err, buff, sizeof(head->err));
	size += sizeof(head->err);

	return size;
}

int read_head_game(char* buff, MSG_HEAD_GAME* head)
{
	size_t size = 0;
	memcpy(&head->length, buff, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);

	memcpy(&head->type, buff, sizeof(head->type));
	size += sizeof(head->type);
	buff += sizeof(head->type);

	memcpy(&head->id, buff, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);

	/*memcpy(&head->pid, buff, sizeof(head->pid));
	size += sizeof(head->pid);
	buff += sizeof(head->pid);*/

	memcpy(&head->iid, buff, sizeof(head->iid));
	size += sizeof(head->iid);
	buff += sizeof(head->iid);

	/*memcpy(&head->rid, buff, sizeof(head->rid));
	size += sizeof(head->rid);
	buff += sizeof(head->rid);*/

	/*memcpy(&head->tid, buff, sizeof(head->tid));
	size += sizeof(head->tid);
	buff += sizeof(head->tid);*/

	memcpy(&head->sid, buff, sizeof(head->sid));
	size += sizeof(head->sid);
	buff += sizeof(head->sid);

	/*memcpy(&head->cid, buff, sizeof(head->cid));
	size += sizeof(head->cid);
	buff += sizeof(head->cid);*/

	memcpy(&head->err, buff, sizeof(head->err));
	size += sizeof(head->err);

	return size;
}

int write_head_gate(char* buff, MSG_HEAD_GATE* head)
{
	size_t size = 0;
	memcpy(buff, &head->length, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);
	memcpy(buff, &head->id, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);
	memcpy(buff, &head->err, sizeof(head->err));
	size += sizeof(head->err);
	return size;
}

int write_head_back(char* buff, MSG_HEAD_BACK* head)
{
	size_t size = 0;
	memcpy(buff, &head->length, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);

	memcpy(buff, &head->type, sizeof(head->type));
	size += sizeof(head->type);
	buff += sizeof(head->type);

	memcpy(buff, &head->id, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);

	memcpy(buff, &head->pid, sizeof(head->pid));
	size += sizeof(head->pid);
	buff += sizeof(head->pid);

	memcpy(buff, &head->rid, sizeof(head->rid));
	size += sizeof(head->rid);
	buff += sizeof(head->rid);

	memcpy(buff, &head->tid, sizeof(head->tid));
	size += sizeof(head->tid);
	buff += sizeof(head->tid);

	memcpy(buff, &head->cid, sizeof(head->cid));
	size += sizeof(head->cid);
	buff += sizeof(head->cid);

	memcpy(buff, &head->err, sizeof(head->err));
	size += sizeof(head->err);
	buff += sizeof(head->err);

	return size;
}

int write_head_game(char* buff, MSG_HEAD_GAME* head)
{
	size_t size = 0;
	memcpy(buff, &head->length, sizeof(head->length));
	size += sizeof(head->length);
	buff += sizeof(head->length);

	memcpy(buff, &head->type, sizeof(head->type));
	size += sizeof(head->type);
	buff += sizeof(head->type);

	memcpy(buff, &head->id, sizeof(head->id));
	size += sizeof(head->id);
	buff += sizeof(head->id);

	/*memcpy(buff, &head->pid, sizeof(head->pid));
	size += sizeof(head->pid);
	buff += sizeof(head->pid);*/

	memcpy(buff, &head->iid, sizeof(head->iid));
	size += sizeof(head->iid);
	buff += sizeof(head->iid);

	/*memcpy(buff, &head->rid, sizeof(head->rid));
	size += sizeof(head->rid);
	buff += sizeof(head->rid);

	memcpy(buff, &head->tid, sizeof(head->tid));
	size += sizeof(head->tid);
	buff += sizeof(head->tid);*/

	memcpy(buff, &head->sid, sizeof(head->sid));
	size += sizeof(head->sid);
	buff += sizeof(head->sid);

	/*memcpy(buff, &head->cid, sizeof(head->cid));
	size += sizeof(head->cid);
	buff += sizeof(head->cid);*/

	memcpy(buff, &head->err, sizeof(head->err));
	size += sizeof(head->err);
	buff += sizeof(head->err);

	return size;
}

int pack_back_msg(char* buff, MSG_HEAD_BACK* head, Message* body)
{
	write_head_back(buff, head);
	size_t bsize = 0;
	body->writeBody(buff + HEAD_LENGTH_BACK, &bsize);
	head->length = bsize;
	write_head_back(buff, head);
	return HEAD_LENGTH_BACK+bsize;
}

int pack_back_msg2(char* buff, MSG_HEAD_BACK* head, char* body)
{
	write_head_back(buff, head);
	memcpy(buff + HEAD_LENGTH_BACK, body, head->length);
	return HEAD_LENGTH_BACK + head->length;
}

int pack_gate_msg(char* buff, MSG_HEAD_GATE* head, Message* body)
{
	int hsize = write_head_gate(buff, head);
	size_t bsize = 0;
	body->writeBody(buff + hsize, &bsize);
	head->length = bsize;
	write_head_gate(buff, head);
	return bsize + hsize;
}

int pack_gate_msg2(char* buff, MSG_HEAD_GATE* head, char* body)
{
	write_head_gate(buff, head);
	size_t size = 0;
	memcpy(buff + HEAD_LENGTH_GATE, body,head->length);
	return HEAD_LENGTH_GATE + head->length;
}

int pack_game_msg(char* buff, MSG_HEAD_GAME* head, Message* body)
{
	int hsize = write_head_game(buff, head);
	size_t bsize = 0;
	body->writeBody(buff + hsize, &bsize);
	head->length = bsize;
	write_head_game(buff, head);
	return bsize + hsize;
}

int pack_game_msg2(char* buff, MSG_HEAD_GAME* head, char* body)
{
	write_head_game(buff, head);
	size_t size = 0;
	memcpy(buff + HEAD_LENGTH_GAME, body, head->length);
	return HEAD_LENGTH_GAME + head->length;
}

VALE_DLL void game_to_back(MSG_HEAD_GAME* game, MSG_HEAD_BACK* back)
{
	//back->cid = game->cid;
	back->err = game->err;
	back->id = game->id;
	back->length = game->length;
	//back->pid = game->pid;
	//back->rid = game->rid;
	//back->tid = game->tid;
	back->type = game->type;
}

VALE_DLL void back_to_game(MSG_HEAD_BACK* back, MSG_HEAD_GAME* game)
{

}

VALE_DLL void back_to_gate(MSG_HEAD_BACK* back, MSG_HEAD_GATE* gate)
{

}

VALE_DLL void gate_to_back(MSG_HEAD_GATE* gate, MSG_HEAD_BACK* back)
{

}


