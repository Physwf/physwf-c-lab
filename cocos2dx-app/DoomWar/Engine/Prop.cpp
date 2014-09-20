#include "Prop.h"

Prop::Prop(CCSprite* layer)
{
	mLayer = layer;
	mPosition = new CCPoint();
}

Prop::~Prop()
{

}

void Prop::bindData(Item* item)
{
	mData = item;
	mSprite = PropSprite::create(item->cid);
	updatePosition();
	mLayer->addChild(mSprite);
}

void Prop::calculateNextPosition()
{
	mPosition->x = mData->position.x * GRID_SIZE + X_MARGIN + GRID_SIZE / 2;
	mPosition->y = mData->position.y * GRID_SIZE + GRID_SIZE / 2;
}

void Prop::updatePosition()
{
	calculateNextPosition();
	mSprite->setPosition(*mPosition);
}

PropSprite* Prop::sprite() const
{
	return mSprite;
}