#ifndef _TABLE_H
#define _TABLE_H

#include "type.h"

class Table
{
public:
	Table();
	~Table();
public:
	tid_t tid() { return nTid; }
private:
	tid_t nTid;
};

#endif