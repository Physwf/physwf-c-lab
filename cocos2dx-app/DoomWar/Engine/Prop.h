#ifndef _PROP_H
#define _PROP_H

#define X_MARGIN 36
#define GRID_SIZE 96.0

#include "dwtype.h"
#include "Unit.h"
#include "PropSprite.h"

class Prop : public DWObject
{
public:
	Prop(CCSprite* layer);
	~Prop();

	void bindData(Item* item);

	void updatePosition();
	void calculateNextPosition();

	void show();
	void hide();

	PropSprite* sprite() const;
private:
	Item* mData;
	PropSprite* mSprite;
	CCSprite* mLayer;
	CCPoint* mPosition;
};
#endif