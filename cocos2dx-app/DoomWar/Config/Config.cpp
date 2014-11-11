#include "Config.h"
#include <time.h>
#include "cocos2d.h"

HeroConfig* Config::hero = new HeroConfig();
BarrierConfig* Config::barrier = new BarrierConfig();
MonsterConfig* Config::monster = new MonsterConfig();
SkillConfig* Config::skill = new SkillConfig();
ItemConfig* Config::item = new ItemConfig();

Unit* HeroConfig::create(ID cid)
{
	Unit *copy = new Unit();
	Unit *master = mMaster[cid];
	memcpy(copy, master, sizeof Unit);
	copy->iid = (ID)copy;

	return copy;
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
	Unit *copy = new Unit();
	Unit *master = mMaster[cid];
	memcpy(copy, master, sizeof Unit);
	copy->iid = (ID)copy;
	return copy;
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

	return copy;
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

void SkillConfig::fill(GSet* set, ID cid)
{
	assert(mGSet.find(cid) != mGSet.end());
	GSet* master = mGSet[cid];
	memcpy(set, master, sizeof GSet);
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

void SkillConfig::onGSetConfigLoaded(xmlNodePtr root)
{
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			GSet* set = new GSet();
			constructGSetWithXML(set, child);
			mGSet[set->cid] = set;
		}
		child = child->next;
	}
}

void SkillConfig::fill(Buff* buff, ID cid)
{
	Buff* master = mBuffs[cid];
	memcpy(buff, master, sizeof Buff);
}


Item* ItemConfig::create(ID cid)
{
	Item *copy = new Item();
	Item *master = mItems[cid];
	memcpy(copy, master, sizeof Item);
	copy->iid = (ID)copy;
	return copy;
}

void ItemConfig::onItemConfigLoaded(xmlNodePtr root)
{
	xmlNodePtr child = root->children;
	while (child)
	{
		if (child->type != XML_TEXT_NODE && child->type != XML_COMMENT_NODE && child->type != XML_DTD_NODE)
		{
			Item* item = new Item();
			constructItemWithXML(item, child);
			mItems[item->cid] = item;
		}
		child = child->next;
	}
}

void Config::constructUnitWithXML(Unit* unit, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szlevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szAI = xmlGetProp(node, BAD_CAST"ai");
	xmlChar* szAlign = xmlGetProp(node, BAD_CAST"alignment");
	xmlChar* szMaxHealth = xmlGetProp(node, BAD_CAST"maxHealth");
	xmlChar* szAgility = xmlGetProp(node, BAD_CAST"agility");
	xmlChar* szSkills = xmlGetProp(node, BAD_CAST"skills");
	xmlChar* szAttackFreq = xmlGetProp(node, BAD_CAST"attackFreq");
	xmlChar *szView = xmlGetProp(node, BAD_CAST"view");

	unit->cid = atoi((const char*)szid);
	unit->name = (char*)szname;
	unit->maxHealth = atoi((const char*)szMaxHealth);
	unit->agility = atoi((const char*)szAgility);
	unit->ai = atoi((const char*)szAI);
	unit->alignment = atoi((const char*)szAlign);

	parseSkills(unit,szSkills);
	unit->attackFreq = atoi((const char*)szAttackFreq);
	parseView(unit, szView);
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

void Config::parseGSet(GSet* set, xmlChar* szGset)
{
	char* coord = strtok((char*)szGset, ",;");
	int count = 0;
	int tempBuffer[255] = {0};
	while (coord != NULL)
	{
		tempBuffer[count] = atoi(coord);
		count++;
		coord = strtok(NULL, ",;");
	}
	Grid* eles = (Grid*)malloc(count * (sizeof(int)) );
	set->elements = eles;
	set->numElements = count;
}

void Config::parseRange(Skill* skill, xmlChar* szRange)
{
	char* coord = strtok((char*)szRange, ",;");
	int count = 0;
	while (coord != NULL)
	{
		int dir = count % 2;
		int index = count / 2;
		if (dir == 0) skill->range.offsets[index].x = atoi(coord);
		else skill->range.offsets[index].y = atoi(coord);
		count++;
		coord = strtok(NULL, ",;");
	}
	CCAssert(count % 2 == 0, "Must be even!");
	skill->range.numGrids = count / 2;
}

void Config::parseRange2(Skill* skill, xmlChar* szRange)
{
	char* id = strtok((char*)szRange, ",");
	while (id != NULL)
	{
		skill->range2.gSets[skill->range2.numGSets] = atoi(id);
		skill->range2.numGSets++;
		strtok(NULL, ",");
	}
}

void Config::parseView(Unit* unit, xmlChar* szView)
{
	char* view = strtok((char*)szView, ",");
	int rect[4] = {0};
	int count = 0;
	while (view != NULL)
	{
		rect[count++] = atoi(view);
		view = strtok(NULL, ",");
		if (count >= 4) break;
	}
	int minX = rect[0];
	int minY = rect[1];
	int maxX = rect[2];
	int maxY = rect[3];
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			if (x == 0 && y == 0) continue;
			int index = unit->view.numGrids;
			unit->view.offsets[index].x = x;
			unit->view.offsets[index].y = y;
			unit->view.numGrids++;
		}
	}
}

