#include "Battle.h"
#include "Config.h"
#include <string.h>
#include "dwtype.h"
#include <assert.h>

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
EType const PVEBattle::BATTLE_MOVE_HERO_SUCESS = "battle_move_hero_sucess";

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

void PVEBattle::enter(ID mapid, Unit** heros, int numHeros)
{
	mMap->init("");

	for (int i = 0; i < numHeros; i++)
	{
		Unit* hero = heros[i];
		(*mHeros)[hero->iid] = hero;
		hero->health = hero->maxHealth;
		hero->positon.x = 1+i;
		hero->positon.y = 2;
		hero->buffs[0] = BUFF_SELF_HEAL;
	}
	mFrontLine = MAX_SCREEN_GRID / NUM_GRIDS_ROW - 1;
	mBackLine = 1;

	for (int row = mBackLine; row <= mFrontLine; row++)
	{
		ID iids[NUM_GRIDS_ROW + 1];
		mMap->getEnemysByRow(row, mEnemys, iids);
		mMap->getBarriersByRow(row, mBarriers, iids);
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

	calculateRoundResult();

	refreshGrids();
}

void PVEBattle::moveHero(ID iid, int x, int y)
{
	std::map<ID, Unit*>::iterator it = mHeros->find(iid);
	assert(it != mHeros->end());

	assert(x >= 0 && x < NUM_GRIDS_ROW);
	assert(y >= 0 && y< MAX_MAP_GRID / NUM_GRIDS_ROW);

	if (it->second->positon.x == x && it->second->positon.y == y) return;

	it->second->positon.x = x;
	it->second->positon.y = y;

	Event e = { BATTLE_MOVE_HERO_SUCESS, (char*)&iid };
	dispatchEvent(&e);

	refreshGrids();

	calculateRoundResult();

	refreshGrids();
}

void PVEBattle::refreshGrids()
{
	memset(mGrids, 0, sizeof(mGrids));

	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it != mHeros->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_HERO;
	}

	it = mEnemys->begin();
	for (it; it != mEnemys->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_ENEMY;
	}

	it = mBarriers->begin();
	for (it; it != mBarriers->end(); it++)
	{
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
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
	//ID* heroToMove = new ID[MAX_SCREEN_HEROS];
	int numHeroToMove = 0;
	int nextGrids[MAX_SCREEN_HEROS] = {0};
	//memset(heroToMove, 0, sizeof(Unit*)*MAX_SCREEN_HEROS);
	MoveResult result = { dir, { 0 }, { 0 }, { 0 }, { 0 } };
	//ID* heroCantMove = new ID[MAX_SCREEN_HEROS];
	int numHeroCantMove = 0;
	//memset(heroCantMove, 0, sizeof(Unit*)*MAX_SCREEN_HEROS);
	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it != mHeros->end(); it++)
	{
		if (it->second->health <= 0) continue;//don't move dead body.
		int index = it->second->positon.x + (it->second->positon.y - mBackLine) * NUM_GRIDS_ROW;
		int next = calculateNextGrid(index, dir);
		int target = next;
		//if grid is occupied by hero, set the index to the front rows, until no more heros are hitted
		while (gridsCopy[index] == GRID_OCCUPY_TYPE_HERO)
		{
			if (next == index) break;
			index = next;
			next = calculateNextGrid(index, dir);
		}
		if (gridsCopy[index] == GRID_OCCUPY_TYPE_NONE)
		{
			//heroToMove[numHeroToMove] = it->second->iid;
			result.moveUnits[numHeroToMove] = it->second->iid;
			nextGrids[numHeroToMove] = target;
			numHeroToMove++;
			continue;
		}
		if (gridsCopy[index] == GRID_OCCUPY_TYPE_BARRIER || gridsCopy[index] == GRID_OCCUPY_TYPE_ENEMY)
		{
			//heroCantMove[numHeroCantMove++] = it->second->iid;
			result.cantmoveUnits[numHeroCantMove++] = it->second->iid;
		}
	}
	if (numHeroCantMove>0)
	{
		for (int i = 0; i < numHeroCantMove; i++)
		{
			if ((*mHeros)[result.cantmoveUnits[i]]->positon.y == mBackLine)
			{
				Event e = { BATTLE_MOVE_FAILED, (char*)&result };
				dispatchEvent(&e);
				return false;
			}
		}
	}
	int skill_count = 0;
	int buff_count = 0;
	for (int i = 0; i < numHeroToMove; i++)
	{
		Unit* who = (*mHeros)[result.moveUnits[i]];
		who->positon.y = nextGrids[i] / NUM_GRIDS_ROW + mBackLine;
		who->positon.x = nextGrids[i] % NUM_GRIDS_ROW;
		
		int j = 0;
		while (who->skills[j])
		{
			Skill skill;
			Config::skill->fill(&skill, who->skills[j]);
			if (skill.condition == SKILL_CONDITION_WHEN_MOVING)
			{
				calculateHeroHealResult(who, result.skills + skill_count);
				skill_count++;
			}
			j++;
		}
		if (dir != FORWARD) continue;

		calculateBuffResult(who, result.buffs + buff_count, BUFF_CONDITION_MOVE_FORWARD);
		buff_count++;
	}


	if (dir == FORWARD)
	{
		mFrontLine++;
		mBackLine++;
		//barriers
		int count = mMap->getBarriersByRow(mFrontLine, mBarriers, result.comeIntoView);
		//enemys
		mMap->getEnemysByRow(mFrontLine, mEnemys, result.comeIntoView + count);
	}
	else if (dir == BACKWARD)
	{
		mFrontLine--;
		mBackLine--;
	}
	Event e = { BATTLE_MOVE_SUCCESS, (char*)&result };
	dispatchEvent(&e);

	return true;
}

