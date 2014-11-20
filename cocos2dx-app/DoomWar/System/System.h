#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Battle.h"
#include "HeroPub.h"
#include "Bag.h"

class System
{
public:
	static PVEBattle* pve;
	static HeroPub *pub;
	static Bag *bag;
};
#endif