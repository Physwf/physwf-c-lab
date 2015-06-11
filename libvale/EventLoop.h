#pragma once
#ifndef _EVENT_LOOP_H
#define _EVENT_LOOP_H

#include "Object.h"
#include "EventPoll.h"

#include "platform.h"

#define EV_ERROR -1
#define EV_IO_NONE 0
#define EV_IO_READ 1
#define EV_IO_WRITE 2
#define EV_IO_ALL (EV_IO_READ | EV_IO_WRITE)

#define EV_CB_INIT(_cb) _cb.object = NULL; _cb.method = NULL
#define EV_CB(_obj,_func) EventHandler{_obj,(EventCallBack)&_func}
#define EV_IO_CB(_obj,_func) IOEventHandler {_obj,(IOEventCallBack)&_func}
#define EV_INVOKE(_cb,...) do{ \
		if(_cb.object && _cb.method) {\
			(_cb.object->*_cb.method)(__VA_ARGS__);\
			}\
	}while(0)



typedef void(Object::*EventCallBack)(...);
typedef void(Object::*IOEventCallBack)(int, int, void*);

typedef struct VALE_DLL {
	Object* object;
	EventCallBack method;
} EventHandler;

typedef struct VALE_DLL {
	Object* object;
	IOEventCallBack method;
} IOEventHandler;

typedef struct VALE_DLL {
	int mask;
	void *data;
	IOEventHandler cbRead;
	IOEventHandler cbWrite;
} IOEvent;

typedef struct VALE_DLL {
	int fd;
	int mask;
} IOFired;

class VALE_DLL EventLoop : public Object
{
public:
	friend class EventSelect;
	EventLoop();
	~EventLoop();
public:
	void run();
	void stop();
	void addEventListener(int fd, int event, const IOEventHandler &cb, void* data);
	void removeEventListener(int fd, int event);
private:
	int procIOEvent();
private:
	int nSize;
	int nMaxfd;
	bool bRuning;
	IEventPoll* pPoll;
	IOEvent* pEvents;
	IOFired* pFireds;
};
#endif
