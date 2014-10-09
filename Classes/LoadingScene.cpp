#include "LoadingScene.h"

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
	auto spr = Sprite::create("Loading.png");
	layer->addChild( spr );

	return true;
}



