#include "Config.h"
#include <time.h>

HeroConfig* Config::hero = new HeroConfig();
BarrierConfig* Config::barrier = new BarrierConfig();
MonsterConfig* Config::monster = new MonsterConfig();

Unit* HeroConfig::create(ID cid)
{
	Unit* u = new Unit();
	u->iid = (ID)u;
	u->cid = cid;
	u->name = "Hero";
	u->maxHealth = 100;
	u->health = 100;
	u->attackRange.numGrids = 8;
	int n = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j==0 ) continue;
			u->attackRange.offsets[n].x = i;
			u->attackRange.offsets[n].y = j;
			n++;
		}
	}
	u->skill.type = SKILL_TYPE_HARM_PHYSICAL;
	u->skill.value = -40;
	return u;
}

Unit* BarrierConfig::create(ID cid)
{
	Unit* u = new Unit();
	u->iid = (ID)u;
	u->cid = cid;
	u->name = "Barrier";
	u->maxHealth = 100;
	u->health = 100;
	return u;
}


Unit* MonsterConfig::create(ID cid)
{
	Unit* u = new Unit();
	u->iid = (ID)u;
	u->cid = cid;
	u->name = "Monster";
	u->maxHealth = 100;
	u->health = 100;

	u->attackRange.numGrids = 8;
	int n = 0;
	for (int i = -1; i < 1; i++)
	{
		for (int j = -1; j < 1; j++)
		{
			if (i == j) continue;
			u->attackRange.offsets[n++].x = i;
			u->attackRange.offsets[n++].y = j;
		}
	}
	u->skill.type = SKILL_TYPE_HARM_PHYSICAL;
	u->skill.value = -20;
	return u;
}
