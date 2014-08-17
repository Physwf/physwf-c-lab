#include "Map.h"
#include <string.h>

PVEMap::PVEMap()
{
	
}

PVEMap::~PVEMap()
{

}

ID PVEMap::cid() const
{
	return mCID;
}

void PVEMap::init(const char* configFile)
{
	memset(mGrids, 0, sizeof(mGrids));
	memset(mBrriers, 0, sizeof(mBrriers));
}

int PVEMap::getGridsByRow(int row, char* girds)
{
	return 0;
}

int PVEMap::getBarriersByRow(int row, std::map<ID, Unit*>*)
{
	return 0;
}

int PVEMap::getEnemysByRow(int row, std::map<ID, Unit*>*)
{
	return 0;
}