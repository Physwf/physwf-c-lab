#include "Battle.h"
#include <string.h>
#include "dwtype.h"

PVEBattle::PVEBattle()
{
	mMap = new PVEMap();
	mHeros = new std::map<ID, Unit*>();
	mEnemys = new std::map<ID, Unit*>();
	mBarriers = new std::map<ID, Unit*>();

	
}

PVEBattle::~PVEBattle()
{

}

EType const PVEBattle::BATTLE_ENTER_MAP = "battle_enter_map";
EType const PVEBattle::BATTLE_STEP_CLEAR = "battle_step_clear";
EType const PVEBattle::BATTLE_MOVE_SUCCESS = "battle_move_success";
EType const PVEBattle::BATTLE_MOVE_FAILED = "battle_move_failed";
EType const PVEBattle::BATTLE_ATTACK_RESULT = "battle_attack_result";

void PVEBattle::initialize()
{
	/*memset(mHeros, 0, sizeof(mHeros));
	mNumHeros = 0;
	memset(mEnemys, 0, sizeof(mEnemys));
	mNumEnemys = 0;
	memset(mBarriers, 0, sizeof(mBarriers));
	mNumBarries = 0;*/
	memset(mGrids, 0, sizeof(mGrids));

	mHeros->clear();
	mEnemys->clear();
	mBarriers->clear();

	mRound = 0;
	mStarLevel = MAX_STAR_LEVEL;
	mGolds = 0;
	
}

void PVEBattle::enter(ID mapid, Unit* heros, int numHeros)
{
	mMap->init("");

	for (int i = 0; i < numHeros; i++)
	{
		Unit* hero = heros + i;
		(*mHeros)[hero->iid] = hero;
		hero->positon.x = 3;
		hero->positon.y = 2;
	}
	mFrontLine = MAX_SCREEN_GRID / NUM_GRIDS_ROW - 1;
	mBackLine = 0;

	for (int row = mBackLine; row < mFrontLine; row++)
	{
		mMap->getEnemysByRow(row, mEnemys);
		mMap->getBarriersByRow(row, mBarriers);
	}

	refreshGrids();

	Event e = { BATTLE_ENTER_MAP, NULL };
	dispatchEvent(&e);
}

void PVEBattle::start()
{
	//to do, count time
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

void PVEBattle::step(StepDirection dir)
{
	if (!calculateHerosMovement(dir)) return;

	//mFrontLine++;
	//mBackLine++;
	//barriers
	mMap->getBarriersByRow(mFrontLine, mBarriers);
	//enemys
	mMap->getEnemysByRow(mFrontLine, mEnemys);

	calculateRoundResult();
}

void PVEBattle::refreshGrids()
{
	memset(mGrids, 0, sizeof(mGrids));

	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it != mHeros->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		mGrids[index] = GRID_OCCUPY_TYPE_HERO;
	}

	it = mEnemys->begin();
	for (it; it != mEnemys->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		mGrids[index] = GRID_OCCUPY_TYPE_ENEMY;
	}

	it = mBarriers->begin();
	for (it; it != mBarriers->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		mGrids[index] = GRID_OCCUPY_TYPE_BARRIER;
	}
}

void PVEBattle::update(unsigned int eclipse)
{

}

