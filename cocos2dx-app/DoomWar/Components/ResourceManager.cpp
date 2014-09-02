#include "ResourceManager.h"
#include <libxml/parser.h>

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

void ResourceManager::loadTexture(const char* pszFile, CCObject* target, SEL_CallFuncO selector)
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

void ResourceManager::loadXML(const char* pszFile, DWObject* object, Config::OnConfigLoaded onConfigLoaded)
{
	xmlDocPtr pDoc;
	xmlNodePtr pRoot;
	pDoc = xmlReadFile(pszFile, "GB2312", XML_PARSE_RECOVER);
	CCAssert(pDoc == NULL, "Failed to read xml file!");
	pRoot = xmlDocGetRootElement(pDoc);
	(object->*onConfigLoaded)(pRoot);
	xmlFreeDoc(pDoc);
}