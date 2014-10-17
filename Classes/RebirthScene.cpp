#include "RebirthScene.h"
#include "LoadingScene.h"

USING_NS_CC;

cocos2d::Scene* RebirthScene::createScene()
{
	RebirthScene* scene = RebirthScene::create();
	return scene;
}

bool RebirthScene::init()
{
	auto layer = Layer::create();
	this->addChild( layer );
	auto playButton = MenuItemImage::create( "menu_play0.png" , "menu_play1.png" ,
											 CC_CALLBACK_1( RebirthScene::menuCallback , this ) );
	auto menu = Menu::create( playButton , NULL );
	layer->addChild( menu );
	return true;
}

void RebirthScene::menuCallback( Ref* sender )
{
	Director::getInstance()->replaceScene( LoadingScene::createScene() );
}

