#include "MenuScene.h"
#include "RebirthScene.h"

USING_NS_CC;

cocos2d::Scene* MenuScene::createScene()
{
	MenuScene* scene = MenuScene::create();
	return scene;
}

bool MenuScene::init()
{
	auto layer = Layer::create();
	this->addChild( layer );
	auto playButton = MenuItemImage::create( "menu_play0.png" , "menu_play1.png" , 
											 CC_CALLBACK_1( MenuScene::menuCallback , this ) );
	auto menu = Menu::create( playButton , NULL );
	layer->addChild( menu );
	return true;
}

void MenuScene::menuCallback( Ref* sender )
{
	Director::getInstance()->replaceScene(RebirthScene::createScene());
}

