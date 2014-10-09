#ifndef _SCENE_H
#define _SCENE_H

#include "Actor.h"
#include "Prop.h"
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

	void enterPVEMap(ID mapid, Unit** heros, int numHeros);
	void leavePVEMap();

	void enterPVPMap(ID mapid);
	void leavePVPMap();

	Actor* getActor(ID iid);
	Actor* getActorByGrid(const CCPoint &pos);

	PVEBattleScene* pve();
private:
	void onEnterPVEBattle(Event* event);
	void onBattleMoveResult(Event* event);
	void onBattleAttakResult(Event* event);
	void onUnitFlop(Event* event);
private:
	std::map<ID, Actor*> *mActors;
	std::map<ID, Prop*> *mProps;

	DWLoadingScene* mLoading;
	PVEBattleScene* mPVEScene;
};
#endif