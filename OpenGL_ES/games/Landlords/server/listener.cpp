#include "listener.h"



std::queue<MsgBase*> msgqueue;
std::map<int,MsgListener> listeners;

void addMsgListener(int msgid, MsgListener listener)
{
	listeners[msgid] = listener;
}

void dispatchMsg(MsgBase* msg)
{
	int msgid = msg->msgid;
	MsgListener listener = listeners[msgid];
	if(listener != NULL)
	{
		listener(msg);
	}
}

void listener_loop()
{
	while(msgqueue.size())
	{
		MsgBase* msg = msgqueue.front();
		msgqueue.pop();
		dispatchMsg(msg);
	}
}
