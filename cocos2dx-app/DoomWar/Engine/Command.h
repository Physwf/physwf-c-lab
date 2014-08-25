#ifndef _COMMAND_H
#define _COMMAND_H

#include <deque>
#include "Actor.h"
#include "Battle.h"

class Command
{
public:
	Command();
	~Command();
	virtual bool tick(float delta) = 0;
};

class CommandSequence : public Command
{
public:
	static CommandSequence* create();
	void push(Command* cmd);
	virtual bool tick(float delta);
private:
	CommandSequence();
	~CommandSequence();
private:
	std::deque<Command*> mQueue;
	Command* mCurCmd;
};

class CommandAttck : public Command
{
public:
	static CommandAttck* create(AttackResult* result);
	virtual bool tick(float delta);
private:
	CommandAttck();
	~CommandAttck();
private:
	float mDuration;
	float mNow;
	Actor* attcker;
	Actor* victim;
};
#endif