#include "Map.h"
#include <string.h>

PVEMap::PVEMap()
{
	memset(mGrids, 0, sizeof(mGrids));
	memset(mBrriers, 0, sizeof(mBrriers));
}

PVEMap::~PVEMap()
{

}

int PVEMap::getGridsByRow(int row, char* girds)
{
	return 0;
}

int PVEMap::getBarriersByRow(int row, Unit* barriers)
{
	return 0;
}

int PVEMap::getEnemysByRow(int row, Unit* enemys)
{
	return 0;
}