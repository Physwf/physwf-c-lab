#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	mFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	mAnimationCache = CCAnimationCache::sharedAnimationCache();
}

ResourceManager* ResourceManager::instance()
{
	if (!mInstance)
		mInstance = new ResourceManager();
	return mInstance;
}


