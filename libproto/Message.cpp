#include "Message.h"

Message::Message()
{

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
	nOffset += C_SIZE;
	return *(input + nOffset - C_SIZE);
}

unsigned char Message::readUnsignedByte(char* input)
{
	nOffset += C_SIZE;
	return (unsigned char)*(input + nOffset - C_SIZE);
}

bool Message::readBoolean(char* input)
{
	nOffset += B_SIZE;
	return (bool)*(input + nOffset - B_SIZE);
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
	nOffset += S_SIZE;
	return (short)*(input + nOffset - S_SIZE);
}

unsigned short Message::readUnsignedShort(char* input)
{
	nOffset += S_SIZE;
	return (unsigned short)*(input + nOffset - S_SIZE);
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
	nOffset += I_SIZE;
	return *(input + nOffset - I_SIZE);
}

unsigned int Message::readUnsignedInt(char* input)
{
	nOffset += I_SIZE;
	return (unsigned int)*(input + nOffset - I_SIZE);
}

void Message::writeInt(int value)
{
	memcpy(&aBuffer[nOffset], &value, I_SIZE);
	nOffset += I_SIZE;
}

void Message::writeUnsignedInt(unsigned int value)
{
	writeUnsignedInt(value);
}

long Message::readLong(char* input)
{
	nOffset += I_SIZE;
	return *(input + nOffset - I_SIZE);
}

unsigned long Message::readUnsignedLong(char* input)
{
	nOffset += I_SIZE;
	return (unsigned long)*(input + nOffset - I_SIZE);
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

}

int read_head_back(char* buff, MSG_HEAD_BACK* head)
{

}

int write_head_gate(char* buff, MSG_HEAD_GATE* head)
{

}

int write_head_back(char* buff, MSG_HEAD_BACK* head)
{

}

int pack_back_msg(char* buff, MSG_HEAD_BACK* head, Message* body)
{

}

int pack_gate_msg(char* buff, MSG_HEAD_BACK* head, Message* body)
{

}
