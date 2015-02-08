#ifndef _BATTLE_H
#define _BATTLE_H

#include "Map.h"
#include "EventDispatcher.h"
#include <map>
#include "dwtype.h"
#include "Unit.h"

#define MAX_SCREEN_HEROS 10
#define MAX_SCREEN_ENYMYS 20
#define MAX_SCREEN_BARRIERS 10
#define MAX_SCREEN_GRID 60
#define MAX_SKILL_RESULTS 5
#define MAX_SKILL_RECIPIENT 10
#define MAX_LOOT_RESULT 4
#define MAX_STAR_LEVEL 3

#define GRID_OCCUPY_TYPE_NONE 0
#define GRID_OCCUPY_TYPE_HERO 1
#define GRID_OCCUPY_TYPE_ENEMY 2
#define GRID_OCCUPY_TYPE_BARRIER 3
#define GRID_OCCUPY_TYPE_PROPS 4

#define SKILL_CONDITION_WHEN_MOVING 1
#define SKILL_CONDITION_AFTER_MOVE 2

#define BUFF_CONDITION_MOVE_FORWARD 1

#define BUFF_SELF_HEAL	201L


typedef struct buff_result_t
{
	ID owner;
	//ID recipient;
	ID type;
	int value;
} BuffResult;

#define ATTACK_TYPE_PHYSICAL	1L
#define ATTACK_TYPE_MAGICAL		2L
typedef struct skill_result_t
{
	ID giver;
	char numRecipients;
	ID recipients[MAX_SKILL_RECIPIENT];
	ID type;//physical or magical or what
	int value[MAX_SKILL_RECIPIENT];
	int healthLeft[MAX_SKILL_RECIPIENT];
	int set[MAX_SKILL_RECIPIENT];
	Skill skill;
	ID loots[MAX_LOOT_RESULT];
	char numLoots;
} SkillResult;

typedef struct move_result_t
{
	StepDirection dir;
	ID moveUnits[MAX_SCREEN_HEROS];
	ID enemys[MAX_SCREEN_HEROS];
	ID cantmoveUnits[MAX_SCREEN_ENYMYS];
	ID comeIntoView[NUM_GRIDS_ROW + 1];
	ID comeOutOfView[NUM_GRIDS_ROW + 1];
	ID pick[MAX_SCREEN_HEROS];
	ID picker[MAX_SCREEN_HEROS];
	SkillResult skills[MAX_SCREEN_HEROS + MAX_SCREEN_ENYMYS];
	BuffResult buffs[MAX_SCREEN_HEROS + MAX_SCREEN_ENYMYS];
} MoveResult;


typedef struct attack_result_t
{
	SkillResult results[MAX_SKILL_RESULTS];
	char count;
	ID loots[MAX_LOOT_RESULT];
	char numLoot;
} AttackResult;

typedef struct round_result_t
{
	SkillResult results[MAX_SCREEN_HEROS + MAX_SCREEN_ENYMYS];
	int count;
} RoundResult;

class PVEBattle :public EventDispather
{
public:
	PVEBattle();
	~PVEBattle();
	void initialize();
	void enter(ID mapid, Unit** heros, int numHeros);
	void start();
	void pause();
	void refresh();
	void end();
	void step(StepDirection dir);
	void moveHero(ID iid, int x, int y);
	//void update(ID eclipse);

	std::map<ID, Unit*>* heros() const;
	std::map<ID, Unit*>* enemys() const;
	std::map<ID, Unit*>* barriers() const;
	Unit* getUnit(ID iid) const;
	Unit* getUnit(int x, int y) const;
	Item* getItem(ID iid) const;
	Item* getItem(int x, int y) const;
	void pickItem(ID iid, ID who);
	ID mapid() const;
	int convertToIndex(int x, int y);
	int step() const;
private:
	void updateStarLevel();
	void updateStep();
	void addUnit(Unit* unit);
	
	void refreshGrids();
	bool calculateHerosMovement(StepDirection dir);
	void calculateEnemyMovement(MoveResult* result);
	void calculateHeroHealResult(Unit* hero, SkillResult* result);
	int calculateNextGrid(int index,StepDirection dir);
	void calculateRoundResult();
	bool calculateHeroBuffResult(int condition);
	bool calculateEnemyBuffResult(int condition);
	bool calculateBuffResult(Unit* who, BuffResult* result,int condition);
	bool calculateHeroAttackResult(Unit* hero, SkillResult* result);
	bool calculateEnemyAttackResult(Unit* enemy, SkillResult* result);
	bool calculateAttackResult(Unit* attacker, MinHeap* candidates, SkillResult* result);
	bool calculateRangeSkillResult(Skill* skill, Unit* attacker, MinHeap* candidates, SkillResult* result, int condition);
	bool calculatePathSkillResult(Skill* skill, Unit* attacker, MinHeap* candidates, SkillResult* result, int condition);
	bool calculateSkillResult(Skill* skill, Unit* attacker, Unit* victim, SkillResult* result, int condition);
	void calculateLootResult(Unit* victim, SkillResult* result);
	bool isInRange(Unit* attacker, Unit* victim);
	bool isInView(Unit* attacker, Unit* victim);
	bool checkBarrier(Position grid1, Position grid2, ID* iid);
	


public:
	static const EType BATTLE_ENTER_MAP;
	static const EType BATTLE_STEP_CLEAR;
	static const EType BATTLE_MOVE_SUCCESS;
	static const EType BATTLE_MOVE_FAILED;
	static const EType BATTLE_ATTACK_RESULT;
	static const EType BATTLE_MOVE_HERO_SUCESS;
	static const EType BATTLE_UNIT_FLOP;
	static const EType BATTLE_STEP;
	static const EType BATTLE_SUCCESS;
	static const EType BATTLE_FAILED;
private:
	char mGrids[MAX_SCREEN_GRID];
	ID mOccupy[MAX_SCREEN_GRID];
	std::map<ID, Unit*>* mHeros;
	std::map<ID, Unit*>* mEnemys;
	std::map<ID, Unit*>* mBarriers;
	std::map<ID, Item*>* mLoots;
	PVEMapData* mMap;

	int mStep;//»ØºÏ
	int mStarLevel;//ÐÇ¼¶
	int mGolds;
	int mFrontLine;
	int mBackLine;
};

class PVPBattle
{

};


#endif