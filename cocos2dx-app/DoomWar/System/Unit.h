#ifndef _UNIT_H
#define _UNIT_H

#include "Heap.h"

#define MAX_ATTACK_GRIDS 20

typedef struct position_t
{
	int x;
	int y;
} Position;

typedef struct range_t
{
	Position offsets[MAX_ATTACK_GRIDS];
	int numGrids;
} Range;

#define SKILL_TYPE_HARM_PHYSICAL	1L
#define SKILL_TYPE_HARM_MAGICAL		2L
#define SKILL_TYPE_BUFF_HEALTH		3L
typedef struct skill_t
{
	char* name;
	unsigned int cid;
	unsigned int type;
	int value;
} Skill;

typedef struct unit_t
{
	unsigned int iid;//instance id
	unsigned int cid;//config id
	char* name;
	unsigned int exp;
	unsigned int maxHealth;
	int health;
	Skill skill;
	unsigned int agility;
	unsigned int armor;
	unsigned short atackFreq;//attacks per turn
	Position positon;
	Range attackRange;
	Range view;//йср╟
} Unit;

class UnitWraper :public IPriority
{
public:
	UnitWraper(Unit* unit);
	~UnitWraper();

	virtual int value() const;
	Unit* unit() const;
private:
	UnitWraper();
private:
	Unit* mUnit;
};
#endif