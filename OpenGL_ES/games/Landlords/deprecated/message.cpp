#include "message.h"
/**
*	MsgBase
**/
MsgBase::MsgBase()
{
};

MsgBase::MsgBase(unsigned short mid)
{
	msgid = mid;
};

void MsgBase::writeExternal(Bytes* output)
{
	Bytes body;
	writeBody(&body);
	Bytes head;
	writeHead(&head,&body);
	writeBytes(output,&head,0,head.length);
	writeBytes(output,&body,0,body.length);
};

void MsgBase::readExternal(Bytes* input)
{
	readHead(input);
	readBody(input);
};

void MsgBase::writeHead(Bytes* output, Bytes* body)
{
	writeUnsignedInt(output,HEAD_LENGTH + body->length);
	writeShort(output,msgid);
	writeUnsignedInt(output,userid);
};

void MsgBase::readHead(Bytes *input)
{
	length = readUnsignedInt(input);
	msgid = readUnsignedShort(input);
	userid = readUnsignedInt(input);
};
/**
*	MSG_BRDCST_DEAL_RESULT
**/
MSG_BRDCST_DEAL_RESULT::MSG_BRDCST_DEAL_RESULT()
{
	msgid = MSG_BRDCST_DEAL_RESULT_999;
};
void MSG_BRDCST_DEAL_RESULT::writeBody(Bytes* output)
{
	char* data = (char*)result;
	Bytes bytes;
	writeBytes(output,&bytes,0,sizeof(DealResult));
};

void MSG_BRDCST_DEAL_RESULT::readBody(Bytes* input)
{
	
};
/**
*	MSG_SEV_WAIT_LOOT
**/
MSG_SEV_WAIT_LOOT::MSG_SEV_WAIT_LOOT()
{
	
};

void MSG_SEV_WAIT_LOOT::writeBody(Bytes* output)
{

};

void MSG_SEV_WAIT_LOOT::readBody(Bytes* input)
{
	
};