void Config::constructSkillWithXML(Skill* skill, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szCast = xmlGetProp(node, BAD_CAST"cast");
	xmlChar* szTrack = xmlGetProp(node, BAD_CAST"track");
	xmlChar* szAttack = xmlGetProp(node, BAD_CAST"attack");
	xmlChar* szRange = xmlGetProp(node, BAD_CAST"range");
	xmlChar* szEffect = xmlGetProp(node, BAD_CAST"effect");
	xmlChar* szMaxTarget = xmlGetProp(node, BAD_CAST"max_targets");
	xmlChar* szLevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szCondition = xmlGetProp(node, BAD_CAST"condition");
	xmlChar* szValue = xmlGetProp(node, BAD_CAST"value");
	xmlChar* szAttackFreq = xmlGetProp(node, BAD_CAST"attackFreq");

	skill->cid = atoi((const char*)szid);
	skill->name = (char*)szname;
	skill->type = atoi((const char*)szType);
	skill->cast = atoi((const char*)szCast);
	skill->track = atoi((const char*)szTrack);
	skill->attack = atoi((const char*)szAttack);
	parseRange2(skill, szRange);
	skill->effect = atoi((const char*)szEffect);
	skill->maxNumOfTargets = atoi((const char*)szMaxTarget);
	skill->level = atoi((const char*)szLevel);
	skill->condition = atoi((const char*)szCondition);
	skill->value = atoi((const char*)szValue);
}

void Config::constructBuffWithXML(Buff* buff, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szValue = xmlGetProp(node, BAD_CAST"value");
	xmlChar* szCondition = xmlGetProp(node, BAD_CAST"condition");

	buff->cid = atoi((const char*)szid);
	buff->name = (char*)szname;
	buff->type = atoi((const char*)szType);
	buff->value = atoi((const char*)szValue);
	buff->condition = atoi((const char*)szCondition);
}

void Config::constructItemWithXML(Item* item, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szPick = xmlGetProp(node, BAD_CAST"pick");
	xmlChar* szValue = xmlGetProp(node, BAD_CAST"value");

	item->cid = atoi((const char*)szid);
	item->name = (char*)szname;
	item->type = atoi((const char*)szType);
	item->pick = atoi((const char*)szPick);
	item->value = atoi((const char*)szValue);
}

void Config::constructGSetWithXML(GSet* set, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szType = xmlGetProp(node, BAD_CAST"type");
	xmlChar* szElements = xmlGetProp(node, BAD_CAST"elements");

	set->cid = atoi((const char*)szid);
	set->name = (char*)szname;
	set->type = atoi((const char*)szType);
	parseGSet(set,szElements);
}