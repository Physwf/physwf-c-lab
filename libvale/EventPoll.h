#ifndef _EVENT_POLL_H
#define _EVENT_POLL_H

#include "Socket.h"

class EventLoop;

class IEventPoll
{
public:
	IEventPoll(EventLoop* loop) :pLoop(loop) { }
	~IEventPoll() {}
public:
	virtual void add(int fd, int mask) = 0;
	virtual void del(int fd, int mask) = 0;
	virtual int poll() = 0;
protected:
	EventLoop* pLoop;
};


class EventSelect : public IEventPoll
{
public:
	EventSelect(EventLoop* loop);
	~EventSelect() {};
public:
	virtual void add(int fd, int mask);
	virtual void del(int fd, int mask);
	virtual int poll();
private:
	fd_set rfds;
	fd_set wfds;
	fd_set _rfds;
	fd_set _wfds;
};
#endif