#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	mFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	mAnimationCache = CCAnimationCache::sharedAnimationCache();
}

ResourceManager* ResourceManager::mInstance = NULL;

ResourceManager* ResourceManager::instance()
{
	if (mInstance == NULL)
		mInstance = new ResourceManager();
	return mInstance;
}

void ResourceManager::load(const char* pszFile, CCObject* target, SEL_CallFuncO selector)
{
	CCTextureCache::sharedTextureCache()->addImageAsync(pszFile, target, selector);
}

void ResourceManager::addSpriteFramePack(const char* plist, CCTexture2D *pobTexture)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, pobTexture);
}

CCSpriteFrame* ResourceManager::getSpriteFrame(const char* name)
{
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
}

void ResourceManager::addAnimation(CCAnimation* animation, const char* name)
{
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation,name);
}

CCAnimation* ResourceManager::getAnimation(const char* name)
{
	return	CCAnimationCache::sharedAnimationCache()->animationByName(name);
}