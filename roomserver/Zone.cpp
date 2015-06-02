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
		head.pid = head.rid = head.tid = 0;
		head.err = 0;
		head.cid = nCid;
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
	head.pid = head.rid = head.tid = 0;
	head.err = 0;
	head.cid = nCid;
	pGame->send((char*)&head, sizeof(MSG_HEAD_BACK), body, size);
}


