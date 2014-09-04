#ifndef _UNIT_H
#define _UNIT_H

#include "Heap.h"
#include "dwtype.h"
#include "libxml\parser.h"

#define MAX_ATTACK_GRIDS 20

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
#define SKILL_TYPE_BUFF_HEALTH		3L
typedef struct skill_t
{
	char* name;
	ID cid;
	ID type;
	int value;
} Skill;

typedef struct unit_t
{
	ID iid;//instance id
	ID cid;//config id
	char* name;
	ID exp;
	ID maxHealth;
	int health;
	Skill skill;
	ID agility;
	ID armor;
	unsigned short atackFreq;//attacks per turn
	Position positon;
	Range attackRange;
	Range view;//йср╟
} Unit;

void constructUnitWithXML(Unit* unit, xmlNodePtr attr);

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