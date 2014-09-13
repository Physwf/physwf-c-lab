#ifndef _UNIT_H
#define _UNIT_H

#include "Heap.h"
#include "dwtype.h"
#include "libxml\parser.h"

#define MAX_ATTACK_GRIDS 20
#define MAX_NUM_SKILLS 10
#define MAX_NUM_BUFFS 10

typedef enum {
	LEFTWARD,
	FORWARD,
	BACKWARD,
	RIGHTWARD
} StepDirection;

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
#define SKILL_TYPE_HEAL				3L

#define SKILL_TRACK_HACK			0L
#define SKILL_TRACK_BULLET			1L
#define SKILL_TRACK_FIXXED			2L

#define SKILL_EFFECT_AXE			1L
#define SKILL_EFFECT_ARROW			2L
#define SKILL_EFFECT_DAGGER			3L
#define SKILL_EFFECT_ICE			4L

#define BUFF_TYPE_HEAL				1L

typedef struct skill_t
{
	char* name;
	ID cid;
	ID type;
	ID cast;
	ID track;
	ID effect;
	int level;
	int value;
	int condition;
} Skill;

typedef struct  buff_t
{
	char* name;
	ID cid;
	ID type;
	char condition;
	int value;
} Buff;

typedef struct unit_t
{
	ID iid;//instance id
	ID cid;//config id
	char* name;
	int exp;
	int maxHealth;
	int health;
	ID skills[MAX_NUM_SKILLS];
	ID buffs[MAX_NUM_BUFFS];
	Skill skill;
	int agility;
	ID armor;
	unsigned short atackFreq;//attacks per turn
	Position positon;
	Range attackRange;
	Range view;//йср╟
} Unit;


class UnitWraper :public IPriority
{
public:
	UnitWraper(Unit* unit);
	UnitWraper(Unit* unit, int value);
	~UnitWraper();

	virtual int value() const;
	Unit* unit() const;
private:
	UnitWraper();
private:
	Unit* mUnit;
	int mValue;
};
#endif