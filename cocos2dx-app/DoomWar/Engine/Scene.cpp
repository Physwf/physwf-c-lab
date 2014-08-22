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

	std::map<ID, Unit*>* barriers = System::pve->barriers();
	for (std::map<ID, Unit*>::iterator it = barriers->begin(); it != barriers->end(); it++)
	{
		Actor* actor = new Actor(mPVEScene);
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}

	std::map<ID, Unit*>* enemys = System::pve->enemys();
	for (std::map<ID, Unit*>::iterator it = enemys->begin(); it != enemys->end(); it++)
	{
		Actor* actor = new Actor(mPVEScene);
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}
	CCDirector::sharedDirector()->replaceScene(mPVEScene->scene());

	System::pve->start();

	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_SUCCESS, this, EventListener(&Scene::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_FAILED, this, EventListener(&Scene::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_ATTACK_RESULT, this, EventListener(&Scene::onBattleAttakResult));
}

void Scene::onBattleMoveResult(Event *event)
{
	if (event->type == PVEBattle::BATTLE_MOVE_SUCCESS)
	{
		ID* herosToMove = (ID*)event->data;
		while (*herosToMove)
		{
			(*mActors)[(*herosToMove)]->updatePosition();
			herosToMove++;
		}
	}
	else if (event->type == PVEBattle::BATTLE_MOVE_FAILED)
	{
		ID* heroCantMove = (ID*)event->data;
	}
	
}

void Scene::onBattleAttakResult(Event* event)
{
	AttackResult* results = (AttackResult*)event->data;
	//while (results)
	{
		switch (results->type)
		{
		case ATTACK_TYPE_PHYSICAL:
		{
			Actor* victim = (*mActors)[results->victim];
			victim->updateHealth(results->value);
		}
		}
		results++;
	}
}

void Scene::leavePVEMap()
{

}


