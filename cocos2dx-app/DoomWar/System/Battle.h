#ifndef _BATTLE_H
#define _BATTLE_H

#include "Unit.h"

#define MAX_STAR_LEVEL 3

class PVEBattle
{
public:
	PVEBattle();
	~PVEBattle();
	void start();
	void pause();
	void end();
	void update(unsigned int eclipse);
private:
	void updateStarLevel();

private:
	Unit heros[MAX_HEROS_IN_A_BATTLE];
	int numHero;
	Unit enemys[MAX_ENYMYS_IN_A_BATTLE];
	int numEnemys;
	int round;//»ØºÏ
	int starLevel;//ÐÇ¼¶
	int golds;
};

class PVPBattle
{

};

#endif