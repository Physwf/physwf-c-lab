#include "Scene.h"
#include <string.h>
#include "DWLoadingScene.h"
#include "PVEBattleScene.h"

Scene::Scene() :mLoading(NULL), mPVEScene(NULL)
{

}

Scene::~Scene()
{

}

void Scene::initialize()
{
	memset(mActors, 0, sizeof(mActors));
	numActors = 0;
}

void Scene::showLoading()
{
	if (mLoading == NULL)
	{
		mLoading = DWLoadingScene::create();
	}
	//to do, if this method been invoked more than once, should use replaceScene() instead
	CCScene* s = CCScene::create();
	s->addChild(mLoading);
	CCDirector::sharedDirector()->runWithScene(s);
}

void Scene::enterPVEMap(unsigned int mapid)
{
	if (mPVEScene == NULL)
	{
		mPVEScene = PVEBattleScene::create();
	}
	CCScene* s = CCScene::create();
	s->addChild(mPVEScene);
	//CCDirector::sharedDirector()->runWithScene(s);
	CCDirector::sharedDirector()->replaceScene(s);
}

void Scene::leavePVEMap()
{

}