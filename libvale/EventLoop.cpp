#include "EventLoop.h"

EventLoop::EventLoop() :nSize(10240), bRuning(false), nMaxfd(-1)
{
	pEvents = (IOEvent*)malloc(sizeof(IOEvent) * nSize);
	pFireds = (IOFired*)malloc(sizeof(IOFired) * nSize);
	for (int i = 0; i < nSize; i++)
	{
		pEvents->mask = EV_IO_NONE;
	}

	pPoll = new EventSelect(this);
}

EventLoop::~EventLoop()
{
	free(pFireds);
	free(pEvents);
	delete pPoll;
}

void EventLoop::run()
{
	bRuning = true;
	while (bRuning)
	{
		procIOEvent();
	}
}

void EventLoop::stop()
{
	bRuning = false;
}

void EventLoop::addEventListener(int fd, int event, const IOEventHandler &cb, void* data)
{
	if (fd > nSize)
	{
		//to do
	}
	IOEvent *ev = pEvents + fd;
	pPoll->add(fd, event);
	ev->mask |= event;
	ev->data = data;
	if (event & EV_IO_READ) ev->cbRead = cb;
	if (event & EV_IO_WRITE) ev->cbWrite = cb;
	if (fd > nMaxfd) nMaxfd = fd;
}

void EventLoop::removeEventListener(int fd, int event)
{
	if (fd > nSize) return;
	IOEvent* ev = pEvents + fd;
	if (ev->mask == EV_IO_NONE) return;
	ev->mask &= (~event);
	pPoll->del(fd,event);
}

int EventLoop::procIOEvent()
{
	int numEvent = pPoll->poll();
	int processed = 0;
	for (int j = 0; j < numEvent; j++)
	{
		int mask = pFireds[j].mask;
		int fd = pFireds[j].fd;
		IOEvent* ev = pEvents + j;
		if (ev->mask & mask & EV_IO_READ)
			EV_INVOKE(ev->cbRead, fd, mask, ev->data);
		if (ev->mask & mask & EV_IO_WRITE)
			EV_INVOKE(ev->cbWrite, fd, mask, ev->data);
		processed++;
	}
	return processed;
}
