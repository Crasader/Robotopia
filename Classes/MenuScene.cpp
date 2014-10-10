#include "MenuScene.h"
#include "GameManager.h"

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
	this->addChild( menu );
	return true;
}

void MenuScene::menuCallback( Ref* sender )
{
	GET_STAGE_MANAGER()->changeStage(1, Point(90, 90));
}

