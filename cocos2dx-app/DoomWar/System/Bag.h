#ifndef _BAG_H
#define _BAG_H

#include "EventDispatcher.h"
#include "Unit.h"

class Bag : public EventDispather
{
public:
	Bag();
	~Bag();
public:
	void addItem(Item* item);
	void useItem(ID iid);
	void destroyItem(ID iid);
	int addGold(int gold);
	int getGold() const;
public:
	static const EType BAG_GOLD_CHANGE;
private:
	std::map<ID, Item*> mItems;
	int mGold;
};
#endif