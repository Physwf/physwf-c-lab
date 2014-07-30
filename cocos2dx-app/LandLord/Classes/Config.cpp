#include "Config.h"

Config::Config()
{
	mProperties = new Properties();
	mProperties->readFile("./data/cards.properties");
};

Config::~Config()
{
	delete mProperties;
};

Properties* Config::getProperties()
{
	return mProperties;
};

Config* Config::getInstance()
{
	if (instance == NULL)
		instance = new Config();
	return instance;
}

void Config::destroy()
{
	delete this;
};

Config* Config::instance = NULL;