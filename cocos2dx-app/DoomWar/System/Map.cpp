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

}

int PVEMap::getBarriersByRow(int row, Unit* barriers)
{

}

int PVEMap::getEnemysByRow(int row, Unit* enemys)
{

}