#include "EventDispatcher.h"
#include <assert.h>
/*ListenerWraper*/
ListenerWraper::ListenerWraper(int priority, DWObject*object, EventListener listener)
{
	mPriority = priority;
	mObject = object;
	mListerner = listener;
}

int ListenerWraper::value() const
{
	return mPriority;
}

void ListenerWraper::call(Event* event)
{
	(mObject->*mListerner)(event);
}

bool ListenerWraper::isWrap(EventListener listener)
{
	return mListerner == listener;
}

/*EventDispather*/
EventDispather::EventDispather()
{

}

EventDispather::~EventDispather()
{

}

void EventDispather::addEventListener(EType type, DWObject* object, EventListener listener, int priority)
{
	std::vector<ListenerWraper*>* list = mListeners[type];
	if (list == NULL)
		mListeners[type] = list = new std::vector<ListenerWraper*>();
	ListenerWraper *wraper = new ListenerWraper(priority, object, listener);
	std::vector<ListenerWraper*>::iterator it = list->begin();
	for (it; it!=list->end(); it++)
	{
		if ((*it)->value() <= priority)
		{
			list->insert(it, wraper);
			break;
		}
	}
	if (it == list->end()) list->insert(it, wraper);
}

void EventDispather::removeEventListener(EType type, EventListener listener)
{
	std::vector<ListenerWraper*>* list = mListeners[type];
	if (list == NULL)
		return;
	std::vector<ListenerWraper*>::iterator it = list->begin();
	for (it; it<list->end(); it++)
	{
		if ((*it)->isWrap(listener))
		{
			list->erase(it);
			break;
		}
	}
}

void EventDispather::dispatchEvent(Event* event)
{
	EType type = event->type;
	std::vector<ListenerWraper*>* list = mListeners[type];
	if (list == NULL)
		return;
	std::vector<ListenerWraper*>::iterator it = list->begin();
	for (it; it != list->end(); it++)
	{
		(*it)->call(event);
	}
}

