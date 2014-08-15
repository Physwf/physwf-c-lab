#ifndef _MAP_H
#define _MAP_H

#include "Actor.h"
#include "DWLoadingScene.h"
#include "PVEBattleScene.h"

class Scene
{
public:
	Scene();
	~Scene();

	void initialize();

	void showLoading();

	void enterPVEMap(unsigned int mapid);
	void leavePVEMap();

	void enterPVPMap(unsigned int mapid);
	void leavePVPMap();
private:
	Actor* mActors[MAX_ACTORS_IN_MAP];
	int numActors;

	DWLoadingScene* mLoading;
	PVEBattleScene* mPVEScene;

};
#endif