#include "Config.h"
#include <time.h>
#include "cocos2d.h"

HeroConfig* Config::hero = new HeroConfig();
BarrierConfig* Config::barrier = new BarrierConfig();
MonsterConfig* Config::monster = new MonsterConfig();
SkillConfig* Config::skill = new SkillConfig();

Unit* HeroConfig::create(ID cid)
{
	Unit *copy = new Unit();
	Unit *master = mMaster[cid];
	memcpy(copy, master, sizeof Unit);
	copy->iid = (ID)copy;

	copy->skill.cid = cid;
	copy->skill.type = SKILL_TYPE_HARM_PHYSICAL;
	copy->skill.value = -40;

	return copy;

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
			constructUnitWithXML(unit, child);
			mMaster[unit->cid] = unit;
		}
		child = child->next;
	}
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
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Unit* unit = new Unit();
			constructUnitWithXML(unit, child);
			mMaster[unit->cid] = unit;
		}
		child = child->next;
	}
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
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Unit* unit = new Unit();
			constructUnitWithXML(unit, child);
			mMaster[unit->cid] = unit;
		}
		child = child->next;
	}
}

void SkillConfig::onSkillConfigLoaded(xmlNodePtr root)
{
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Skill* skill = new Skill();
			constructSkillWithXML(skill, child);
			mMaster[skill->cid] = skill;
		}
		child = child->next;
	}
}

void Config::constructUnitWithXML(Unit* unit, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szlevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szMaxHealth = xmlGetProp(node, BAD_CAST"maxHealth");
	xmlChar* szAgility = xmlGetProp(node, BAD_CAST"agility");
	xmlChar* szAttackRange = xmlGetProp(node, BAD_CAST"attackRange");

	unit->cid = atoi((const char*)szid);
	unit->name = (char*)szname;

	parseRange(unit, szAttackRange);
}

void Config::parseRange(Unit* unit, xmlChar* szRange)
{
	char* coord = strtok((char*)szRange, ",;");
	int count = 0;
	while (coord != NULL)
	{
		int dir = count % 2;
		int index = count / 2;
		if (dir == 0) unit->attackRange.offsets[index].x = atoi(coord);
		else unit->attackRange.offsets[index].y = atoi(coord);
		count++;
		coord = strtok(NULL, ",;");
	}
	CCAssert(count % 2 == 0, "Must be even!");
	unit->attackRange.numGrids = count / 2;
}

void Config::constructSkillWithXML(Skill* skill, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");

	skill->cid = atoi((const char*)szid);
	skill->name = (char*)szname;
}
