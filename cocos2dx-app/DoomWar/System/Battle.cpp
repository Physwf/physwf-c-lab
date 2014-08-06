#include "Battle.h"
#include <string.h>

PVEBattle::PVEBattle()
{
	memset(mHeros, 0, sizeof(mHeros));
	mNumHeros = 0;
	memset(mEnemys, 0, sizeof(mEnemys));
	mNumEnemys = 0;
	memset(mBarriers, 0, sizeof(mBarriers));
	mNumBarries = 0;
	memset(mGrids, 0, sizeof(mGrids));

	mRound = 0;
	mStarLevel = MAX_STAR_LEVEL;
	mGolds = 0;
	mFrontRow = 0;
}

PVEBattle::~PVEBattle()
{

}

void PVEBattle::initialize(Unit* heros, int numHeros, PVEMap* map)
{
	memcpy(mHeros, heros, numHeros*sizeof(Unit));
	mNumHeros = numHeros;

	mMap = map;
	mFrontRow = MAX_SCREEN_GRID / NUM_GRIDS_ROW;
}

void PVEBattle::start()
{

}

void PVEBattle::pause()
{

}

void PVEBattle::refresh()
{

}

void PVEBattle::end()
{

}

void PVEBattle::step()
{
	mFrontRow++;
	//grids
	memcpy(mGrids + NUM_GRIDS_ROW, mGrids, MAX_SCREEN_GRID*sizeof(char));
	mMap->getGridsByRow(mFrontRow, mGrids);
	//barriers
	int numAdd = mMap->getBarriersByRow(mFrontRow,mBarriers + mNumBarries);
	mNumBarries += numAdd;
	//enemys
	numAdd = mMap->getEnemysByRow(mNumEnemys, mEnemys + mNumEnemys);
	mNumEnemys += numAdd;

	checkEncounter();
}

void PVEBattle::update(unsigned int eclipse)
{

}

void PVEBattle::checkEncounter()
{

}
