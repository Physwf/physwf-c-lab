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
	//mBrriers[38] = 2;
	//mBrriers[39] = 2;
	mEnemys[43] = 2001;
	mEnemys[44] = 2001;

	mEnemys[50] = 2001;
	mEnemys[54] = 2001;

	mEnemys[61] = 2001;
	mEnemys[62] = 2001;

	mEnemys[75] = 2001;
	mEnemys[78] = 2001;

	mEnemys[85] = 2001;
	mEnemys[88] = 2001;

	mEnemys[95] = 2001;
	mEnemys[98] = 2001;

	mEnemys[105] = 2001;
	mEnemys[108] = 2001;

	mEnemys[115] = 2001;
	mEnemys[118] = 2001;

	mEnemys[125] = 2001;
	mEnemys[128] = 2001;

	mEnemys[135] = 2001;
	mEnemys[138] = 2001;
}

int PVEMap::getBarriersByRow(int row, std::map<ID, Unit*>* barriers, ID* iids)
{
	int start = row * NUM_GRIDS_ROW;
	int end = start + NUM_GRIDS_ROW;
	int count = 0;
	for (int i = start; i < end; i++)
	{
		if (mBarriers[i])
		{
			Unit* barrier = Config::barrier->create(mBarriers[i]);
			barrier->positon.x = i - start;
			barrier->positon.y = row;
			(*barriers)[barrier->iid] = barrier;
			iids[count] = barrier->iid;
			mBarriers.erase(mBarriers.find(i));
			count++;
		}
	}
	return count;
}

int PVEMap::getEnemysByRow(int row, std::map<ID, Unit*>* enemies, ID* iids)
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
			monster->health = monster->maxHealth;
			(*enemies)[monster->iid] = monster;
			iids[count] = monster->iid;
			mEnemys.erase(mEnemys.find(i));
			count++;
		}
	}
	return count;
}