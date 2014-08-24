#include "Command.h"
#include "Engine.h"

CommandSequence::CommandSequence() :mCurCmd(NULL)
{

}

CommandSequence::~CommandSequence()
{

}

void CommandSequence::push(Command* cmd)
{
	mQueue.push_back(cmd);
}

bool CommandSequence::tick(float delta)
{
	if (mCurCmd)
	{
		while (mCurCmd->tick(delta))
		{
			if (mQueue.size())
			{
				mCurCmd = mQueue.front();
				mQueue.pop_front();
			}
			else
			{
				mCurCmd = NULL;
			}
		}
	}
		
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
}

CommandAttck::~CommandAttck()
{

}

bool CommandAttck::tick(float delta)
{
	mNow += delta;
	if (mNow>=mDuration)
	{
		return true;
	}
	return false;
}

CommandAttck* CommandAttck::create(AttackResult* result)
{
	CommandAttck* cmd = new CommandAttck();
	cmd->attcker = Engine::scene->getActor(result->attacker);
	cmd->victim = Engine::scene->getActor(result->victim);
	cmd->victim->updateHealth(result->value);
	return cmd;
}
