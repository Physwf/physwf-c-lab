#ifndef _MAP_H
#define _MAP_H

#include "Unit.h"
#include "dwtype.h"
#include <map>

#define NUM_GRIDS_ROW 6
#define MAX_MAP_GRID 500
#define MAX_MAP_BARRIERS 60
#define MAX_MAP_ENEMYS 100

class PVEMapData
{
public:
	PVEMapData();
	//PVEMap(config)
	~PVEMapData();
	void init(const char* configFile);
	int getGridsByRow(int row, char* girds);
	int getBarriersByRow(int row, std::map<ID, Unit*>*,ID*);
	int getEnemysByRow(int row, std::map<ID, Unit*>*,ID*);

	ID cid() const;
private:
	char mGrids[MAX_MAP_GRID];
	std::map<int, ID> mBarriers;
	std::map<int, ID> mEnemys;
	//ID mBrriers[MAX_MAP_BARRIERS];
	//ID mEnemys[MAX_MAP_ENEMYS];
	ID mCID;
};
#endif