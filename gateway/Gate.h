#ifndef _GATE_H
#define _GATE_H

#define MODE_NEGATIVE 2
#define MODE_POSITIVE 4

#include "Server.h"
#include "SyncMsgConnection.h"
#include "Message.h"

#include "Chanel.h"

#include <set>

typedef SyncMsgConnection<mid_t, MSG_HEAD_BACK> BackConnection;

typedef std::set<FrontConnection*> FrontBuffer;
typedef std::set<BackConnection*> BackBuffer;

class Gate : public Object
{
public:
	Gate();
	~Gate();
public:
	void start();
	void setMode(int mode) { nMode &= mode; }
private:
	void onFrontConnect(int fd, int event,void* data);
	void onFrontClose(FrontConnection* con);
	void onBackConnect(int fd, int event, void* data);
	void onBackClose(BackConnection* con);
private:
	EventLoop* pLoop;
	Server* pFront;
	Server* pBack;
	BackConnection* pRoom;
	BackConnection* pAuth;

	FrontBuffer fBuffer;
	BackBuffer bBuffer;

	int nMode;
};

#endif