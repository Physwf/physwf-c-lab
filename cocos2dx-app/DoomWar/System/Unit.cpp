#include "Unit.h"

UnitWraper::UnitWraper(Unit* unit)
{
	mUnit = unit;
}

int UnitWraper::value()const
{
	return (int)mUnit->agility;
}

Unit* UnitWraper::unit() const
{
	return mUnit;
}