bool PVEBattle::calculateHerosMovement(StepDirection dir)
{
	char gridsCopy[MAX_SCREEN_GRID];
	memcpy(gridsCopy, mGrids, sizeof(mGrids));
	int stepLen = 1;
	ID* heroToMove = new ID[MAX_SCREEN_HEROS];
	int numHeroToMove = 0;
	int nextGrids[MAX_SCREEN_HEROS] = {0};
	memset(heroToMove, 0, sizeof(Unit*)*MAX_SCREEN_HEROS);
	ID* heroCantMove = new ID[MAX_SCREEN_HEROS];
	int numHeroCantMove = 0;
	memset(heroCantMove, 0, sizeof(Unit*)*MAX_SCREEN_HEROS);
	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it != mHeros->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y  - mBackLine) * NUM_GRIDS_ROW;
		int next = 0;
		//if grid is occupied by hero, set the index to the front rows, until no more heros are hitted
		while (gridsCopy[index] == GRID_OCCUPY_TYPE_HERO)
		{
			next = calculateNextGrid(index, dir);
			if (next == index) break;
			else index = next;
		}
		if (gridsCopy[index] == GRID_OCCUPY_TYPE_NONE)
		{
			heroToMove[numHeroToMove] = it->second->iid;
			nextGrids[numHeroToMove] = next;
			numHeroToMove++;
			continue;
		}
		if (gridsCopy[index] == GRID_OCCUPY_TYPE_BARRIER || gridsCopy[index] == GRID_OCCUPY_TYPE_ENEMY)
		{
			heroCantMove[numHeroCantMove++] = it->second->iid;
		}
	}
	if (numHeroCantMove>0)
	{
		for (int i = 0; i < numHeroCantMove; i++)
		{
			if ((*mHeros)[heroCantMove[i]]->positon.y == mBackLine)
			{
				Event e = { BATTLE_MOVE_FAILED, (char*)heroCantMove };
				dispatchEvent(&e);
				return false;
			}
		}
	}
	for (int i = 0; i < numHeroToMove; i++)
	{
		(*mHeros)[heroToMove[i]]->positon.y = nextGrids[i] / NUM_GRIDS_ROW;
		(*mHeros)[heroToMove[i]]->positon.x = nextGrids[i] % NUM_GRIDS_ROW;
	}

	refreshGrids();

	Event e = { BATTLE_MOVE_SUCCESS, (char*)heroToMove };
	dispatchEvent(&e);

	delete heroToMove;
	delete heroCantMove;

	return true;
}

int PVEBattle::calculateNextGrid(int index, StepDirection dir)
{
	if (dir == RIGHTWARD)
	{
		if (index % NUM_GRIDS_ROW == NUM_GRIDS_ROW - 1) return index;
		else return index + 1;
	}
	else if (dir == FORWARD)
	{
		return index + NUM_GRIDS_ROW;
	}
	else if (dir == BACKWARD)
	{
		if (index < NUM_GRIDS_ROW) return index;
		else return index - NUM_GRIDS_ROW;
	}
	else if (dir == LEFTWARD)
	{
		if (index % NUM_GRIDS_ROW == 0) return index;
		else return index - 1;
	}
}

void PVEBattle::calculateRoundResult()
{
	//step 1, check blood recover, buff/debuff status 
	//step 2, check props in occupied grids
	//step 3, check active enemys and move them if hero(s) be seen (in enemys view)
	//step 4, heros round, attack enemys in aligity order.
	MaxHeap heros = MaxHeap(mHeros->size());
	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it!=mHeros->end(); it++)
	{
		UnitWraper *wraper = new UnitWraper(it->second);
		heros.Enqueue(wraper);
	}
	//AttackResult* results = new AttackResult[MAX_SCREEN_HEROS];
	AttackResult results[MAX_SCREEN_HEROS+MAX_SCREEN_ENYMYS] = { 0 };
	int count = 0;
	while (heros.size())
	{
		UnitWraper *wraper = (UnitWraper*)heros.Dequeue();
		Unit* hero = wraper->unit();
		delete wraper;
		if (calculateHeroAttackResult(hero, &results[count])) count++;
	}

	//step 5, enemys round, attack heros in aligity order
	MaxHeap enemys = MaxHeap(mEnemys->size());
	it = mEnemys->begin();
	for (it; it != mEnemys->end(); it++)
	{
		UnitWraper *wraper = new UnitWraper(it->second);
		enemys.Enqueue(wraper);
	}
	while (enemys.size())
	{
		UnitWraper *wraper = (UnitWraper*)enemys.Dequeue();
		Unit* enemy = wraper->unit();
		delete wraper;
		if (calculateEnemyAttackResult(enemy, &results[count])) count++;
	}
	if (count)
	{
		Event e = { BATTLE_ATTACK_RESULT, (char*)results };
		dispatchEvent(&e);
	}
	else
	{
		Event e = { BATTLE_STEP_CLEAR, NULL };
		dispatchEvent(&e);
	}
}
bool PVEBattle::calculateHeroBuffResult(Unit* hero, BuffResult* result)
{
	for (std::map<ID, Unit*>::iterator it = mHeros->begin(); it != mHeros->end(); it++)
	{
		// to do, implement multi-buff in one turn
		if (calculateBuffResult(hero, it->second, result)) return true;
	}
	return false;
}

