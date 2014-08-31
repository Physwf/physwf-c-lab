#include "Command.h"
#include "Engine.h"
#include "ResourceManager.h"

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

void CommandSequence::push(Command* cmd)
{
	mQueue.push_back(cmd);

	if (mCurCmd == NULL)
	{
		mCurCmd = mQueue.front();
		mCurCmd->trigger();
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

}

CommandSequence* CommandSequence::create()
{
	return new CommandSequence();
}


/**
CommandAttck
**/

CommandAttck::CommandAttck()
{
	mDuration = 2.0;
	mNow = 0;
}

CommandAttck::~CommandAttck()
{

}

bool CommandAttck::tick(float delta)
{
	mNow += delta;
	if (mEffect->tick(delta))
	{
		return true;
	}
	return false;
}

void CommandAttck::trigger()
{
	mEffect->fire();
}

CommandAttck* CommandAttck::create(AttackResult* result)
{
	CommandAttck* cmd = new CommandAttck();
	cmd->mEffect = HackEffect::create(0, result->attacker, result->victim);
	return cmd;
}

/*CommandProgress*/

CommandProgress::CommandProgress(ID actor, int delta)
{
	mActor = Engine::scene->getActor(actor);
	mHealth = mActor->health();
	mDelta = delta;
}

CommandProgress::~CommandProgress()
{

}

bool CommandProgress::tick(float delta)
{
	mCurrent += mDelta / 10;
	if (mDelta >= 0)
	{
		mCurrent = mCurrent >= mHealth ? mHealth : mCurrent;
	}
	else
	{
		mCurrent = mCurrent < mHealth ? mHealth : mCurrent;
	}

	mActor->updateHealth(mCurrent);

	if (mCurrent == mHealth) return true;
	return false;
}

void CommandProgress::trigger()
{
	mCurrent = mHealth - mDelta;
}

CommandProgress* CommandProgress::create(ID actor, int delta)
{
	CommandProgress* progress = new CommandProgress(actor,delta);
	return progress;
}


CommandMove::CommandMove(Actor* actor)
{
	mActor = actor;
}

CommandMove::~CommandMove()
{
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
	CCPoint *pos = actor->position();
	move->mAction = CCMoveTo::create(0.2f, *pos);
	move->mAction->retain();
	return move;
}



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
