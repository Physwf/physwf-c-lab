#include "EventDispatcher.h"
#include <assert.h>
/*ListenerWraper*/
ListenerWraper::ListenerWraper(int priority, EventListener listener)
{
	mPriority = priority;
}

int ListenerWraper::value() const
{
	return mPriority;
}
EventListener ListenerWraper::listener() const
{
	return mListerner;
}

/*EventDispather*/
EventDispather::EventDispather()
{

}

EventDispather::~EventDispather()
{

}

void EventDispather::addEventListener(EType type, EventListener listener, int priority = 0)
{
	std::vector<ListenerWraper*>* list = mListeners[type];
	if (list == NULL)
		list = new std::vector<ListenerWraper*>();
	ListenerWraper *wraper = new ListenerWraper(priority, listener);
	std::vector<ListenerWraper*>::iterator it = list->begin();
	for (it; it<list->end(); it++)
	{
		if ((*it)->value() <= priority)
		{
			list->insert(it, wraper);
			break;
		}
	}
}

void EventDispather::removeEventListener(EType type, EventListener listener)
{
	std::vector<ListenerWraper*>* list = mListeners[type];
	if (list == NULL)
		return;
	std::vector<ListenerWraper*>::iterator it = list->begin();
	for (it; it<list->end(); it++)
	{
		if ((*it)->listener() == listener)
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
	for (it; it<list->end(); it++)
	{
		(*it)->listener()(event);
	}
}

