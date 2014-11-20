#include "StaticDisplayObject.h"

using namespace cocos2d;

CCScene * StaticDisplayObject::scene()
{
	CCScene * scene = NULL;
	//������ѭ���г�ʼ������ַ�ʽ�����Ա���д���if�жϺ�д���return���
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		StaticDisplayObject * layer = StaticDisplayObject::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);
	}while(0);

	/*�����ϲ������ѭ����ʽ���������µ�Ч����
	scene = CCScene::create();
	if(!scene) return scene;

	StaticDisplayObject * layer = StaticDisplayObject::create();
	if(!layer) return scene;

	scene->addChild(layer);
	*/

	return scene;
};

bool StaticDisplayObject::init()
{
	bool bRet = false;
	do
	{
		//super call
		CC_BREAK_IF(!CCLayer::init());

		CCSize size =  CCDirector::sharedDirector()->getWinSize();

		CCSprite * sprite = CCSprite::create("Alcedo256.jpg");
		CC_BREAK_IF(!sprite);
		sprite->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(sprite);

		CCLabelTTF * label = CCLabelTTF::create("Hello Cocos2d-x!","Arial",13);
		CC_BREAK_IF(!label);
		label->setPosition(ccp(size.width/2+60,size.height/2-80));
		this->addChild(label);

		bRet = true;

	}while(0);

	return bRet;
};