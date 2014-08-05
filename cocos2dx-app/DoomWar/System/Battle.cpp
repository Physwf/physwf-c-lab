#include "Battle.h"
#include <string.h>

PVEBattle::PVEBattle()
{
	memset(heros, 0, sizeof(heros));
	numHero = 0;
	memset(enemys, 0, sizeof(enemys));
	numEnemys = 0;
	round = 0;
	starLevel = MAX_STAR_LEVEL;
	golds = 0;
}

PVEBattle::~PVEBattle()
{

}
