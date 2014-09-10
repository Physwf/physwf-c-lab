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

void Scene::enterPVEMap(ID mapid, Unit** heros, int numHeros)
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
		Actor* actor = new Actor(mPVEScene->layerActor());
		actor->setData(it->second,true);
		(*mActors)[actor->iid()] = actor;
	}

	std::map<ID, Unit*>* barriers = System::pve->barriers();
	for (std::map<ID, Unit*>::iterator it = barriers->begin(); it != barriers->end(); it++)
	{
		Actor* actor = new Actor(mPVEScene->layerActor());
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}

	std::map<ID, Unit*>* enemys = System::pve->enemys();
	for (std::map<ID, Unit*>::iterator it = enemys->begin(); it != enemys->end(); it++)
	{
		Actor* actor = new Actor(mPVEScene->layerActor());
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}
	CCDirector::sharedDirector()->replaceScene(mPVEScene->scene());

	System::pve->start();

	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_SUCCESS, this, EventListener(&Scene::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_HERO_SUCESS, this, EventListener(&Scene::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_FAILED, this, EventListener(&Scene::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_ATTACK_RESULT, this, EventListener(&Scene::onBattleAttakResult));
}

void Scene::onBattleMoveResult(Event *event)
{
	if (event->type == PVEBattle::BATTLE_MOVE_SUCCESS)
	{
		MoveResult* result = (MoveResult*)event->data;
		CommandParallel* cmds = CommandParallel::create();
		int i = 0;
		ID iid;
		while (iid = result->moveUnits[i])
		{
			(*mActors)[iid]->calculateNextPosition();
			CommandMove *move = CommandMove::create((*mActors)[iid]);
			cmds->addCommand(move);
			i++;
		}
		CommandScroll* cmd = CommandScroll::create(mPVEScene, result->dir);
		cmds->addCommand(cmd);
		mPVEScene->addCommand(cmds);
		
		i = 0;
		while (iid = result->comeIntoView[i])
		{
			Actor* actor = new Actor(mPVEScene->layerActor());
			Unit* unit = System::pve->getUnit(iid);
			CCAssert(unit != NULL, "Unit is null!");
			actor->setData(unit);
			(*mActors)[actor->iid()] = actor;
			i++;
		}
	}
	else if (event->type == PVEBattle::BATTLE_MOVE_FAILED)
	{
		//ID* heroCantMove = (ID*)event->data;
	}
	else if (event->type == PVEBattle::BATTLE_MOVE_HERO_SUCESS)
	{
		ID* iid = (ID*)event->data;
		(*mActors)[(*iid)]->updatePosition();
	}
}

void Scene::onBattleAttakResult(Event* event)
{
	AttackResult* results = (AttackResult*)event->data;
	while (results->attacker)
	{
		CommandAttck* attack = CommandAttck::create(results);
		mPVEScene->addCommand(attack);
		Actor* victim = getActor(results->victim);
		CommandProgress* progress = CommandProgress::create(results->value, victim);
		mPVEScene->addCommand(progress);
		if (results->healthLeft <= 0)
		{
			CommandDie* die = CommandDie::create(victim);
			mPVEScene->addCommand(die);
			mActors->erase(mActors->find(results->victim));
		}
		
		results++;
	}
}

void Scene::leavePVEMap()
{

}

Actor* Scene::getActor(ID iid)
{
	return (*mActors)[iid];
}

PVEBattleScene* Scene::pve()
{
	return mPVEScene;
}

Actor* Scene::getActorByGrid(const CCPoint &pos)
{
	CCRect bounds;
	for (std::map<ID, Actor*>::iterator it = mActors->begin(); it != mActors->end(); it++)
	{

		bounds.origin = it->second->sprite()->getPosition();
		bounds.origin.x -= GRID_SIZE / 2;
		bounds.origin.y -= GRID_SIZE / 2;
		bounds.size = CCSize(GRID_SIZE,GRID_SIZE);
		if (bounds.containsPoint(pos)) return it->second;
	}
	return NULL;
}


