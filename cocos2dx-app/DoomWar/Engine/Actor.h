#ifndef _ACTOR_H
#define _ACTOR_H

#define MAX_ACTORS_IN_MAP 50
#define X_MARGIN 36
#define GRID_SIZE 96
#include "ActorSprite.h"
#include "Unit.h"

class Actor
{
public:
	Actor(CCLayer* layer);
	~Actor();

public:
	void setData(Unit* data);

	void updatePosition();
	void moveTo();

	void attack();

	ID iid() const;

private:
	CCLayer* mLayer;
	ActorSprite* mSprite;
	Unit* mData;
};
#endif