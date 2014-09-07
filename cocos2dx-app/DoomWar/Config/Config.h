#ifndef _CONFIG_H
#define _CONFIG_H

#include "Unit.h"
#include "dwtype.h"
#include <map>
#include <libxml\parser.h>
#include <libxml\tree.h>

class HeroConfig;
class BarrierConfig;
class MonsterConfig;
class SkillConfig;

class Config : public DWObject
{
public:
	typedef void(DWObject::*OnConfigLoaded)(xmlNodePtr root);
public:
	static HeroConfig* hero;
	static BarrierConfig* barrier;
	static MonsterConfig* monster;
	static SkillConfig* skill;
protected:
	void constructUnitWithXML(Unit* unit, xmlNodePtr node);
	void parseRange(Unit* unit, xmlChar* szRange);
	void constructSkillWithXML(Skill* monster, xmlNodePtr node);
};

class HeroConfig : public Config
{
public:
	Unit* create(ID cid);
	void onHeroConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mMaster;
};

class BarrierConfig : public Config
{
public:
	Unit* create(ID cid);
	void onBarrierConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mMaster;
};

class MonsterConfig : public Config
{
public:
	Unit* create(ID cid);
	void onMonsterConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Unit*> mMaster;
};

class SkillConfig : public Config
{
public:
	void fill(Skill* skill,ID cid);
	void onSkillConfigLoaded(xmlNodePtr root);
private:
	std::map<ID, Skill*> mMaster;
};




#endif