#include "RebirthScene.h"
#include "UILayer.h"
#include "LoadingScene.h"

USING_NS_CC;

cocos2d::Scene* RebirthScene::createScene()
{
	RebirthScene* scene = RebirthScene::create();
	return scene;
}

bool RebirthScene::init()
{
	auto layer = UILayer::create();
	layer->initializeRobotSetting();
	this->addChild( layer );
	return true;
}

void RebirthScene::menuCallback( Ref* sender )
{
	Director::getInstance()->replaceScene( LoadingScene::createScene() );
}

