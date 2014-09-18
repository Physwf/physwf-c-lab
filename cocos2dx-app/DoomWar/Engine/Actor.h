#ifndef _ACTOR_H
#define _ACTOR_H

#define MAX_ACTORS_IN_MAP 50
#define X_MARGIN 36
#define GRID_SIZE 96.0
#include "ActorSprite.h"
#include "Unit.h"

class Actor : public DWObject
{
public:
	Actor(CCSprite* layer);
	~Actor();

public:
	void setData(Unit* data, bool bHero=false);
	Unit* getData();

	void updatePosition();
	void calculateNextPosition();
	void updateHealth(int delta);
	void moveTo();

	void attack();
	void shake(float delta);

	ID iid() const;
	int health() const;
	bool isHero();

	CCPoint* position();

	CCSprite* sprite() const;

	void hideBlood();
	void showBlood();
private:
	CCSprite* mLayer;
	ActorSprite* mSprite;
	Unit* mData;
	CCPoint* mPosition;
	bool mIsHero;
};
#endif