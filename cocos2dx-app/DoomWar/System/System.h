#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Battle.h"
#include "HeroPub.h"

class System
{
public:
	static PVEBattle* pve;
	static HeroPub *pub;
};
#endif