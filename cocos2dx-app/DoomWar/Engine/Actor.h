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
	Actor(CCSprite* layer);
	~Actor();

public:
	void setData(Unit* data);

	void updatePosition();
	void updateHealth(int health);
	void moveTo();

	void attack();
	void shake(float delta);

	ID iid() const;
	int health() const;

	CCPoint* position();
private:
	CCSprite* mLayer;
	ActorSprite* mSprite;
	Unit* mData;
	CCPoint* mPosition;
};
#endif