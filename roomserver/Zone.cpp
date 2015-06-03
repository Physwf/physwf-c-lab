#include "Zone.h"
#include "Protocol.h"

Zone::~Zone()
{

}

cid_t Zone::nIncreaser = 0;

cid_t Zone::getNextId()
{
	return ++nIncreaser;
}

void Zone::tryCreate()
{
	if (!nCid)
	{
		nCid = getNextId();
		MSG_HEAD_BACK head;
		head.id = MSG_CREATE_CHANEL_100;
		head.type = MSG_TYPE_CHANEL;
		head.rid = head.tid = head.pid = 0;
		head.err = 0;
		MSG_CREATE_CHANEL body;
		body.cid = nCid;
		char data[4] = { 0 };
		size_t bSize = 0;
		body.writeBody(data, &bSize);
		pGame->send((char*)&head, sizeof(MSG_HEAD_BACK), data,bSize);
	}
}

void Zone::broadcast(mid_t mid,char* body,size_t size)
{
	MSG_HEAD_BACK head;
	head.id = mid;
	head.type = MSG_TYPE_BROADCAST;
	head.err = 0;
	char body[32];
	pGame->send((char*)&head, sizeof(MSG_HEAD_BACK), body, size);
}


