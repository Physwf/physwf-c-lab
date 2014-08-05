#ifndef _UNIT_H
#define _UNIT_H

#define MAX_HEROS_IN_A_BATTLE 10
#define MAX_ENYMYS_IN_A_BATTLE 10

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
} Unit;

#endif