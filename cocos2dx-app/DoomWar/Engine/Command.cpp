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
}

CommandSkill::~CommandSkill()
{

}

bool CommandSkill::tick(float delta)
{
	mNow += delta;
	if (mEffect->tick(delta))
	{
		return true;
	}
	return false;
}

void CommandSkill::trigger()
{
	mEffect->fire();
}

Command* CommandSkill::create(SkillResult* result)
{
	CommandSequence * seq = CommandSequence::create();
	CommandSkill* cmd = new CommandSkill();
	if (result->skill.track == SKILL_TRACK_HACK)
	{
		cmd->mEffect = HackEffect::create(result->skill.effect, result->giver, result->recipient);
	}
	else if (result->skill.track == SKILL_TRACK_BULLET)
	{
		cmd->mEffect = BulletEffect::create(result->skill.effect, result->giver, result->recipient);
	}
	else if (result->skill.track == SKILL_TRACK_FIXXED)
	{

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
		Actor* victim = Engine::scene->getActor(result->recipient);
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
	//mDelay = CCDelayTime::create(0.2f);
	//mAction = CCSequence::create(mDelay, mMove);
	//mAction->retain();
}

CommandMove::~CommandMove()
{
	mDelay->release();
	mMove->release();
	mAction->release();
}

bool CommandMove::tick(float delta)
{
	return mMove->isDone();
}

void CommandMove::trigger()
{
	mActor->sprite()->runAction(mMove);
}

CommandMove* CommandMove::create(Actor* actor)
{
	CommandMove* move = new CommandMove(actor);
	move->mPos = *actor->position();
	srand(time(NULL));
	//move->mDelay->initWithDuration(0.2 * (rand()%10/10.0));
	move->mMove->initWithDuration(0.2f, move->mPos);
	//move->mAction->initWithTwoActions(move->mDelay, move->mMove);
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

CommandScroll::CommandScroll(CCLayer* layer)
{
	mLayer = layer;
}

CommandScroll::~CommandScroll()
{

}

CommandScroll* CommandScroll::create(CCLayer* layer, StepDirection dir)
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
	Actor* owner = Engine::scene->getActor(result->owner);
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

CommandPick* CommandPick::create(Prop* prop)
{
	CommandPick* pick = new CommandPick();
	pick->mProp = prop;
	return pick;
}

void CommandPick::trigger()
{
	mProp->hide();
}

bool CommandPick::tick(float delta)
{
	return true;
}