void PVEBattle::calculateHeroHealResult(Unit* hero, SkillResult* result)
{
	//if in range, sort by health
	std::map<ID, Unit*>::iterator it = mHeros->begin();
	MinHeap heap = MinHeap(mHeros->size());
	for (; it != mHeros->end(); it++)
	{
		if (it->second->iid == hero->iid) continue;
		if (it->second->health >= it->second->maxHealth) continue;
		if (isInRange(hero, it->second))
		{
			UnitWraper* wraper = new UnitWraper(it->second, it->second->health);
			heap.Enqueue(wraper);
		}
	}
	if (heap.size() <= 0) return;
	//find weakest
	Skill heal;
	Config::skill->fill(&heal, hero->skills[0]);
	for (int i = 0; i < hero->attackFreq; i++)
	{
		UnitWraper* wraper = (UnitWraper*)heap.Dequeue();
		calculateSkillResult(&heal, hero, wraper->unit(), result, SKILL_CONDITION_WHEN_MOVING);
	}
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
	return 0;
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
		if (it->second->health <= 0) continue;//dead
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
	for (it; it != mEnemys->end(); )
	{
		if (it->second->health <= 0)//dead
		{
			it = mEnemys->erase(it);
			continue;
		}
		UnitWraper *wraper = new UnitWraper(it->second);
		enemys.Enqueue(wraper);
		it++;
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

bool PVEBattle::calculateHeroBuffResult(int condition)
{
	for (std::map<ID, Unit*>::iterator it = mHeros->begin(); it != mHeros->end(); it++)
	{
		// to do, implement multi-buff in one turn
	}
	return false;
}

bool PVEBattle::calculateEnemyBuffResult(int condition)
{
	for (std::map<ID, Unit*>::iterator it = mEnemys->begin(); it != mEnemys->end(); it++)
	{
		// to do
	}
	return false;
}

bool PVEBattle::calculateBuffResult(Unit* who, BuffResult* result, int condition)
{
	result->owner = who->iid;
	int i = 0;
	while (ID cid = who->buffs[i])
	{
		i++;
		Buff buff;
		Config::skill->fill(&buff, cid);
		if (buff.condition != condition) continue;
		switch (buff.type)
		{
		case BUFF_TYPE_HEAL:
			result->type = BUFF_TYPE_HEAL;
			who->health += buff.value;
			break;
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
		if (it->second->health <= 0) continue;//don't attack dead body.
		// to do, implement multi-attack in one turn
		if (calculateAttackResult(hero, it->second, result)) return true;
	}
	return false;
}


bool PVEBattle::calculateEnemyAttackResult(Unit* enemy, AttackResult* result)
{
	for (std::map<ID, Unit*>::iterator it = mHeros->begin(); it != mHeros->end(); it++)
	{
		if (it->second->health <= 0) continue;//don't attack dead body.
		// to do, implement multi-attack in on turn
		if (calculateAttackResult(enemy, it->second, result)) return true;
	}
	return false;
}

bool PVEBattle::calculateAttackResult(Unit* attacker, Unit* victim, AttackResult* result)
{
	if (isInRange(attacker, victim))
	{
		ID idBarrier = 0;
		if (checkBarrier(attacker->positon, victim->positon, &idBarrier))
		{
			Unit* barrier = (*mBarriers)[idBarrier];
			Skill main;
			Config::skill->fill(&main, attacker->skills[0]);
			if (calculateSkillResult(&main, attacker, barrier, result->results, SKILL_CONDITION_AFTER_MOVE))
			{
				result->count++;
				return true;
			}
		}
		else
		{
			int i = 0;
			while (attacker->skills[i])
			{
				Skill skill;
				Config::skill->fill(&skill, attacker->skills[i]);
				if (calculateSkillResult(&skill, attacker, victim, result->results + result->count, SKILL_CONDITION_AFTER_MOVE))
					result->count++;
				i++;
			}
			if (result->count) return true;
		}
	}
	return false;
}

bool PVEBattle::calculateSkillResult(Skill* skill, Unit* attacker, Unit* victim, SkillResult* result, int condition)
{
	if (skill->condition != condition) return false;
	result->giver = attacker->iid;
	result->recipient = victim->iid;
	result->skill = *skill;
	switch (skill->type)
	{
		case SKILL_TYPE_HARM_PHYSICAL:
		{
			result->type = SKILL_TYPE_HARM_PHYSICAL;
			result->value = skill->value;//to be detailed
			victim->health += result->value;
			result->healthLeft = victim->health;
		}
		break;
		case SKILL_TYPE_HARM_MAGICAL:
		{
			result->type = SKILL_TYPE_HARM_MAGICAL;
			result->value = skill->value;//to be detailed
		}
		break;
		case SKILL_TYPE_HEAL:
		{
			result->type = SKILL_TYPE_HEAL;
			result->value = skill->value;//to be detailed
			victim->health += skill->value;
			victim->health = attacker->health > victim->maxHealth ? victim->maxHealth : victim->health;
		}
		break;
	}
	return true;
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

bool PVEBattle::checkBarrier(Position grid1, Position grid2, ID* iid)
{
	int offsetx = grid1.x - grid2.x;
	int offsety = grid1.y - grid2.y;
	int max = abs(offsetx) > abs(offsety) ? abs(offsetx) : abs(offsety);
	for (int i = 1; i < max; i++)
	{
		float testx = grid2.x + (float)offsetx / max;
		float testy = grid2.y + (float)offsety / max;
		int gridx = (int)testx;
		int gridy = (int)testy;
		int index = gridx + gridy * NUM_GRIDS_ROW;
		if (mGrids[index] == GRID_OCCUPY_TYPE_BARRIER)
		{
			for (std::map<ID, Unit*>::iterator it = mBarriers->begin(); it != mBarriers->end(); it++)
			{
				if (it->second->positon.x == gridx && it->second->positon.y == gridy)
				{
					*iid = it->second->iid;
					return true;
				}
			}
		}
	}
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

Unit* PVEBattle::getUnit(ID iid) const
{
	if (mHeros->find(iid) != mHeros->end()) return (*mHeros)[iid];
	if (mEnemys->find(iid) != mEnemys->end()) return (*mEnemys)[iid];
	if (mBarriers->find(iid) != mBarriers->end()) return (*mBarriers)[iid];
	return NULL;
}











