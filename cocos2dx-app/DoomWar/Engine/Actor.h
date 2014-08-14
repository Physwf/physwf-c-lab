#ifndef _ACTOR_H
#define _ACTOR_H

class Actor
{
public:
	void stepForword();
	void stepBackword();
	void stepLeft();
	void stepRight();
	void moveTo();

	void attack();

	unsigned int iid() const;
};
#endif