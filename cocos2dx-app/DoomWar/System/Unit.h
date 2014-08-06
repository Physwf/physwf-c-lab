#ifndef _UNIT_H
#define _UNIT_H

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
	unsigned int armor;
	unsigned short atackFreq;//attacks per turn
} Skill;

typedef struct unit_t
{
	char* name;
	unsigned int id;
	unsigned int exp;
	int health;
	Skill skill;
	Position positon;
	Range attackRange;
	Range view;
} Unit;

#endif