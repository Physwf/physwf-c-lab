#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "cocos2d.h"

using namespace cocos2d;

class ResourceManager
{
public:
	static ResourceManager* instance();

	CCSpriteFrame* getSpriteFrame(const char* name);
	CCAnimationFrame* getAnimationFrame(const char* name);

	void addSpriteFramePack(const char* plist, const char* file);

private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* mInstance;
	CCSpriteFrameCache* mFrameCache;
	CCAnimationCache* mAnimationCache;
};
#endif