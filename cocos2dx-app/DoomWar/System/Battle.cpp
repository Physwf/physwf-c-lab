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

EType const PVEBattle::BATTLE_STEP_CLEAR = "battle_step_clear";
EType const PVEBattle::BATTLE_ATTACK_RESULT = "battle_attack_result";

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
	return false;
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
	AttackResult results[MAX_SCREEN_HEROS+MAX_SCREEN_ENYMYS] = { 0 };
	int count = 0;
	while (heros.size())
	{
		UnitWraper *wraper = (UnitWraper*)heros.Dequeue();
		Unit* hero = wraper->unit();
		if (calculateHeroAttackResult(hero, &results[count])) count++;
	}

	//step 5, enemys round, attack heros in aligity order
	MaxHeap enemys = MaxHeap(mNumEnemys);
	for (int i = 0; i < mNumEnemys; i++)
	{
		UnitWraper wraper = UnitWraper(&mEnemys[i]);
		enemys.Enqueue(&wraper);
	}
	while (enemys.size())
	{
		UnitWraper *wraper = (UnitWraper*)enemys.Dequeue();
		Unit* enemy = wraper->unit();
		if (calculateEnemyAttackResult(enemy, &results[count])) count++;
	}
	Event e = { BATTLE_ATTACK_RESULT, (char*)results };
	dispatchEvent(&e);
	//send battle result
}
bool PVEBattle::calculateHeroBuffResult(Unit* hero, BuffResult* result)
{
	for (int i = 0; i < mNumHeros; i++)
	{
		// to do, implement multi-buff in one turn
		if (calculateBuffResult(hero, &mHeros[i], result)) return true;
	}
	return false;
}

bool PVEBattle::calculateEnemyBuffResult(Unit* enemy, BuffResult* result)
{
	for (int i = 0; i < mNumEnemys; i++)
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
	for (int i = 0; i < mNumEnemys; i++)
	{
		// to do, implement multi-attack in one turn
		if (calculateAttackResult(hero, &mEnemys[i], result)) return true;
	}
	return false;
}


bool PVEBattle::calculateEnemyAttackResult(Unit* enemy, AttackResult* result)
{
	for (int i = 0; i < mNumHeros; i++)
	{
		// to do, implement multi-attack in on turn
		if (calculateAttackResult(enemy, &mHeros[i], result)) return true;
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
				return true;
			}
			break;
			case SKILL_TYPE_HARM_MAGICAL:
			{
				result->type = ATTACK_TYPE_PHYSICAL;
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
	bool in = false;
	for (int i = 0; i < attacker->attackRange.numGrids; i++)
	{
		if (attacker->attackRange.offsets[i].x + attacker->positon.x == victim->positon.x &&
			attacker->attackRange.offsets[i].y + attacker->positon.y == victim->positon.y)
			in = true;
	}
	if (!in) return false;

	//second, check if be blocked, to do
	return false;
}

