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

#define MAX_STAR_LEVEL 3

#define GRID_OCCUPY_TYPE_NONE 0
#define GRID_OCCUPY_TYPE_HERO 1
#define GRID_OCCUPY_TYPE_ENEMY 2
#define GRID_OCCUPY_TYPE_BARRIER 3
#define GRID_OCCUPY_TYPE_PROPS 4

typedef struct move_result_t
{
	StepDirection dir;
	ID moveUnits[MAX_SCREEN_ENYMYS];
	ID cantmoveUnits[MAX_SCREEN_ENYMYS];
	ID comeIntoView[NUM_GRIDS_ROW + 1];
	ID comeOutOfView[NUM_GRIDS_ROW + 1];
} MoveResult;

typedef struct buff_result_t
{
	ID giver;
	ID recipient;
	ID type;
	int value;
} BuffResult;

#define ATTACK_TYPE_PHYSICAL	1L
#define ATTACK_TYPE_MAGICAL		2L
typedef struct attack_result_t
{
	ID attacker;
	ID victim;
	ID type;//physical or magical or what
	int value;
	int healthLeft;
	Skill skill;
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
	int calculateNextGrid(int index,StepDirection dir);
	void calculateRoundResult();
	bool calculateHeroBuffResult(Unit* hero, BuffResult* result);
	bool calculateEnemyBuffResult(Unit* enemy, BuffResult* result);
	bool calculateBuffResult(Unit* giver, Unit* recipient, BuffResult* result);
	bool calculateHeroAttackResult(Unit* hero,AttackResult* result);
	bool calculateEnemyAttackResult(Unit* enemy, AttackResult* result);
	bool calculateAttackResult(Unit* attacker, Unit* victim, AttackResult* result);
	bool isInRange(Unit* attacker, Unit* victim);
	void calculateSkillResult(Skill* skill, Unit* victim, AttackResult* result);


public:
	static const EType BATTLE_ENTER_MAP;
	static const EType BATTLE_STEP_CLEAR;
	static const EType BATTLE_MOVE_SUCCESS;
	static const EType BATTLE_MOVE_FAILED;
	static const EType BATTLE_ATTACK_RESULT;
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