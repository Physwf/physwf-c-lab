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
	u->attackRange.numGrids = n;
	u->skill.cid = cid;
	u->skill.type = SKILL_TYPE_HARM_PHYSICAL;
	u->skill.value = -40;
	return u;
}

void HeroConfig::onHeroConfigLoaded(xmlNodePtr root)
{
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Unit* unit = new Unit();
			constructWithXML(unit, child);
			mHeros[unit->cid] = unit;
		}
		child = child->next;
	}
}

void HeroConfig::constructWithXML(Unit* hero, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szlevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szMaxHealth = xmlGetProp(node, BAD_CAST"maxHealth");
	xmlChar* szAgility = xmlGetProp(node, BAD_CAST"agility");

	hero->cid = atoi((const char*)szid);
	hero->name = (char*)szname;
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

void BarrierConfig::onBarrierConfigLoaded(xmlNodePtr root)
{

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
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			u->attackRange.offsets[n].x = i;
			u->attackRange.offsets[n].y = j;
			n++;
		}
	}
	u->skill.cid = cid;
	u->skill.type = SKILL_TYPE_HARM_PHYSICAL;
	u->skill.value = -20;
	return u;
}


void MonsterConfig::onMonsterConfigLoaded(xmlNodePtr root)
{

}
