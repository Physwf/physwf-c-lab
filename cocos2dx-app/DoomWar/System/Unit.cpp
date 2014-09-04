#include "Unit.h"

UnitWraper::UnitWraper(Unit* unit)
{
	mUnit = unit;
}

UnitWraper::~UnitWraper()
{
	
}

int UnitWraper::value()const
{
	return (int)mUnit->agility;
}

Unit* UnitWraper::unit() const
{
	return mUnit;
}

void constructUnitWithXML(Unit* unit, xmlNodePtr node)
{
	xmlChar* szid = xmlGetProp(node, BAD_CAST"id");
	xmlChar* szname = xmlGetProp(node, BAD_CAST"name");
	xmlChar* szlevel = xmlGetProp(node, BAD_CAST"level");
	xmlChar* szMaxHealth = xmlGetProp(node, BAD_CAST"maxHealth");
	xmlChar* szAgility = xmlGetProp(node, BAD_CAST"agility");

	unit->cid = atoi((const char*)szid);
	unit->name = (char*)szname;
}