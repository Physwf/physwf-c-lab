#ifndef _MAP_H
#define _MAP_H

#include "Unit.h"

#define NUM_GRIDS_ROW 6
#define MAX_MAP_GRID 500
#define MAX_MAP_BARRIERS 60
#define MAX_MAP_ENEMYS 100

class PVEMap
{
public:
	PVEMap();
	//PVEMap(config)
	~PVEMap();
	void init(const char* configFile);
	int getGridsByRow(int row, char* girds);
	int getBarriersByRow(int row, Unit* barriers);
	int getEnemysByRow(int row, Unit* enemys);
private:
	char mGrids[MAX_MAP_GRID];
	Unit mBrriers[MAX_MAP_BARRIERS];
	Unit mEnemys[MAX_MAP_ENEMYS];
};
#endif