#include "Bag.h"

Bag::Bag()
{

}

Bag::~Bag()
{

}

void Bag::addItem(Item* item)
{
	mItems[item->iid] = item;
}

void Bag::useItem(ID iid)
{
	std::map<ID, Item*>::iterator it = mItems.find(iid);
	if (it != mItems.end())
	{
		Item* item = it->second;
	}
}

void Bag::destroyItem(ID iid)
{

}

int Bag::addGold(int gold)
{
	mGold += gold;
	return mGold;
}

int Bag::getGold() const
{
	return mGold;
}