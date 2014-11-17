#include "Command.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "System.h"
#include <set>

Command::Command()
{

}

Command::~Command()
{

}

CommandSequence::CommandSequence() : mCurCmd(NULL)
{

}

CommandSequence::~CommandSequence()
{

}

void CommandSequence::push(Command* cmd, bool autoTrigger)
{
	mQueue.push_back(cmd);

	if (mCurCmd == NULL)
	{
		mCurCmd = mQueue.front();
		if (autoTrigger) trigger();
		mQueue.pop_front();
	}
}

bool CommandSequence::tick(float delta)
{
	if (mCurCmd)
	{
		if (mCurCmd->tick(delta))
		{
			if (mQueue.size())
			{
				mCurCmd = mQueue.front();
				mCurCmd->trigger();
				mQueue.pop_front();
			}
			else
			{
				mCurCmd = NULL;
				return true;
			}
		}
	}
	return false;
}

void CommandSequence::trigger()
{
	mCurCmd->trigger();
}

CommandSequence* CommandSequence::create()
{
	return new CommandSequence();
}


/**
CommandAttck
**/

CommandSkill::CommandSkill()
{
	mDuration = 2.0;
	mNow = 0;
}

CommandSkill::~CommandSkill()
{

}

bool CommandSkill::tick(float delta)
{
	mNow += delta;
	
	for (std::vector<Effect*>::iterator it = mEffects.begin(); it != mEffects.end(); )
	{
		if ((*it)->tick(delta))
		{
			it = mEffects.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (mEffects.size() == 0) return true;
	/*
	if (mEffect->tick(delta))
	{
		return true;
	}
	*/
	return false;
}

void CommandSkill::trigger()
{
	//mEffect->fire();
	for (std::vector<Effect*>::iterator it = mEffects.begin(); it != mEffects.end(); it++)
	{
		(*it)->fire();
	}
}

void CommandSkill::addEffect(Effect* effect)
{
	mEffects.push_back(effect);
}

Command* CommandSkill::create(SkillResult* result)
{
	if (result->skill.track == SKILL_TRACK_HACK)
	{
		return createHack(result);
	}
	else if (result->skill.track == SKILL_TRACK_BULLET)
	{
		return createBullet(result);
	}
	else if (result->skill.track == SKILL_TRACK_FIXXED)
	{
		return createFixed(result);
	}
	else if (result->skill.track == SKILL_TRACK_ARC)
	{
		return createArc(result);
	}
	return NULL;
}

Command* CommandSkill::createHack(SkillResult* result)
{
	CommandSequence *seq = CommandSequence::create();
	CommandSkill* skill = new CommandSkill();
	skill->addEffect(HackEffect::create(result->skill.effect, result->giver, result->recipients[0]));
	seq->push(skill, false);
	CommandHit* hit = CommandHit::create(result->recipients[0]);
	seq->push(hit, false);
	Actor* victim = Engine::world->getActor(result->recipients[0]);
	if (result->value != 0)
	{
		CommandProgress* progress = CommandProgress::create(result->value[0], victim);
		seq->push(progress, false);
	}
	
	if (result->healthLeft[0] <= 0)
	{
		CommandDie* die = CommandDie::create(victim);
		seq->push(die, false);
	}
	
	return seq;
}

Command* CommandSkill::createBullet(SkillResult* result)
{
	CommandParallel* cmds = CommandParallel::create();
	for (int i = 0; i < result->numRecipients; i++)
	{
		CommandSequence * seq = CommandSequence::create();
		CommandSkill* skill = new CommandSkill();
		skill->addEffect(BulletEffect::create(result->skill.effect, result->giver, result->recipients[i]));
		seq->push(skill, false);
		CommandHit* hit = CommandHit::create(result->recipients[i]);
		seq->push(hit, false);
		Actor* victim = Engine::world->getActor(result->recipients[i]);
		if (result->value[i] != 0)
		{
			CommandProgress* progress = CommandProgress::create(result->value[i], victim);
			seq->push(progress, false);
		}
		
		if (result->healthLeft[i] <= 0)
		{
			CommandDie* die = CommandDie::create(victim);
			seq->push(die, false);
		}
		cmds->addCommand(seq);
		
	}
	return cmds;
}

Command* CommandSkill::createFixed(SkillResult* result)
{
	CommandParallel* cmds = CommandParallel::create();

	CommandSkill* skill = new CommandSkill();
	
	Actor* attacker = Engine::world->getActor(result->giver);

	for (int i = 0; i < result->skill.range2.numGSets; i++)
	{
		ID cid = result->skill.range2.gSets[i];
		GSet path;
		Config::skill->fill(&path, cid);
		FrisbeeEffect* fEffect = FrisbeeEffect::create(result->skill.effect, attacker->position());
		bool flag = false;
		CommandSequence* seq = NULL;
		float interval = 0;
		
		for (int j = 0; j < path.numElements; j++)
		{
			char ox = path.elements[j].x; 
			char oy = path.elements[j].y;
			
			bool needbreak = false;
			interval += .1f;
			Actor* actor = Engine::world->getActor(ccp(ox * GRID_SIZE + attacker->position()->x, oy * GRID_SIZE + attacker->position()->y));
			for (int k = 0; k < result->numRecipients; k++)
			{
				if (actor != NULL && result->recipients[k] == actor->iid() && result->set[k] == i)
				{
					flag = true;
					if (actor->isBarrier())
					{
						seq = CommandSequence::create();
						CommandWait* wait = CommandWait::create(interval);
						CommandHit* hit = CommandHit::create(actor->iid());
						seq->push(wait, false);
						seq->push(hit, false);
						fEffect->addNode(ox, oy);
						needbreak = true;
					}
					else
					{
						seq = CommandSequence::create();
						CommandWait* wait = CommandWait::create(interval);
						CommandHit* hit = CommandHit::create(actor->iid());
						seq->push(wait, false);
						seq->push(hit, false);
						CommandProgress* progress = CommandProgress::create(result->value[k], actor);
						seq->push(progress, false);
					}

					if (result->healthLeft[k] <= 0)
					{
						CommandDie* die = CommandDie::create(actor);
						seq->push(die, false);
					}

					cmds->addCommand(seq);
				}
			}
			if (attacker->getData()->positon.x + ox > NUM_GRIDS_ROW) needbreak = true;
			if (attacker->getData()->positon.x + ox < 0) needbreak = true;
			if (needbreak) break;
			fEffect->addNode(ox, oy);
		}
		skill->addEffect(fEffect);
	}
	cmds->addCommand(skill);
	return cmds;
}

Command* CommandSkill::createArc(SkillResult* result)
{
	CommandParallel * cmds = CommandParallel::create();
	for (int i = 0; i < result->numRecipients; i++)
	{
		CommandSequence* seq = CommandSequence::create();
		CommandSkill* skill = new CommandSkill();
		skill->addEffect(ArcEffect::create(result->skill.effect, result->giver, result->recipients[i]));
		seq->push(skill, false);
		CommandHeal* heal = CommandHeal::create(result->recipients[i]);
		seq->push(heal, false);
		if (result->value != 0)
		{
			Actor* victim = Engine::world->getActor(result->recipients[i]);
			CommandProgress* progress = CommandProgress::create(result->value[i], victim);
			seq->push(progress,false);
		}
		cmds->addCommand(seq);
	}
	return cmds;
}

/*CommandHit*/
CommandHit::CommandHit()
{

}

CommandHit::~CommandHit()
{

}

bool CommandHit::tick(float delta)
{
	return mTint->isDone();
}

void CommandHit::trigger()
{
	mActorSprite->runAction(mTint);
	mHitEmitter->setPosition(mActorSprite->getPosition());
	Engine::world->pve()->layerEffect()->addChild(mHitEmitter);
}

CommandHit* CommandHit::create(ID iid)
{
	CommandHit* hit = new CommandHit();
	Actor* actor = Engine::world->getActor(iid);
	hit->mActorSprite = actor->sprite();
	CCTintTo* tintTo = CCTintTo::create(0.1f, 50, 0, 0);
	tintTo->retain();
	CCReverseTime *tintBack = CCReverseTime::create(tintTo);
	tintBack->retain();
	hit->mTint = CCSequence::createWithTwoActions(tintTo, tintBack);
	hit->mTint->retain();
	hit->mHitEmitter = CCParticleSystemQuad::create("Data/hit.xml");
	hit->mHitEmitter->retain();
	return hit;
}

/*CommandHeal*/

CommandHeal::CommandHeal()
{

}

CommandHeal::~CommandHeal()
{

}

bool CommandHeal::tick(float delta)
{
	mAnimSprite->setPosition(mActor->sprite()->getPosition());
	return mAction->isDone();
}

void CommandHeal::trigger()
{
	Engine::world->pve()->layerEffect()->addChild(mAnimSprite);
	mAnimSprite->runAction(mAction);
}

CommandHeal* CommandHeal::create(ID iid)
{
	CommandHeal* heal = new CommandHeal();
	heal->mActor = Engine::world->getActor(iid);
	CCAnimation* anim = ResourceManager::instance()->getAnimation("heal");
	heal->mAction = CCAnimate::create(anim);
	heal->mAction->retain();
	heal->mAnimSprite = CCSprite::create();
	heal->mAnimSprite->setPosition(heal->mActor->sprite()->getPosition());
	heal->mAnimSprite->retain();
	return heal;
}

/*CommandProgress*/

CommandProgress::CommandProgress(int delta)
{
	mDelta = delta;
}

CommandProgress::~CommandProgress()
{

}

bool CommandProgress::tick(float delta)
{
	mCurrent += mDelta/10.0;

	(mObject->*mOnProgressDelta)(mDelta / 10.0);

	if (mCurrent == mDelta) return true;
	return false;
}

void CommandProgress::trigger()
{
	mCurrent = 0;
}

CommandProgress* CommandProgress::create(int delta, Actor* actor)
{
	CommandProgress* progress = new CommandProgress(delta);
	progress->mObject = actor;
	progress->mOnProgressDelta = (OnProgressDelta)&Actor::updateHealth;
	return progress;
}

CommandProgress* CommandProgress::create(int delta, DWObject* object, OnProgressDelta onProgressDelta)
{
	CommandProgress* progress = new CommandProgress(delta);
	progress->mObject = object;
	progress->mOnProgressDelta = onProgressDelta;
	return progress;
}

/*CommandMove*/
CommandMove::CommandMove(Actor* actor)
{
	mActor = actor;
	mMove = CCMoveTo::create(0.2f, mPos);
	mMove->retain();
	mDelay = CCDelayTime::create(0.2f);
	mDelay->retain();
	mAction = CCSequence::createWithTwoActions(mDelay, mMove);
	mAction->retain();
}

CommandMove::~CommandMove()
{
	mDelay->release();
	mMove->release();
	mAction->release();
}

bool CommandMove::tick(float delta)
{
	return mAction->isDone();
}

void CommandMove::trigger()
{
	mActor->sprite()->runAction(mAction);
}

CommandMove* CommandMove::create(Actor* actor)
{
	CommandMove* move = new CommandMove(actor);
	move->mPos = *actor->position();
	srand(time(NULL) / (rand() % time(NULL)));
	float delay = 0.1 * ((float)(rand() % 10) / 10.0)+0.1;
	CCLog("delay:%f\n",delay);
	move->mDelay->initWithDuration(delay);
	move->mMove->initWithDuration(0.2f, move->mPos);
	move->mAction->initWithTwoActions(move->mDelay, move->mMove);
	return move;
}


/*CommandParallel*/
CommandParallel* CommandParallel::create()
{
	return new CommandParallel();
}

bool CommandParallel::tick(float delta)
{
	for (std::vector<Command*>::iterator it = mCommands.begin(); it != mCommands.end(); )
	{
		if ((*it)->tick(delta))
		{
			it = mCommands.erase(it);
		}
		else
		{
			it++;
		}
	}
	return mCommands.size() == 0;
}

void CommandParallel::trigger()
{
	for (std::vector<Command*>::iterator it = mCommands.begin(); it != mCommands.end(); it++)
	{
		(*it)->trigger();
	}
}

void CommandParallel::addCommand(Command* cmd)
{
	mCommands.push_back(cmd);
}

CommandParallel::CommandParallel()
{

}

CommandParallel::~CommandParallel()
{

}

CommandScroll::CommandScroll(CCSprite* layer)
{
	mLayer = layer;
}

CommandScroll::~CommandScroll()
{

}

CommandScroll* CommandScroll::create(CCSprite* layer, StepDirection dir)
{
	CommandScroll* pScroll = new CommandScroll(layer);
	CCPoint pos = layer->getPosition();
	if (dir == FORWARD)
		pos.y -= GRID_SIZE;
	else if (dir == BACKWARD)
		pos.y += GRID_SIZE;
	pScroll->mMove = CCMoveTo::create(0.2f,pos);
	pScroll->mMove->retain();

	return pScroll;
}

bool CommandScroll::tick(float delta)
{
	return mMove->isDone();
}

void CommandScroll::trigger()
{
	mLayer->runAction(mMove);
}

CommandPVEScroll::CommandPVEScroll()
{
	
}

CommandPVEScroll::~CommandPVEScroll()
{

}

CommandPVEScroll* CommandPVEScroll::create(StepDirection dir)
{
	CommandPVEScroll* mCmd = new CommandPVEScroll();
	mCmd->mScrollCmds = CommandParallel::create();
	mCmd->mScrollCmds->addCommand(CommandScroll::create(Engine::world->pve()->layerMap(), dir));
	mCmd->mScrollCmds->addCommand(CommandScroll::create(Engine::world->pve()->layerProp(), dir));
	mCmd->mScrollCmds->addCommand(CommandScroll::create(Engine::world->pve()->layerActor(), dir));
	mCmd->mScrollCmds->addCommand(CommandScroll::create(Engine::world->pve()->layerEffect(), dir));
	return mCmd;
}

bool CommandPVEScroll::tick(float delta)
{
	return mScrollCmds->tick(delta);
}

void CommandPVEScroll::trigger()
{
	mScrollCmds->trigger();
}

CommandDashBoard::CommandDashBoard()
{

}

CommandDashBoard::~CommandDashBoard()
{

}

CommandDashBoard* CommandDashBoard::create(UIBehavior behavior)
{
	CommandDashBoard* pCmd = new CommandDashBoard();
	pCmd->mBehavior = behavior;
	return pCmd;
}

void CommandDashBoard::trigger()
{
	if (mBehavior == HIDE)
	{
		Engine::world->pve()->ui()->hideDashBoard();
	}
	else if (mBehavior == SHOW)
	{
		Engine::world->pve()->ui()->showDashBoard();
	}
}

bool CommandDashBoard::tick(float delta)
{
	return true;
}


CommandSumary::CommandSumary()
{

}

CommandSumary::~CommandSumary()
{

}

CommandSumary* CommandSumary::create(UIBehavior behavior)
{
	CommandSumary* pCmd = new CommandSumary();
	pCmd->mBehavior = behavior;
	return pCmd;
}

void CommandSumary::trigger()
{
	if (mBehavior == HIDE)
	{
		//Engine::world->pve()->showSumary();
	}
	else if (mBehavior == SHOW)
	{
		Engine::world->pve()->showSumary();
	}
}

bool CommandSumary::tick(float delta)
{
	return true;
}

CommandDie::CommandDie(Actor* actor)
{
	mActor = actor;
}

CommandDie::~CommandDie()
{

}

CommandDie* CommandDie::create(Actor* actor)
{
	CommandDie* pDie = new CommandDie(actor);
	return pDie;
}

bool CommandDie::tick(float delta)
{
	return true;
}

void CommandDie::trigger()
{
	mActor->sprite()->removeFromParent();
	Engine::world->removeActor(mActor->iid());
}

/*CommandBuff*/

CommandBuff::CommandBuff()
{

}

CommandBuff::~CommandBuff()
{

}

bool CommandBuff::tick(float delta)
{
	return true;
}

void CommandBuff::trigger()
{

}

Command* CommandBuff::create(BuffResult* result)
{
	CommandSequence * seq = CommandSequence::create();
	//to do implement command buff
	Actor* owner = Engine::world->getActor(result->owner);
	CommandProgress* progress = CommandProgress::create(result->value, owner);
	seq->push(progress, false);
	return seq;
}

CommandDrop::CommandDrop()
{

}

CommandDrop::~CommandDrop()
{

}

CommandDrop* CommandDrop::create(Prop* prop)
{
	CommandDrop* drop = new CommandDrop();
	drop->mProp = prop;
	return drop;
}

void CommandDrop::trigger()
{
	mProp->show();
}

bool CommandDrop::tick(float delta)
{
	return true;
}

/*CommandDrop*/
CommandPick::CommandPick()
{

}

CommandPick::~CommandPick()
{

}

CommandPick* CommandPick::create(Prop* prop,ID who)
{
	CommandPick* pick = new CommandPick();
	pick->mProp = prop;
	pick->mPicker = who;
	return pick;
}

void CommandPick::trigger()
{
	mProp->hide();
	System::pve->pickItem(mProp->data()->iid, mPicker);
}

bool CommandPick::tick(float delta)
{
	return true;
}

CommandShakeScreen::CommandShakeScreen() :mTime(0.0f)
{
	mOrigin = new CCPoint();
}

CommandShakeScreen::~CommandShakeScreen()
{

}

CommandShakeScreen* CommandShakeScreen::create(float am)
{
	CommandShakeScreen* pCmd = new CommandShakeScreen();
	pCmd->mAmp = am;
	return pCmd;
}

bool CommandShakeScreen::tick(float delta)
{
	float e = (1 + mTime + mTime*mTime / 2 + mTime*mTime*mTime / 6);
	float aX = mAmp * sin(mTime * 100) / e;
	float aY = mAmp * cos(mTime * 100) / e;
	CCLog("%f,%f,%f", aX, aY, mTime);
	Engine::world->pve()->layerMap()->setPosition(ccp(mOrigin->x+aX, mOrigin->y+aY));
	CCLog("x:%f,y:%f", mOrigin->x + aX, mOrigin->y + aY);
	mTime += delta;
	if (mTime > 0.03)
	{
		Engine::world->pve()->layerMap()->setPosition(*mOrigin);
		CCLog("zx:%f,zy:%f", mOrigin->x, mOrigin->y);
		return true;
	}
	return false;
}

void CommandShakeScreen::trigger()
{
	*mOrigin = Engine::world->pve()->layerMap()->getPosition();
	CCLog("ox:%f,oy:%f",mOrigin->x,mOrigin->y);
}
/*CommandWait*/
CommandWait::CommandWait() :mDuration(0.0f)
{

}

CommandWait::~CommandWait()
{

}

CommandWait* CommandWait::create(float duration)
{
	CommandWait* wait = new CommandWait();
	wait->mDuration = duration;
	return wait;
}

bool CommandWait::tick(float delta)
{
	mDuration -= delta;
	if (mDuration <= 0) return true;
	return false;
}

void CommandWait::trigger()
{

}