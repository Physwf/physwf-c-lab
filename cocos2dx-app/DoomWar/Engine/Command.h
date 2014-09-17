#ifndef _COMMAND_H
#define _COMMAND_H

#include <deque>
#include <vector>
#include "Actor.h"
#include "Battle.h"
#include "Effect.h"

class Command
{
public:
	Command();
	~Command();
	virtual bool tick(float delta) = 0;
	virtual void trigger() = 0;
};

class CommandSequence : public Command
{
public:
	static CommandSequence* create();
	void push(Command* cmd,bool autoTrigger);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandSequence();
	~CommandSequence();
private:
	std::deque<Command*> mQueue;
	Command* mCurCmd;
};

class CommandParallel : public Command
{
public:
	static CommandParallel* create();
	virtual bool tick(float delta);
	virtual void trigger();
	void addCommand(Command* cmd);
private:
	CommandParallel();
	~CommandParallel();
private:
	std::vector<Command*> mCommands;
};

class CommandMove : public Command
{
public:
	static CommandMove* create(Actor* actor);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandMove(Actor* actor);
	~CommandMove();
private:
	Actor* mActor;
	CCSequence* mAction;
	CCDelayTime* mDelay;
	CCMoveTo* mMove;
	CCPoint mPos;

};

class CommandScroll : public Command
{
public:
	static CommandScroll* create(CCLayer* layer, StepDirection dir);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandScroll(CCLayer* layer);
	~CommandScroll();
private:
	CCLayer* mLayer;
	CCMoveTo* mMove;

};

class CommandSkill : public Command
{
public:
	static Command* create(SkillResult* result);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandSkill();
	~CommandSkill();
private:
	float mDuration;
	float mNow;
	Effect* mEffect;
};

class CommandProgress : public Command
{
public:
	typedef void(DWObject::*OnProgressDelta)(int delta);
private:
	OnProgressDelta mOnProgressDelta;
	DWObject* mObject;
	int mDelta;
	int mCurrent;
	Actor* mActor;
public:
	static CommandProgress* create(int delta, Actor* actor);
	static CommandProgress* create(int delta, DWObject* object, OnProgressDelta onProgressDelta);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandProgress(int delta);
	~CommandProgress();
};

class CommandDie : public Command
{
public:
	static CommandDie* create(Actor* actor);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandDie(Actor* actor);
	~CommandDie();
private:
	Actor* mActor;
};

#endif