#include "Config.h"
#include <time.h>

HeroConfig* Config::hero = new HeroConfig();

Unit* HeroConfig::create(ID cid)
{
	ID iid = (ID)time(NULL);
	Unit* u = new Unit();
	u->iid = iid;
	u->cid = cid;
	u->name = "Hero";
	u->maxHealth = 100;
	u->health = 100;
	return u;
}
