#ifndef _HALL_H
#define _HALL_H

#include "type.h"

#include "Protocol.h"

class Hall : public Object
{
public:
	Hall();
	~Hall();
public:
	void initialize();
private:
	void onNewPlayer(void* head, void* body);
	void onDestroyPlayer(void* head, void* body);
	void onReqEnterRoom(void* head, void* body);
	void onReqLeaveRoom(void* head, void* body);

};
#endif