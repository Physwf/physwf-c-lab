#ifndef _EVENTDISPATCHER_H
#define _EVENTDISPATCHER_H

#define MAX_LISTENER_CAPACITY 20
#include <map>
#include <vector>

#include "dwtype.h"
#include "Heap.h"

typedef char* EType;

typedef struct event_t
{
	EType type;
	char* data;
} Event;


typedef void(DWObject::*EventListener)(Event*);

/*Wraper used to wrap listener*/
class ListenerWraper : public IPriority
{
public:
	ListenerWraper(int priority, DWObject*object, EventListener listener);
	~ListenerWraper();

	virtual int value() const;
	void call(Event* event);
	bool isWrap(EventListener listener);
private:
	ListenerWraper();

private:
	int mPriority;
	DWObject* mObject;
	EventListener mListerner;
};

class EventDispather
{
public:
	EventDispather();
	~EventDispather();

	virtual void addEventListener(EType type, DWObject* object, EventListener listener, int priority = 0);
	virtual void removeEventListener(EType type, EventListener listener);
	virtual void dispatchEvent(Event* event);
protected:
	std::map<EType, std::vector<ListenerWraper*>*> mListeners;

};




#endif