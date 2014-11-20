#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "cocos2d.h"
#include <cocoa\CCObject.h>
#include "dwtype.h"
#include "Config.h"

using namespace cocos2d;

class ResourceManager
{
public:
	static ResourceManager* instance();

	CCSpriteFrame* getSpriteFrame(const char* name);
	CCAnimationFrame* getAnimationFrame(const char* name);
	
	CCAnimation* getAnimation(const char* name);

	void loadTexture(const char* pszFile, CCObject* target, SEL_CallFuncO selector);
	void addSpriteFramePack(const char* plist, CCTexture2D *pobTexture);
	void addAnimation(CCAnimation* animation, const char* name);

	void loadXML(const char* pszFile, DWObject* object, Config::OnConfigLoaded onConfigLoaded);
private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* mInstance;
	CCSpriteFrameCache* mFrameCache;
	CCAnimationCache* mAnimationCache;
};
#endif