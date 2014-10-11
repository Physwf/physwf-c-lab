#include "Bag.h"

EType const Bag::BAG_GOLD_CHANGE = "bag_gold_change";

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
	Event e = { BAG_GOLD_CHANGE, (char*)&gold };
	dispatchEvent(&e);
	return mGold;
}

int Bag::getGold() const
{
	return mGold;
}