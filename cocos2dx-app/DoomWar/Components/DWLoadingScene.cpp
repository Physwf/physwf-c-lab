#include "DWLoadingScene.h"

CCScene* DWLoadingScene::scene() const
{
	return mScene;
}

bool DWLoadingScene::init()
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

DWLoadingScene* DWLoadingScene::create()
{
	DWLoadingScene* pLoading = new DWLoadingScene();
	if (pLoading && pLoading->init())
	{
		pLoading->autorelease();
		pLoading->mScene->addChild(pLoading);
		return pLoading;
	}
	return NULL;
}

DWLoadingScene::DWLoadingScene()
{
	mScene = CCScene::create();
}

DWLoadingScene::~DWLoadingScene()
{

}
