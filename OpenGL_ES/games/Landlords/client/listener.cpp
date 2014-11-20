#include <string.h>
#include <map>

#include <log/Log.h>

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
	memset(&head,0,sizeof(MsgHead));
	if(conn.readBufAvaliable >= HEAD_LENGTH)
	{
		EnterCriticalSection(&CS);
		memcpy(&head,conn.readBuffer,HEAD_LENGTH);
		Log::info("sizeof MsgHead:%d",sizeof(MsgHead));
		Log::info("conn.readBufAvaliable:%d",conn.readBufAvaliable);
		Log::info("HEAD_LENGTH:%d",HEAD_LENGTH);
		Log::info("head.length:%d",head.length);
		if(conn.readBufAvaliable >= head.length)
		{
			memcpy(buffer,conn.readBuffer+HEAD_LENGTH,head.length-HEAD_LENGTH);
			conn.readBufAvaliable -= head.length;
			memcpy(conn.readBuffer,conn.readBuffer+head.length,conn.readBufAvaliable);
			dispatchMsg(head.msgid,buffer);
			Log::info("msg recv");
		}
		LeaveCriticalSection(&CS);
	}
}