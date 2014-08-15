#ifndef _ACTOR_H
#define _ACTOR_H

#define MAX_ACTORS_IN_MAP 50
#include "ActorSprite.h"
#include "Unit.h"

class Actor
{
public:
	Actor();
	~Actor();

public:
	void setData(Unit* data);

	void stepForword();
	void stepBackword();
	void stepLeft();
	void stepRight();
	void moveTo();

	void attack();

	unsigned int iid() const;

private:
	ActorSprite* mSprite;
	Unit* mData;
};
#endif