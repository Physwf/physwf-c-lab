#ifndef _ACTOR_H
#define _ACTOR_H

#define MAX_ACTORS_IN_MAP 50
#include "ActorSprite.h"
#include "Unit.h"

class Actor
{
public:
	Actor(CCLayer* layer);
	~Actor();

public:
	void setData(Unit* data);

	void stepForword();
	void stepBackword();
	void stepLeft();
	void stepRight();
	void moveTo();

	void attack();

	ID iid() const;

private:
	CCLayer* mLayer;
	ActorSprite* mSprite;
	Unit* mData;
};
#endif