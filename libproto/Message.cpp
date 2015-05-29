#include "Message.h"

Message::Message()
{

}

Message::Message(mid_t mid)
{

}

void Message::readBody(char* input, size_t size)
{
	nOffset = 0;
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

char* Message::readBytes(char* input, size_t size)
{
	memcpy(aBuffer, input + nOffset, size);
	nOffset += size;
	//aBuffer += size;
}