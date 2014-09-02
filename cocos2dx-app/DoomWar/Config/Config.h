#ifndef _CONFIG_H
#define _CONFIG_H

#include "Unit.h"
#include "dwtype.h"
#include <libxml\parser.h>

class HeroConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onHeroConfigLoaded(xmlNodePtr root);
private:

};

class BarrierConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onBarrierConfigLoaded(xmlNodePtr root);
private:
};

class MonsterConfig : public DWObject
{
public:
	Unit* create(ID cid);
	void onMonsterConfigLoaded(xmlNodePtr root);
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