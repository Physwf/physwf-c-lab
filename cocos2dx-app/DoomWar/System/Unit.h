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
	int offsets[MAX_ATTACK_GRIDS];
	int numGrids;
} Range;

typedef struct skill_t
{
	char* name;
	unsigned short id;
	unsigned int damage;
} Skill;

typedef struct unit_t
{
	unsigned int id;
	char* name;
	unsigned int exp;
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