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
	void push(Command* cmd);
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
	CCAction* mAction;
};

class CommandAttck : public Command
{
public:
	static CommandAttck* create(AttackResult* result);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandAttck();
	~CommandAttck();
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
	static CommandProgress* create(int delta, DWObject* object, OnProgressDelta onProgressDelta);
	virtual bool tick(float delta);
	virtual void trigger();
private:
	CommandProgress(int delta);
	~CommandProgress();
};
#endif