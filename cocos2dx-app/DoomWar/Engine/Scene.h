#ifndef _SCENE_H
#define _SCENE_H

#include "Actor.h"
#include "DWLoadingScene.h"
#include "PVEBattleScene.h"
#include "dwtype.h"
#include "EventDispatcher.h"

#include <map>

class Scene : public DWObject
{
public:
	Scene();
	~Scene();

	void initialize();

	void enterPVEMap(ID mapid, Unit* heros, int numHeros);
	void leavePVEMap();

	void enterPVPMap(ID mapid);
	void leavePVPMap();
private:
	void onEnterPVEBattle(Event* event);
private:
	std::map<ID, Actor*> *mActors;

	DWLoadingScene* mLoading;
	PVEBattleScene* mPVEScene;

};
#endif