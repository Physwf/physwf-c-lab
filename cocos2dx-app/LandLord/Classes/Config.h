#ifndef _CONFIG_H
#define _CONFIG_H
#include "Properties.h"
class Config
{
private:
	Config();
	~Config();
public:
	static Config* getInstance();
	Properties* getProperties();
	void destroy();
private:
	static Config* instance;
	Properties* mProperties;
};
#endif