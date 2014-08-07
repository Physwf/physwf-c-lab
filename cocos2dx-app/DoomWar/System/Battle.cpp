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

	if (checkEncounter())
	{
		calculateRoundResult();
	}
	else
	{
		Event e = { BATTLE_STEP_CLEAR, NULL};
		dispatchEvent(&e);
	}
}

void PVEBattle::update(unsigned int eclipse)
{

}

bool PVEBattle::checkEncounter()
{

}

void PVEBattle::calculateRoundResult()
{
	//step 1, check blood recover, buff/debuff status 
	//step 2, check props in occupied grids
	//step 3, check active enemys and move them if hero(s) be seen (in enemys view)
	//step 4, heros round, attack enemys in aligity order.
	MaxHeap heros = MaxHeap(mNumHeros);
	for (int i = 0; i < mNumHeros; i++)
	{
		UnitWraper wraper = UnitWraper(&mHeros[i]);
		heros.Enqueue(&wraper);
	}
	while (heros.size())
	{
		UnitWraper *wraper = (UnitWraper*)heros.Dequeue();
		Unit* hero = wraper->unit();
		Range aRange = hero->attackRange;
	}

	//step 5, enemys round, attack heros in aligity order

	//send battle result
}

bool PVEBattle::isInAttackRange(Unit* attacker, Unit* victim)
{
	//first, check if in attack grids
	bool in = false;
	for (int i = 0; i < attacker->attackRange.numGrids; i++)
	{
		if (attacker->attackRange.offsets[i].x + attacker->positon.x == victim->positon.x &&
			attacker->attackRange.offsets[i].y + attacker->positon.y == victim->positon.y)
			in = true;
	}
	if (!in) return false;

	//second, check if be blocked
}

