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
				return true;
			}
		}
	}
	return false;
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
	mEffect = CCSprite::create();
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
	cmd->attcker->attack();
	Engine::scene->pve()->layerEffect()->addChild(cmd->mEffect);
	cmd->mEffect->setPosition(cmd->attcker->position());
	CCAnimation* ice = ResourceManager::instance()->getAnimation("ice");
	cmd->mEffect->runAction(CCAnimate::create(ice));
	return cmd;
}
