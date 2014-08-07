#ifndef _EVENTDISPATCHER_H
#define _EVENTDISPATCHER_H

#define MAX_LISTENER_CAPACITY 20
#include <map>
#include <vector>

#include "Heap.h"

typedef char* EType;

typedef struct event_t
{
	EType type;
	char* data;
} Event;

typedef void(*EventListener)(Event*);

/*Wraper used to wrap listener*/
class ListenerWraper : public IPriority
{
public:
	ListenerWraper(int priority, EventListener listener);
	~ListenerWraper();

	virtual int value() const;
	EventListener listener() const;
private:
	ListenerWraper();
	
private:
	int mPriority;
	EventListener mListerner;
};

class EventDispather
{
public:
	EventDispather();
	~EventDispather();

	virtual void addEventListener(EType type, EventListener listener, int priority=0);
	virtual void removeEventListener(EType type, EventListener listener);
	virtual void dispatchEvent(Event* event);
protected:
	std::map<EType, std::vector<ListenerWraper*>*> mListeners;

};
#endif