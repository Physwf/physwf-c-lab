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

	//Config::skill->fill(&copy->skill, copy->skill.cid);

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
	Unit *copy = new Unit();
	Unit *master = mMaster[cid];
	memcpy(copy, master, sizeof Unit);
	copy->iid = (ID)copy;

	//Config::skill->fill(&copy->skill, copy->skill.cid);

	return copy;

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
			mSkills[skill->cid] = skill;
		}
		child = child->next;
	}
}

void SkillConfig::fill(Skill* skill, ID cid)
{
	Skill* master = mSkills[cid];
	memcpy(skill, master, sizeof Skill);
}

void SkillConfig::onBuffConfigLoaded(xmlNodePtr root)
{
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Buff* buff = new Buff();
			constructBuffWithXML(buff, child);
			mBuffs[buff->cid] = buff;
		}
		child = child->next;
	}
}

void SkillConfig::fill(Buff* buff, ID cid)
{
	Buff* master = mBuffs[cid];
	memcpy(buff, master, sizeof Buff);
}

void Config::constructUnitWithXML(Unit* unit, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szlevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szMaxHealth = xmlGetProp(node, BAD_CAST"maxHealth");
	xmlChar* szAgility = xmlGetProp(node, BAD_CAST"agility");
	xmlChar* szSkills = xmlGetProp(node, BAD_CAST"skills");
	xmlChar* szAttackRange = xmlGetProp(node, BAD_CAST"attackRange");

	unit->cid = atoi((const char*)szid);
	unit->name = (char*)szname;
	unit->maxHealth = atoi((const char*)szMaxHealth);
	unit->agility = atoi((const char*)szAgility);

	parseSkills(unit,szSkills);
	parseRange(unit, szAttackRange);
}

void Config::parseSkills(Unit* unit, xmlChar* szSkills)
{
	char* skill = strtok((char*)szSkills, ",");
	int count = 0;
	while (skill != NULL)
	{
		unit->skills[count++] = atoi(skill);
		skill = strtok(NULL, ",");
	}
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
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szCast = xmlGetProp(node, BAD_CAST"cast");
	xmlChar* szTrack = xmlGetProp(node, BAD_CAST"track");
	xmlChar* szEffect = xmlGetProp(node, BAD_CAST"effect");
	xmlChar* szLevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szValue = xmlGetProp(node, BAD_CAST"value");

	skill->cid = atoi((const char*)szid);
	skill->name = (char*)szname;
	skill->type = atoi((const char*)szType);
	skill->cast = atoi((const char*)szCast);
	skill->track = atoi((const char*)szTrack);
	skill->effect = atoi((const char*)szEffect);
	skill->level = atoi((const char*)szLevel);
	skill->value = atoi((const char*)szValue);
}

void Config::constructBuffWithXML(Buff* buff, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szValue = xmlGetProp(node, BAD_CAST"value");

	buff->cid = atoi((const char*)szid);
	buff->name = (char*)szname;
	buff->type = atoi((const char*)szType);
	buff->value = atoi((const char*)szValue);
}

