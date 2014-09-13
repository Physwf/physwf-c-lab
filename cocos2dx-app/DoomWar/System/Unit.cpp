#include "Unit.h"

UnitWraper::UnitWraper(Unit* unit)
{
	mUnit = unit;
	mValue = unit->agility;
}

UnitWraper::UnitWraper(Unit* unit, int value)
{
	mUnit = unit;
	mValue = value;
}

UnitWraper::~UnitWraper()
{
	
}

int UnitWraper::value()const
{
	return mValue;
}

Unit* UnitWraper::unit() const
{
	return mUnit;
}