bool PVEBattle::calculateEnemyBuffResult(Unit* enemy, BuffResult* result)
{
	for (std::map<ID, Unit*>::iterator it = mEnemys->begin(); it != mEnemys->end(); it++)
	{
		// to do
	}
	return false;
}

bool PVEBattle::calculateBuffResult(Unit* giver, Unit* recipient, BuffResult* result)
{
	if (isInRange(giver, recipient))
	{
		result->giver = giver->iid;
		result->recipient = recipient->iid;
		switch (giver->skill.type)
		{
		case SKILL_TYPE_BUFF_HEALTH:
			{
				recipient->health += giver->skill.value;
				recipient->health = recipient->health > recipient->maxHealth ? recipient->maxHealth : recipient->health;
			}
		default:
			break;
		}
	}
	return false;
}

bool PVEBattle::calculateHeroAttackResult(Unit* hero, AttackResult* result)
{
	for (std::map<ID, Unit*>::iterator it = mEnemys->begin(); it != mEnemys->end(); it++)
	{
		// to do, implement multi-attack in one turn
		if (calculateAttackResult(hero, it->second, result)) return true;
	}
	return false;
}


bool PVEBattle::calculateEnemyAttackResult(Unit* enemy, AttackResult* result)
{
	for (std::map<ID, Unit*>::iterator it = mHeros->begin(); it != mHeros->end(); it++)
	{
		// to do, implement multi-attack in on turn
		if (calculateAttackResult(enemy, it->second, result)) return true;
	}
	return false;
}

bool PVEBattle::calculateAttackResult(Unit* attacker, Unit* victim, AttackResult* result)
{
	if (isInRange(attacker, victim))
	{
		result->attacker = attacker->iid;
		result->victim = victim->iid;
		switch (attacker->skill.type){
			case SKILL_TYPE_HARM_PHYSICAL:
			{
				result->type = ATTACK_TYPE_PHYSICAL;
				result->value = attacker->skill.value;//to be detailed
				victim->health += result->value;
				return true;
			}
			break;
			case SKILL_TYPE_HARM_MAGICAL:
			{
				result->type = ATTACK_TYPE_MAGICAL;
				result->value = attacker->skill.value;//to be detailed
				return true;
			}
			break;
		}
	}
	return false;
}

bool PVEBattle::isInRange(Unit* attacker, Unit* victim)
{
	//first, check if in attack grids
	for (int i = 0; i < attacker->attackRange.numGrids; i++)
	{
		if (attacker->attackRange.offsets[i].x + attacker->positon.x == victim->positon.x &&
			attacker->attackRange.offsets[i].y + attacker->positon.y == victim->positon.y)
		{
			return true;
		}
	}

	//second, check if be blocked, to do
	return false;
}

std::map<ID, Unit*>* PVEBattle::heros() const
{
	return mHeros;
}

std::map<ID, Unit*>* PVEBattle::enemys() const
{
	return mEnemys;
}

std::map<ID, Unit*>* PVEBattle::barriers() const
{
	return mBarriers;
}

ID PVEBattle::mapid() const
{
	return mMap->cid();
}









