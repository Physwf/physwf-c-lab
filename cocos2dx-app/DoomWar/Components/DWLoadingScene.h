#ifndef _DW_LOADING_SCENE_H
#define _DW_LOADING_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class DWLoadingScene : public CCLayer
{
public:
	virtual bool init();
	CCScene* scene() const;
	static DWLoadingScene* create();
private:
	DWLoadingScene();
	~DWLoadingScene();
private:
	CCScene* mScene;
};
#endif