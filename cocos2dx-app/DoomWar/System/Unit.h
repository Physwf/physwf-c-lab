#ifndef _UNIT_H
#define _UNIT_H

#include "Heap.h"
#include "dwtype.h"
#include "libxml\parser.h"

#define MAX_ATTACK_GRIDS 50
#define MAX_NUM_SKILLS 10
#define MAX_NUM_BUFFS 10

typedef enum {
	NONE,
	LEFTWARD,
	FORWARD,
	BACKWARD,
	RIGHTWARD
} StepDirection;

typedef struct grid_t
{
	int x;
	int y;
} Grid;

typedef struct grid_set_t
{
	char cid;
	char* name;
	char type;
	Grid *elements;
	int numElements;
} GSet;

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

typedef struct range2_t
{
	char numGSets;
	ID gSets[2];
} Range2;

#define SKILL_TYPE_HARM_PHYSICAL	1L
#define SKILL_TYPE_HARM_MAGICAL		2L
#define SKILL_TYPE_HEAL				3L

#define SKILL_TRACK_HACK			0L
#define SKILL_TRACK_BULLET			1L
#define SKILL_TRACK_FIXXED			2L
#define SKILL_TRACK_ARC				3L

#define SKILL_ATTACK_BY_RANGE		1L
#define SKILL_ATTACK_BY_GRID		2L

#define SKILL_EFFECT_AXE			1L
#define SKILL_EFFECT_ARROW			2L
#define SKILL_EFFECT_DAGGER			3L
#define SKILL_EFFECT_ICE			4L
#define SKILL_EFFECT_FIREBALL		5L

#define BUFF_TYPE_HEAL				1L

#define MAX_NUM_NODES				5L
#define MAX_NUM_PATHS				4L

typedef struct path_t
{
	char numNodes;
	char nodes[MAX_NUM_NODES];
} Path;

typedef struct path_grop_t
{
	ID track;
	char numPaths;
	Path paths[MAX_NUM_PATHS];
} PathGroup;

typedef struct skill_t
{
	char* name;
	ID cid;
	char type;
	char cast;
	char attack;
	char track;
	Range2 range2;
	Range range;
	char effect;
	char level;
	int value;
	char limit;
	char condition;
} Skill;

typedef struct  buff_t
{
	char* name;
	ID cid;
	char type;
	char condition;
	int value;
} Buff;
#define UNIT_AI_TYPE_NEAREST 1L
#define UNIT_AI_TYPE_WEAKEST 2L

#define UNIT_ALIGN_TYPE_HERO 1L
#define UNIT_ALIGN_TYPE_ENEMY 2L
#define UNIT_ALIGN_TYPE_BARRIER 3L
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
	char ai;
	char alignment;
	char armor;
	unsigned short attackFreq;//attacks per turn
	Position positon;
	Range attackRange;
	Range view;//йср╟
} Unit;

#define ITEM_TYPE_GOLD	1
#define ITEM_TYPE_BLOOD 2
#define ITEM_TYPE_EGG	3

#define ITEM_PICK_TYPE_STEP 1
#define ITEM_PICK_TYPE_AUTO 2
typedef struct item_t
{
	ID iid;
	ID cid;
	char* name;
	ID type;
	char pick;
	ID value;
	Position position;
} Item;

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