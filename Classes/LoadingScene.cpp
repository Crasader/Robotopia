#include "LoadingScene.h"
#include "GameManager.h"
USING_NS_CC;

cocos2d::Scene* LoadingScene::createScene()
{
	LoadingScene* scene = LoadingScene::create();
	return scene;
}

bool LoadingScene::init()
{
	auto layer = Layer::create();
	this->addChild( layer );
	auto spr = GET_RESOURCE_MANAGER()->createSprite("Loading.png");
	layer->addChild( spr );

	return true;
}



