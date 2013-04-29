#include "SpriteObject.h"

using namespace cocos2d;

CCScene * SpriteObject::scene () 
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		SpriteObject * layer = SpriteObject::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

	}while(0);

	return scene;
}

bool SpriteObject::init()
{
	bool bRet = false;
	do
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite * pSprite = CCSprite::create("Alcedo256.jpg");
		CC_BREAK_IF(!pSprite);
		pSprite->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(pSprite);

		CCImage * image = new CCImage();
		image->initWithImageFile("Alcedo256.jpg",CCImage::kFmtJpg);
		CCTexture2D * tex = new CCTexture2D();
		tex->initWithImage(image);
		CCSprite * pSprite2 = CCSprite::createWithTexture(tex);
		this->addChild(pSprite2);

		CCRect rect;
		rect.setRect(0,0,100,100);
		CCSpriteFrame * pFrame = CCSpriteFrame::create("Alcedo256.jpg",rect);
		CCSprite * pSprite3 = CCSprite::createWithSpriteFrame(pFrame);
		CC_BREAK_IF(!pSprite3);
		this->addChild(pSprite3);

		bRet = true;
	}while(0);
	return bRet;
}