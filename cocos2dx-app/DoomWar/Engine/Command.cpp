#include "Command.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "System.h"

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
	mEmitter = NULL;
	mHitEmitter = NULL;
}

CommandSkill::~CommandSkill()
{

}

bool CommandSkill::tick(float delta)
{
	mNow += delta;
	if (mEffect->tick(delta))
	{
		if (mEmitter) mEmitter->stopSystem();
		if (mHitEmitter) mHitEmitter->resetSystem();
		return true;
	}
	if (mEmitter) mEmitter->setPosition(mEffect->getPosition());
	return false;
}

void CommandSkill::trigger()
{
	mEffect->fire();
	if (mEmitter) mEmitter->setPosition(mEffect->getPosition());
}

Command* CommandSkill::create(SkillResult* result)
{
	CommandSequence * seq = CommandSequence::create();
	CommandSkill* cmd = new CommandSkill();
	cmd->mHitEmitter = CCParticleSystemQuad::create("Data/hit.xml");
	Engine::world->pve()->layerEffect()->addChild(cmd->mHitEmitter);
	
	//cmd->mHitEmitter = ParticleHitEmitter::create();

	Actor* target = Engine::world->getActor(result->recipient);
	cmd->mHitEmitter->setPosition(*target->position());
	cmd->mHitEmitter->stopSystem();

	if (result->skill.track == SKILL_TRACK_HACK)
	{
		cmd->mEffect = HackEffect::create(result->skill.effect, result->giver, result->recipient);
	}
	else if (result->skill.track == SKILL_TRACK_BULLET)
	{
		cmd->mEffect = BulletEffect::create(result->skill.effect, result->giver, result->recipient);
		cmd->mEmitter = CCParticleSystemQuad::create("Data/trace.xml");
		cmd->mEmitter->setEmissionRate(40);
		Engine::world->pve()->layerEffect()->addChild(cmd->mEmitter);
		//cmd->mEmitter = ParticleTraceEmitter::create();
	}
	else if (result->skill.track == SKILL_TRACK_FIXXED)
	{
		for (int i = 0; i < result->skill.paths->numPaths; i++)
		{
			Path *path = &result->skill.paths->paths[i];
			cmd->mEffect = FrisbeeEffect::create(result->skill.effect, path);
		}
	}
	else if (result->skill.track == SKILL_TRACK_ARC)
	{
		cmd->mEffect = ArcEffect::create(result->skill.effect, result->giver, result->recipient);
	}
	else
	{
		cmd->mEffect = BulletEffect::create(result->skill.effect, result->giver, result->recipient);
	}
	seq->push(cmd,false);
	if (result->value != 0)
	{
		Actor* victim = Engine::world->getActor(result->recipient);
		CommandProgress* progress = CommandProgress::create(result->value, victim);
		seq->push(progress, false);
	}
	return seq;
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