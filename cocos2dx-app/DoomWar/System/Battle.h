#ifndef _BATTLE_H
#define _BATTLE_H

#include "Map.h"
#include "EventDispatcher.h"

#define MAX_SCREEN_HEROS 10
#define MAX_SCREEN_ENYMYS 20
#define MAX_SCREEN_BARRIERS 10
#define MAX_SCREEN_GRID 60

#define MAX_STAR_LEVEL 3

typedef struct buff_result_t
{
	unsigned int giver;
	unsigned int recipient;
	unsigned int type;
	int value;
} BuffResult;

#define ATTACK_TYPE_PHYSICAL	1L
#define ATTACK_TYPE_MAGICAL		2L
typedef struct attack_result_t
{
	unsigned int attacker;
	unsigned int victim;
	unsigned int type;//physical or magical or what
	int value;
} AttackResult;

class PVEBattle :public EventDispather
{
public:
	PVEBattle();
	~PVEBattle();
	void initialize(Unit* heros, int numHeros, PVEMap* map);
	void start();
	void pause();
	void refresh();
	void end();
	void step();
	void update(unsigned int eclipse);
private:
	void updateStarLevel();
	bool checkEncounter();
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
	static const EType BATTLE_STEP_CLEAR;
	static const EType BATTLE_ATTACK_RESULT;
private:
	Unit mHeros[MAX_SCREEN_HEROS];
	int mNumHeros;
	Unit mEnemys[MAX_SCREEN_ENYMYS];
	int mNumEnemys;
	Unit mBarriers[MAX_SCREEN_BARRIERS];
	int mNumBarries;
	char mGrids[MAX_SCREEN_GRID];
	
	PVEMap* mMap;

	int mRound;//»ØºÏ
	int mStarLevel;//ÐÇ¼¶
	int mGolds;
	int mFrontRow;
};

class PVPBattle
{

};


class BattleSystem
{
public:
	BattleSystem();
	~BattleSystem();

	void startPVE(unsigned int mapid);
private:
	PVEBattle* pve;
	PVPBattle* pvp;
};
#endif