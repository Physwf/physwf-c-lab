#include "Config.h"
#include <time.h>

HeroConfig* Config::hero = new HeroConfig();
BarrierConfig* Config::barrier = new BarrierConfig();
MonsterConfig* Config::monster = new MonsterConfig();

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

Unit* BarrierConfig::create(ID cid)
{
	ID iid = (ID)time(NULL);
	Unit* u = new Unit();
	u->iid = iid;
	u->cid = cid;
	u->name = "Barrier";
	u->maxHealth = 100;
	u->health = 100;
	return u;
}




Unit* MonsterConfig::create(ID cid)
{
	ID iid = (ID)time(NULL);
	Unit* u = new Unit();
	u->iid = iid;
	u->cid = cid;
	u->name = "Monster";
	u->maxHealth = 100;
	u->health = 100;
	return u;
}
