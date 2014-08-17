#ifndef _HERO_PUB_H
#define _HERO_PUB_H

#include <map>
#include "Unit.h"
#include "dwtype.h"

#define MAX_HERO_IN_PUB 30

class HeroPub
{
public:
	HeroPub();
	~HeroPub();

	void initialize();
	Unit* getHero(ID cid);
	void unlockHero(ID cid);

private:
	//Unit* mHeros[MAX_HERO_IN_PUB];
	//int numHeros;
	std::map<ID, Unit*> mHeros;
};
#endif