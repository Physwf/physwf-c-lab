#include "World.h"
#include <string.h>
#include "PVEView.h"
#include "System.h"
#include "Game.h"

World::World() : mPVEView(NULL)
{
	
}

World::~World()
{

}

void World::initialize()
{
	System::pve->initialize();

	mPVEView = PVEView::create();
	mPVEView->retain();
}

void World::enterPVEView(ID mapid, Unit** heros, int numHeros)
{
	System::pve->addEventListener(PVEBattle::BATTLE_ENTER_MAP, this, EventListener(&World::onEnterPVEBattle));
	System::pve->enter(mapid, heros, numHeros);
}

void World::onEnterPVEBattle(Event* event)
{
	//to do add enemys and barriers
	
	//to do load map

	mActors = new std::map<ID, Actor*>();
	std::map<ID,Unit*>* heros = System::pve->heros();
	for (std::map<ID,Unit*>::iterator it=heros->begin(); it != heros->end(); it++)
	{
		Actor* actor = new Actor(mPVEView->layerActor());
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}

	std::map<ID, Unit*>* barriers = System::pve->barriers();
	for (std::map<ID, Unit*>::iterator it = barriers->begin(); it != barriers->end(); it++)
	{
		Actor* actor = new Actor(mPVEView->layerActor());
		actor->setData(it->second);
		actor->hideBlood();
		(*mActors)[actor->iid()] = actor;
	}

	std::map<ID, Unit*>* enemys = System::pve->enemys();
	for (std::map<ID, Unit*>::iterator it = enemys->begin(); it != enemys->end(); it++)
	{
		Actor* actor = new Actor(mPVEView->layerActor());
		actor->setData(it->second);
		(*mActors)[actor->iid()] = actor;
	}

	mProps = new std::map<ID, Prop*>();

	//CCDirector::sharedDirector()->replaceScene(mPVEView->scene());

	Game::instance()->replaceView(mPVEView);

	System::pve->start();

	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_SUCCESS, this, EventListener(&World::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_HERO_SUCESS, this, EventListener(&World::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_MOVE_FAILED, this, EventListener(&World::onBattleMoveResult));
	System::pve->addEventListener(PVEBattle::BATTLE_ATTACK_RESULT, this, EventListener(&World::onBattleAttakResult));
	System::pve->addEventListener(PVEBattle::BATTLE_STEP_CLEAR, this, EventListener(&World::onBattleStepClear));
	System::pve->addEventListener(PVEBattle::BATTLE_UNIT_FLOP, this, EventListener(&World::onUnitFlop));
	System::bag->addEventListener(Bag::BAG_GOLD_CHANGE, this, EventListener(&World::onGoldChange));
	System::pve->addEventListener(PVEBattle::BATTLE_STEP, this, EventListener(&World::onPVEStep));
	System::pve->addEventListener(PVEBattle::BATTLE_SUCCESS, this, EventListener(&World::onBattleSuccess));
}

void World::onBattleMoveResult(Event *event)
{
	
	if (event->type == PVEBattle::BATTLE_MOVE_SUCCESS)
	{
		MoveResult* result = (MoveResult*)event->data;
		CommandDashBoard* hide = CommandDashBoard::create(HIDE);
		mPVEView->addCommand(hide);

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
		
		CommandPVEScroll* cmd = CommandPVEScroll::create(result->dir);
		cmds->addCommand(cmd);
		i = 0;
		while (result->skills[i].giver)
		{
			Command* skill = CommandSkill::create(&result->skills[i]);
			cmds->addCommand(skill);
			i++;
		}
		i = 0;
		while (result->buffs[i].owner)
		{
			Command* buff = CommandBuff::create(&result->buffs[i]);
			cmds->addCommand(buff);
			i++;
		}
		mPVEView->addCommand(cmds);
		
		i = 0;
		while (iid = result->comeIntoView[i])
		{
			Actor* actor = new Actor(mPVEView->layerActor());
			Unit* unit = System::pve->getUnit(iid);
			CCAssert(unit != NULL, "Unit is null!");
			actor->setData(unit);
			if (actor->isBarrier()) actor->hideBlood();
			(*mActors)[actor->iid()] = actor;
			i++;
		}
		i = 0;
		CommandParallel* enemysMove = CommandParallel::create();
		while (iid = result->enemys[i])
		{
			(*mActors)[iid]->calculateNextPosition();
			CommandMove *move = CommandMove::create((*mActors)[iid]);
			enemysMove->addCommand(move);
			i++;
		}
		mPVEView->addCommand(enemysMove);
		i = 0;
		CommandParallel* picks = CommandParallel::create();
		while (iid = result->pick[i])
		{
			std::map<ID, Prop*>::iterator it;
			if ((it = mProps->find(iid)) != mProps->end())
			{
				CommandPick* pCmd = CommandPick::create(it->second, result->picker[i]);
				picks->addCommand(pCmd);
				mProps->erase(it);
			}
			i++;
		}
		mPVEView->addCommand(picks);
	}
	else if (event->type == PVEBattle::BATTLE_MOVE_FAILED)
	{
		//ID* heroCantMove = (ID*)event->data;
	}
	else if (event->type == PVEBattle::BATTLE_MOVE_HERO_SUCESS)
	{
		CommandDashBoard* hide = CommandDashBoard::create(HIDE);
		mPVEView->addCommand(hide);

		MoveResult *result = (MoveResult *)event->data;
		ID iid = result->moveUnits[0];
		(*mActors)[iid]->updatePosition();
		int i = 0;
		CommandParallel* enemysMove = CommandParallel::create();
		while (iid = result->enemys[i])
		{
			(*mActors)[iid]->calculateNextPosition();
			CommandMove *move = CommandMove::create((*mActors)[iid]);
			enemysMove->addCommand(move);
			i++;
		}
		mPVEView->addCommand(enemysMove);
		i = 0;
		CommandParallel* picks = CommandParallel::create();
		while (iid = result->pick[i])
		{
			std::map<ID, Prop*>::iterator it;
			if ((it = mProps->find(iid)) != mProps->end())
			{
				CommandPick* pCmd = CommandPick::create(it->second, result->picker[i]);
				picks->addCommand(pCmd);
				mProps->erase(it);
				//System::pve->pickItem(iid, result->picker[i]);
			}
			i++;
		}
		mPVEView->addCommand(picks);
	}
}

void World::onBattleAttakResult(Event* event)
{
	AttackResult* aResults = (AttackResult*)event->data;
	
	while (aResults->count)
	{
		int i = 0;
		while (i < aResults->count)
		{
			SkillResult* sResult = aResults->results + i;
			Command* attack = CommandSkill::create(sResult);
			mPVEView->addCommand(attack);
			Command* shake = CommandShakeScreen::create(16.0f);
			mPVEView->addCommand(shake);
			CommandParallel* dies = CommandParallel::create();
			for (int j = 0; j < sResult->numRecipients; j++)
			{
				Actor* victim = getActor(sResult->recipients[j]);
				//CommandProgress* progress = CommandProgress::create(sResult->value, victim);
				//mPVEScene->addCommand(progress);
				if (sResult->healthLeft <= 0)
				{
					CommandDie* die = CommandDie::create(victim);
					dies->addCommand(die);
					mActors->erase(mActors->find(sResult->recipients[j]));
				}
			}
			mPVEView->addCommand(dies);
			i++;
		}
		i = 0;
		while (i < aResults->numLoot)
		{
			Item* loot = System::pve->getItem(aResults->loots[i]);
			if (loot->pick == ITEM_PICK_TYPE_STEP)
			{
				Prop* prop = new Prop(mPVEView->layerProp());
				prop->bindData(loot);
				(*mProps)[loot->iid] = prop;
				CommandDrop* drop = CommandDrop::create(prop);
				mPVEView->addCommand(drop);
			}
			else if (loot->pick == ITEM_PICK_TYPE_AUTO)
			{
				Prop* prop = new Prop(mPVEView->layerProp());
				prop->bindData(loot);
				CommandPick* pCmd = CommandPick::create(prop, 0);
				mPVEView->addCommand(pCmd);
			}
			i++;
		}
		aResults++;
	}
	CommandDashBoard* show = CommandDashBoard::create(SHOW);
	mPVEView->addCommand(show);
}
void World::onBattleStepClear(Event* event)
{
	CommandDashBoard* show = CommandDashBoard::create(SHOW);
	mPVEView->addCommand(show);
}

void World::onUnitFlop(Event* e)
{
	ID iid = *(ID*)e->data;
	Actor* actor = new Actor(mPVEView->layerActor());
	Unit* unit = System::pve->getUnit(iid);
	CCAssert(unit != NULL, "Unit is null!");
	actor->setData(unit);
	if (actor->isBarrier()) actor->hideBlood();
	(*mActors)[actor->iid()] = actor;
}

void World::onGoldChange(Event* event)
{
	mPVEView->updateGold(System::bag->getGold());
}

void World::onPVEStep(Event* event)
{
	mPVEView->updateStep(System::pve->step());
}

void World::onBattleSuccess(Event* event)
{
	CommandSumary *pSum = CommandSumary::create(SHOW);
	mPVEView->addCommand(pSum);
}


void World::leavePVEView()
{

}

Actor* World::getActor(ID iid)
{
	std::map<ID, Actor*>::iterator res = mActors->find(iid);
	assert(res != mActors->end());
	return res->second;
}

PVEView* World::pve()
{
	return mPVEView;
}

Actor* World::getActorByGrid(const CCPoint &pos)
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


