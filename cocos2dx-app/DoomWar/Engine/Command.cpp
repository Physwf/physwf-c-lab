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
	cmd->mEffect = BulletEffect::create(0, result->attacker, result->victim);
	return cmd;
}
