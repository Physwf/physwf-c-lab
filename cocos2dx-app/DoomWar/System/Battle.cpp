#include "Battle.h"
#include "Config.h"
#include <string.h>
#include "dwtype.h"
#include <assert.h>
#include "System.h"
#include <set>

PVEBattle::PVEBattle()
{
	mMap = new PVEMapData();
	mHeros = new std::map<ID, Unit*>();
	mEnemys = new std::map<ID, Unit*>();
	mBarriers = new std::map<ID, Unit*>();
	mLoots = new std::map<ID, Item*>();
	
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
EType const PVEBattle::BATTLE_UNIT_FLOP = "battle_unit_flop";
EType const PVEBattle::BATTLE_STEP = "battle_step";
EType const PVEBattle::BATTLE_SUCCESS = "battle_success";
EType const PVEBattle::BATTLE_FAILED = "battle_failed";

void PVEBattle::initialize()
{
	/*memset(mHeros, 0, sizeof(mHeros));
	mNumHeros = 0;
	memset(mEnemys, 0, sizeof(mEnemys));
	mNumEnemys = 0;
	memset(mBarriers, 0, sizeof(mBarriers));
	mNumBarries = 0;*/
	memset(mGrids, 0, sizeof(mGrids));
	memset(mOccupy, 0, sizeof(mOccupy));

	mHeros->clear();
	mEnemys->clear();
	mBarriers->clear();
	mLoots->clear();

	mStep = 0;
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

int PVEBattle::step() const
{
	return mStep;
}

void PVEBattle::updateStep()
{
	mStep++;
	Event e = { BATTLE_STEP, NULL };
	dispatchEvent(&e);
}

void PVEBattle::addUnit(Unit* unit)
{
	int index = (unit->positon.x) + ((unit->positon.y) - mBackLine) * NUM_GRIDS_ROW;
	if (unit->alignment == UNIT_ALIGN_TYPE_HERO)
	{
		(*mHeros)[unit->iid] = unit;
		mGrids[index] = GRID_OCCUPY_TYPE_HERO;
		mOccupy[index] = unit->iid;
	}
	else if (unit->alignment == UNIT_ALIGN_TYPE_ENEMY)
	{
		(*mEnemys)[unit->iid] = unit;
		mGrids[index] = GRID_OCCUPY_TYPE_ENEMY;
		mOccupy[index] = unit->iid;
	}
}

void PVEBattle::step(StepDirection dir)
{
	if (!calculateHerosMovement(dir)) return;

	refreshGrids();

	calculateRoundResult();

	refreshGrids();

	updateStep();
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

	MoveResult mResult = { NONE, { 0 }, { 0 }, { 0 }, { 0 } };

	int index = convertToIndex(x, y);
	if (mGrids[index] == GRID_OCCUPY_TYPE_PROPS)
	{
		Item* loot = getItem(x, y);
		mResult.pick[0] = loot->iid;
		//mLoots->erase(mLoots->find(loot->iid));
	}

	mResult.moveUnits[0] = iid;
	calculateEnemyMovement(&mResult);

	Event e = { BATTLE_MOVE_HERO_SUCESS, (char*)&mResult };
	dispatchEvent(&e);

	refreshGrids();

	calculateRoundResult();

	refreshGrids();

	updateStep();
}

void PVEBattle::refreshGrids()
{
	memset(mGrids, 0, sizeof(mGrids));
	memset(mOccupy, 0, sizeof(mOccupy));

	std::map<ID, Unit*>::iterator it = mHeros->begin();
	for (it; it != mHeros->end(); it++)
	{
		int index = convertToIndex(it->second->positon.x, it->second->positon.y);
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_HERO;
		mOccupy[index] = it->second->iid;
	}

	it = mEnemys->begin();
	for (it; it != mEnemys->end(); it++)
	{
		int index = convertToIndex(it->second->positon.x, it->second->positon.y);
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_ENEMY;
		mOccupy[index] = it->second->iid;
	}

	it = mBarriers->begin();
	for (it; it != mBarriers->end(); it++)
	{
		int index = convertToIndex(it->second->positon.x, it->second->positon.y);
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_BARRIER;
		mOccupy[index] = it->second->iid;
	}

	std::map<ID, Item*>::iterator iLoot = mLoots->begin();
	for (iLoot; iLoot != mLoots->end(); iLoot++)
	{
		int index = convertToIndex(iLoot->second->position.x, iLoot->second->position.y);
		if (index <0 || index >= MAX_SCREEN_GRID) continue;
		mGrids[index] = GRID_OCCUPY_TYPE_PROPS;
		mOccupy[index] = iLoot->second->iid;
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
		int index = convertToIndex(it->second->positon.x, it->second->positon.y);
		int next = calculateNextGrid(index, dir);
		int target = next;
		//if grid is occupied by hero, set the index to the front rows, until no more heros are hitted
		while (gridsCopy[index] == GRID_OCCUPY_TYPE_HERO)
		{
			if (next == index) break;
			index = next;
			next = calculateNextGrid(index, dir);
		}
		if (gridsCopy[index] == GRID_OCCUPY_TYPE_NONE || gridsCopy[index] == GRID_OCCUPY_TYPE_PROPS)
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
	int pick_count = 0;
	for (int i = 0; i < numHeroToMove; i++)
	{
		Unit* who = (*mHeros)[result.moveUnits[i]];
		who->positon.y = nextGrids[i] / NUM_GRIDS_ROW + mBackLine;
		who->positon.x = nextGrids[i] % NUM_GRIDS_ROW;
		//pick loot
		int index = convertToIndex(who->positon.x, who->positon.y);
		if (mGrids[index] == GRID_OCCUPY_TYPE_PROPS)
		{
			Item* loot = getItem(who->positon.x, who->positon.y);
			result.pick[pick_count] = loot->iid;
			result.picker[pick_count] = who->iid;
			pick_count++;
			//mLoots->erase(mLoots->find(loot->iid));
		}

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

	calculateEnemyMovement(&result);

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

void PVEBattle::calculateEnemyMovement(MoveResult* result)
{
	std::map<ID, Unit*>::iterator iEnemy = mEnemys->begin();
	
	int count = 0;
	external:while (iEnemy != mEnemys->end())
	{
		Unit* enemy = iEnemy->second;
		iEnemy++;
		MinHeap nearHeros = MinHeap(mHeros->size());
		std::map<ID, Unit*>::iterator iHero = mHeros->begin();
		while (iHero != mHeros->end())
		{
			Unit* hero = iHero->second;
			if (isInRange(enemy, hero)) goto external;
			if (isInView(enemy, hero))
			{
				int dist = (hero->positon.x - enemy->positon.x)*(hero->positon.x - enemy->positon.x) + (hero->positon.y - enemy->positon.y)*(hero->positon.y - enemy->positon.y);
				nearHeros.Enqueue(new UnitWraper(hero, dist));
			}
			iHero++;
		}
		if (nearHeros.size())
		{
			UnitWraper* wraper = (UnitWraper*)nearHeros.Dequeue();
			Unit* target = wraper->unit();
			
			int dir[2] = { target->positon.x - enemy->positon.x, target->positon.y - enemy->positon.y };
			dir[0] = dir[0] ? abs(dir[0]) / dir[0] : dir[0];
			dir[1] = dir[1] ? abs(dir[1]) / dir[1] : dir[1];
			// to do, avoid barriers
			int index = convertToIndex(enemy->positon.x + dir[0], (enemy->positon.y + dir[1]));
			if (mGrids[index] == GRID_OCCUPY_TYPE_NONE)
			{
				enemy->positon.x += dir[0];
				enemy->positon.y += dir[1];
				result->enemys[count++] = enemy->iid;
				mGrids[index] = GRID_OCCUPY_TYPE_ENEMY;
				mOccupy[index] = enemy->iid;
			}
		}
		
	}
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
	calculateRangeSkillResult(&heal, hero, &heap, result, SKILL_CONDITION_WHEN_MOVING);
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
	RoundResult rResult = {0};
	//int count = 0;
	while (heros.size())
	{
		UnitWraper *wraper = (UnitWraper*)heros.Dequeue();
		Unit* hero = wraper->unit();
		delete wraper;
		if (calculateHeroAttackResult(hero, &rResult.results[rResult.count])) rResult.count++;
	}
	
	//step 5, enemys round, attack heros in aligity order
	MaxHeap enemys = MaxHeap(mEnemys->size());
	it = mEnemys->begin();
	for (it; it != mEnemys->end(); )
	{
		if (it->second->health <= 0)//dead
		{
			//it = mEnemys->erase(it);
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
		if (calculateEnemyAttackResult(enemy, &rResult.results[rResult.count])) rResult.count++;
	}

	if (rResult.count)
	{
		Event e = { BATTLE_ATTACK_RESULT, (char*)&rResult };
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
			result->value = buff.value;
			who->health = who->health > who->maxHealth ? who->maxHealth : who->health;
			break;
		default:
			break;
		}
	}
	return false;
}

bool PVEBattle::calculateHeroAttackResult(Unit* hero, SkillResult* result)
{
	MinHeap nearEneymeys = MinHeap(mEnemys->size());
	for (std::map<ID, Unit*>::iterator it = mEnemys->begin(); it != mEnemys->end(); it++)
	{
		if (!isInRange(hero, it->second)) continue;
		if (it->second->health <= 0) continue;//don't attack dead body.
		int dist = (it->second->positon.x - hero->positon.x) * (it->second->positon.x - hero->positon.x) + (it->second->positon.y - hero->positon.y) + (it->second->positon.y - hero->positon.y);
		UnitWraper *wraper = new UnitWraper(it->second, dist);
		nearEneymeys.Enqueue(wraper);
		// to do, implement multi-attack in one turn
	}
	if (calculateAttackResult(hero, &nearEneymeys, result)) return true;
	return false;
}


bool PVEBattle::calculateEnemyAttackResult(Unit* enemy, SkillResult* result)
{
	MinHeap nearHeros = MinHeap(mHeros->size());
	for (std::map<ID, Unit*>::iterator it = mHeros->begin(); it != mHeros->end(); it++)
	{
		if (!isInRange(enemy, it->second)) continue;
		if (it->second->health <= 0) continue;//don't attack dead body.
		int dist = (it->second->positon.x - enemy->positon.x) * (it->second->positon.x - enemy->positon.x) + (it->second->positon.y - enemy->positon.y) + (it->second->positon.y - enemy->positon.y);
		// to do, implement multi-attack in on turn
		UnitWraper *wraper = new UnitWraper(it->second, dist);
		nearHeros.Enqueue(wraper);
	}
	if (calculateAttackResult(enemy, &nearHeros, result)) return true;
	return false;
}

bool PVEBattle::calculateAttackResult(Unit* attacker, MinHeap* candidates, SkillResult* result)
{
	Skill main;
	Config::skill->fill(&main, attacker->skills[0]);
	result->giver = attacker->iid;
	result->skill = main;
	bool ret;
	switch (main.attack)
	{
	case SKILL_ATTACK_BY_RANGE:
		return calculateRangeSkillResult(&main, attacker, candidates, result, SKILL_CONDITION_AFTER_MOVE);
		break;
	case SKILL_ATTACK_BY_GRID:
		return calculatePathSkillResult(&main, attacker, candidates, result, SKILL_CONDITION_AFTER_MOVE);
		break;
	}
	return false;
}

bool PVEBattle::calculateRangeSkillResult(Skill* skill, Unit* attacker, MinHeap* candidates, SkillResult* result, int condition)
{
	if (skill->condition != condition) return false;
	int i = 0;
	while (i < skill->limit && candidates->size())
	{
		i++;
		UnitWraper* wraper = (UnitWraper*)candidates->Dequeue();
		Unit* victim = wraper->unit();
		ID idBarrier = 0;
		
		if (checkBarrier(attacker->positon, victim->positon, &idBarrier))
		{
			Unit* barrier = (*mBarriers)[idBarrier];
			if (calculateSkillResult(skill, attacker, barrier, result, condition))
			{
				result->recipients[result->numRecipients] = barrier->iid;
				result->numRecipients++;
				calculateLootResult(barrier, result);
				return true;
			}
		}
		else
		{
			if (calculateSkillResult(skill, attacker, victim, result, condition))
			{
				result->recipients[result->numRecipients] = victim->iid;
				result->numRecipients++;
				calculateLootResult(victim, result);
			}
		}
	}
	return result->numRecipients>0;
}

bool PVEBattle::calculatePathSkillResult(Skill* skill, Unit* attacker, MinHeap* candidates, SkillResult* result, int condition)
{
	if (skill->condition != condition) return false;

	std::map<ID,Unit*> enemys;
	while (candidates->size())
	{
		UnitWraper* wraper = (UnitWraper*)candidates->Dequeue();
		Unit* victim = wraper->unit();
		enemys[victim->iid] = victim;
	}
		
	for (int i = 0; i < skill->range2.numGSets; i++)
	{
		ID cid = skill->range2.gSets[i];
		GSet set = { 0 };
		Config::skill->fill(&set, cid);
		for (int j = 0; j < set.numElements; j++)
		{
			Grid grid = set.elements[j];
			grid.x += attacker->positon.x;
			grid.y += attacker->positon.y;
			if (grid.x > NUM_GRIDS_ROW || grid.x < 0) break;

			Unit* unit = getUnit(grid.x, grid.y);
			if (unit == NULL) continue;
			int index = grid.x + (grid.y - mBackLine) * NUM_GRIDS_ROW;
			if (mGrids[index] == GRID_OCCUPY_TYPE_BARRIER)
			{
				if (calculateSkillResult(skill, attacker, unit, result, condition))
				{
					result->recipients[result->numRecipients] = unit->iid;
					result->set[result->numRecipients] = i;
					result->numRecipients++;
					calculateLootResult(unit, result);
				}
				break;
			}
			if (enemys.find(unit->iid) != enemys.end())
			{
				if (calculateSkillResult(skill, attacker, unit, result, condition))
				{
					result->recipients[result->numRecipients] = unit->iid;
					result->set[result->numRecipients] = i;
					result->numRecipients++;
					calculateLootResult(unit, result);
				}
			}
		}
			
	}
	return result->numRecipients>0;
}

bool PVEBattle::calculateSkillResult(Skill* skill, Unit* attacker, Unit* victim, SkillResult* result, int condition)
{
	switch (skill->type)
	{
		case SKILL_TYPE_HARM_PHYSICAL:
			if (victim->health <= 0) return false;
			result->type = SKILL_TYPE_HARM_PHYSICAL;
			result->value[result->numRecipients] = skill->value;//to be detailed
			victim->health += result->value[result->numRecipients];
			result->healthLeft[result->numRecipients] = victim->health;
		break;
		case SKILL_TYPE_HARM_MAGICAL:
			if (victim->health <= 0) return false;
			result->type = SKILL_TYPE_HARM_MAGICAL;
			result->value[result->numRecipients] = skill->value;//to be detailed
		break;
		case SKILL_TYPE_HEAL:
			result->type = SKILL_TYPE_HEAL;
			result->value[result->numRecipients]  = skill->value;//to be detailed
			victim->health += skill->value;
			victim->health = victim->health > victim->maxHealth ? victim->maxHealth : victim->health;
		break;
	}
	return true;
}

void PVEBattle::calculateLootResult(Unit* victim, SkillResult* result)
{
	std::map<ID, Unit*>::iterator it;
	if (victim->health > 0) return;

	if ((it = mHeros->find(victim->iid)) != mHeros->end())
	{
		mHeros->erase(it);
	}
	if ((it = mEnemys->find(victim->iid)) != mEnemys->end())
	{
		mEnemys->erase(it);
		Item* item = Config::item->create(4001);
		item->position = victim->positon;
		(*mLoots)[item->iid] = item;
		result->loots[result->numLoots] = item->iid;
		result->numLoots++;
		int index = (victim->positon.x) + ((victim->positon.y) - mBackLine) * NUM_GRIDS_ROW;
		mGrids[index] = GRID_OCCUPY_TYPE_PROPS;
		mOccupy[index] = item->iid;
	}
	if ((it = mBarriers->find(victim->iid)) != mBarriers->end())
	{
		mBarriers->erase(it);
		Item* item = Config::item->create(4003);
		int index = (victim->positon.x) + ((victim->positon.y) - mBackLine) * NUM_GRIDS_ROW;
		mGrids[index] = GRID_OCCUPY_TYPE_NONE;
		(*mLoots)[item->iid] = item;
		item->position = victim->positon;
		result->loots[result->numLoots] = item->iid;
		result->numLoots++;
	}
}

bool PVEBattle::isInRange(Unit* attacker, Unit* victim)
{
	//first, check if in attack grids
	Skill skill;
	Config::skill->fill(&skill, attacker->skills[0]);
	for (int i = 0; i < skill.range2.numGSets; i++)
	{
		ID cid = skill.range2.gSets[i];
		GSet set;
		Config::skill->fill(&set, cid);
		for (int j = 0; j < set.numElements; j++)
		{
			if (set.elements[j].x + attacker->positon.x == victim->positon.x && set.elements[j].y + attacker->positon.y == victim->positon.y)
			{
				return true;
			}
		}
	}
	//second, check if be blocked, to do
	return false;
}

bool PVEBattle::isInView(Unit* attacker, Unit* victim)
{
	//first, check if in attack grids
	for (int i = 0; i < attacker->view.numGrids; i++)
	{
		if (attacker->view.offsets[i].x + attacker->positon.x == victim->positon.x &&
			attacker->view.offsets[i].y + attacker->positon.y == victim->positon.y)
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
		int index = gridx + (gridy - mBackLine)* NUM_GRIDS_ROW;
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

Unit* PVEBattle::getUnit(int x, int y) const
{
	int index = x + (y - mBackLine) * NUM_GRIDS_ROW;
	ID iid = mOccupy[index];
	if (mHeros->find(iid) != mHeros->end()) return (*mHeros)[iid];
	if (mEnemys->find(iid) != mEnemys->end()) return (*mEnemys)[iid];
	if (mBarriers->find(iid) != mBarriers->end()) return (*mBarriers)[iid];
	return NULL;
}

Item* PVEBattle::getItem(ID iid) const
{
	if (mLoots->find(iid) != mLoots->end()) return (*mLoots)[iid];
	return NULL;
}

Item* PVEBattle::getItem(int x, int y) const
{
	int index = x + (y - mBackLine) * NUM_GRIDS_ROW;
	ID iid = mOccupy[index];
	std::map<ID, Item*>::iterator it = mLoots->find(iid);
	if (mLoots->find(iid) != mLoots->end()) return (*mLoots)[iid];
	/*
	std::map<ID, Item*>::iterator it = mLoots->begin();
	for (it; it != mLoots->end(); it++)
	{
		if (it->second->position.x == x && it->second->position.y == y) return it->second;
	}
	return NULL;
	*/
}

void PVEBattle::pickItem(ID iid,ID who)
{
	std::map<ID, Item*>::iterator it = mLoots->find(iid);
	if (it != mLoots->end())
	{
		Item* item = it->second;
		if (item->type == ITEM_TYPE_GOLD)
		{
			System::bag->addGold(item->value);
		}
		else if (item->type == ITEM_TYPE_BLOOD)
		{
			std::map<ID, Unit*>::iterator itHero = mHeros->find(who);
			assert(itHero != mHeros->end());
			Unit* picker = itHero->second;
			picker->health += item->value;
		}
		else if (item->type == ITEM_TYPE_EGG)
		{
			ID cid = item->value;
			Unit* monster = Config::monster->create(cid);
			monster->health = monster->maxHealth;
			monster->positon = item->position;
			addUnit(monster);

			Event e = {BATTLE_UNIT_FLOP,(char*)&monster->iid};
			dispatchEvent(&e);
		}
		mLoots->erase(it);
		refreshGrids();
		if (mEnemys->size() == 0 && mLoots->size() == 0)
		{
			Event e = { BATTLE_SUCCESS, NULL };
			dispatchEvent(&e);
		}
	}
}

int PVEBattle::convertToIndex(int x, int y)
{
	return x + (y - mBackLine) * NUM_GRIDS_ROW;
}
