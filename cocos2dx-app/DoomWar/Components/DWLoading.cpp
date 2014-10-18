#include "DWLoading.h"

bool DWLoading::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCLabelTTF* label = CCLabelTTF::create("Loading...", "Arial", 30);
	CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();

	label->setPosition(ccp(visiableSize.width/2,visiableSize.height/2));
	this->addChild(label);

	return true;
}

DWLoading* DWLoading::create()
{
	DWLoading* pLoading = new DWLoading();
	if (pLoading && pLoading->init())
	{
		pLoading->autorelease();
		return pLoading;
	}
	return NULL;
}

DWLoading::DWLoading()
{

}

DWLoading::~DWLoading()
{

}
