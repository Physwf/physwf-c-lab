#ifndef _CONFIG_H
#define _CONFIG_H

#include "Unit.h"
#include "dwtype.h"
#include <map>
#include <libxml\parser.h>
#include <libxml\tree.h>

class HeroConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onHeroConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mHeros;
};

class BarrierConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onBarrierConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mBarriers;
};

class MonsterConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onMonsterConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mMonsters;
};
class Config
{
public:
	typedef void(DWObject::*OnConfigLoaded)(xmlNodePtr root);
public:
	static HeroConfig* hero;
	static BarrierConfig* barrier;
	static MonsterConfig* monster;
};


#endif