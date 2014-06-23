#include <string.h>
#include <map>

#include "listener.h"
#include "../shared/common.h"
#include "../shared/msg.h"

char buffer[1024];
std::map<int,MsgListener> listeners;

MsgHead head;

void addMsgListener(int msgid, MsgListener listener)
{
	listeners[msgid] = listener;
}

void dispatchMsg(unsigned short mid, char* msg)
{
	MsgListener listener = listeners[mid];
	if(listener != NULL)
	{
		listener(msg);
	}
}

void listener_loop()
{
	if(conn.readBufAvaliable > HEAD_LENGTH)
	{
		EnterCriticalSection(&CS);
		memcpy(&head,conn.readBuffer,HEAD_LENGTH);
		if(conn.readBufAvaliable > head.length)
		{
			memcpy(buffer,conn.readBuffer,head.length);
			conn.readBufAvaliable -= head.length;
			memcpy(conn.readBuffer,conn.readBuffer+head.length,conn.readBufAvaliable);
			dispatchMsg(head.msgid,buffer);
		}
		LeaveCriticalSection(&CS);
	}
}