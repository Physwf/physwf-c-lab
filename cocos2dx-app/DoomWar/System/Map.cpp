#include "Map.h"
#include "Config.h"
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
	memset(mEnemys, 0, sizeof(mEnemys));
	mBrriers[38] = 2;
	mBrriers[39] = 2;
	mEnemys[43] = 3;
	mEnemys[44] = 3;
}

int PVEMap::getBarriersByRow(int row, std::map<ID, Unit*>* barriers)
{
	int start = row * NUM_GRIDS_ROW;
	int end = start + NUM_GRIDS_ROW;
	int count = 0;
	for (int i = start; i < end; i++)
	{
		if (mBrriers[i])
		{
			Unit* barrier = Config::barrier->create(mBrriers[i]);
			barrier->positon.x = i - start;
			barrier->positon.y = row;
			(*barriers)[barrier->iid] = barrier;
			count++;
		}
	}
	return count;
}

int PVEMap::getEnemysByRow(int row, std::map<ID, Unit*>* enemies)
{
	int start = row * NUM_GRIDS_ROW;
	int end = start + NUM_GRIDS_ROW;
	int count = 0;
	for (int i = start; i < end; i++)
	{
		if (mEnemys[i])
		{
			Unit* monster = Config::monster->create(mEnemys[i]);
			monster->positon.x = i - start;
			monster->positon.y = row;
			(*enemies)[monster->iid] = monster;
			count++;
		}
	}
	return count;
}