#include "WorldScene.h"
#include "GameLayer.h"
#include "BackgroundLayer.h"
#include "UILayer.h"
#include "GameManager.h"

USING_NS_CC;

WorldScene* WorldScene::createScene()
{
	WorldScene* scene = WorldScene::create();
	return scene;
}


WorldScene* WorldScene::createSceneWithData( Vec2 boxNum , Size boxSize , std::map<int , ObjectType> mapData , char* BGpath )
{
	WorldScene* scene = WorldScene::create();
	GET_INPUT_MANAGER()->receiveInputData( scene );
	scene->getGameLayer()->initWorldFromData(boxNum, boxSize, mapData, BGpath);
	return scene;
}

bool WorldScene::init()
{
	if( !Scene::init() )
	{
		return false;
	}

	m_GameLayer = GameLayer::create();
	m_GameLayer->setAnchorPoint( Point::ZERO );
	m_BackgroundLayer = BackgroundLayer::create();
	m_BackgroundLayer->setPosition( Point::ZERO );
	m_UILayer = UILayer::create();
	m_UILayer->setPosition( Point::ZERO );

	this->addChild( m_GameLayer , WorldScene::ZOrder::GAMELAYER , TAG_GAME_LAYER );
	this->addChild( m_BackgroundLayer , WorldScene::ZOrder::BACKGROUND , "TAG_BACKGROUND_LAYER" );
	this->addChild( m_UILayer , WorldScene::ZOrder::UILAYER , "TAG_UI_LAYER" );
	
	m_UILayer->initializeUILayer();
	return true;
}
