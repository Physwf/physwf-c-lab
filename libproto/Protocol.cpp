#include "Protocol.h"

void MSG_NOTI_DEAL_RESULT::readBody(char* input)
{
	count = readByte(input);
	cards = readBytes(input, count * C_SIZE);
}