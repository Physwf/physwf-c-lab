#ifndef _SESSION_H
#define _SESSION_H

#include "platform.h"

class VALE_DLL Session
{
public:
	Session();
	Session(const char* sid);
	~Session();
public:
	const char* getSID() { return szSID; }
	int getFd() { return nFd; }
	int getPid() { return nPid; }
private:
	char* szSID;
	int nFd;
	int nPid;
};
#endif