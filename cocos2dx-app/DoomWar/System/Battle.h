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
	ID recipient;
	ID type;//physical or magical or what
	int value;
	int healthLeft;
	Skill skill;
} SkillResult;

typedef struct move_result_t
{
	StepDirection dir;
	ID moveUnits[MAX_SCREEN_HEROS];
	ID cantmoveUnits[MAX_SCREEN_ENYMYS];
	ID comeIntoView[NUM_GRIDS_ROW + 1];
	ID comeOutOfView[NUM_GRIDS_ROW + 1];
	SkillResult skills[MAX_SCREEN_HEROS + MAX_SCREEN_ENYMYS];
	BuffResult buffs[MAX_SCREEN_HEROS + MAX_SCREEN_ENYMYS];
} MoveResult;


typedef struct attack_result_t
{
	char count;
	SkillResult results[MAX_SKILL_RESULTS];
} AttackResult;

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
	void update(ID eclipse);

	std::map<ID, Unit*>* heros() const;
	std::map<ID, Unit*>* enemys() const;
	std::map<ID, Unit*>* barriers() const;
	Unit* getUnit(ID iid) const;
	ID mapid() const;
private:
	void updateStarLevel();
	void refreshGrids();
	bool calculateHerosMovement(StepDirection dir);
	void calculateHeroHealResult(Unit* hero, SkillResult* result);
	int calculateNextGrid(int index,StepDirection dir);
	void calculateRoundResult();
	bool calculateHeroBuffResult(int condition);
	bool calculateEnemyBuffResult(int condition);
	bool calculateBuffResult(Unit* who, BuffResult* result,int condition);
	bool calculateHeroAttackResult(Unit* hero, AttackResult* result);
	bool calculateEnemyAttackResult(Unit* enemy, AttackResult* result);
	bool calculateAttackResult(Unit* attacker, MinHeap* candidates, AttackResult* result);
	bool calculateSkillResult(Skill* skill, Unit* attacker, Unit* victim, SkillResult* result,int condition);
	bool isInRange(Unit* attacker, Unit* victim);
	bool checkBarrier(Position grid1, Position grid2, ID* iid);
	


public:
	static const EType BATTLE_ENTER_MAP;
	static const EType BATTLE_STEP_CLEAR;
	static const EType BATTLE_MOVE_SUCCESS;
	static const EType BATTLE_MOVE_FAILED;
	static const EType BATTLE_ATTACK_RESULT;
	static const EType BATTLE_MOVE_HERO_SUCESS;
private:
	//Unit mHeros[MAX_SCREEN_HEROS];
	//int mNumHeros;
	//Unit mEnemys[MAX_SCREEN_ENYMYS];
	//int mNumEnemys;
	//Unit mBarriers[MAX_SCREEN_BARRIERS];
	//int mNumBarries;
	char mGrids[MAX_SCREEN_GRID];
	
	std::map<ID, Unit*>* mHeros;
	std::map<ID, Unit*>* mEnemys;
	std::map<ID, Unit*>* mBarriers;

	PVEMap* mMap;

	int mRound;//»ØºÏ
	int mStarLevel;//ÐÇ¼¶
	int mGolds;
	int mFrontLine;
	int mBackLine;

	
};

class PVPBattle
{

};


#endif