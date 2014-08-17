#include "Scene.h"
#include <string.h>
#include "DWLoadingScene.h"
#include "PVEBattleScene.h"
#include "System.h"

Scene::Scene() :mLoading(NULL), mPVEScene(NULL)
{
}

Scene::~Scene()
{

}

void Scene::initialize()
{
	System::pve->initialize();
}

void Scene::enterPVEMap(ID mapid, Unit* heros, int numHeros)
{
	System::pve->addEventListener(PVEBattle::BATTLE_ENTER_MAP, this, EventListener(&Scene::onEnterPVEBattle));
	System::pve->enter(mapid, heros, numHeros);
}

void Scene::onEnterPVEBattle(Event* event)
{
	//to do add enemys and barriers
	mPVEScene = PVEBattleScene::create();
	//to do load map

	mActors = new std::map<ID, Actor*>();
	std::map<ID,Unit*>* heros = System::pve->heros();
	for (std::map<ID,Unit*>::iterator it=heros->begin(); it != heros->end(); it++)
	{
		Actor* actor = new Actor(mPVEScene);
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}

	CCDirector::sharedDirector()->replaceScene(mPVEScene->scene());

	System::pve->start();
}

void Scene::leavePVEMap()
{

}


