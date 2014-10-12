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


void WorldScene::initCurrentSceneWithData( Vec2 boxNum , Size boxSize , std::map<int , ObjectType> mapData , char* BGpath )
{
	m_KeySentinel = GET_INPUT_MANAGER()->receiveInputData( this );
	this->getGameLayer()->initWorldFromData(boxNum, boxSize, mapData, BGpath);
}

bool WorldScene::init()
{
	if( !Scene::init() )
	{
		return false;
	}
	m_ShakeTime = 500.f;
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

void WorldScene::onEnter()
{
	Node::onEnter();
}

void WorldScene::update(float dTime)
{
	GET_STAGE_MANAGER()->accumultateTime( dTime );
	GET_STAGE_MANAGER()->initLastMonster( dTime );
	m_KeySentinel->update( dTime );
	m_UILayer->update( dTime );
	m_GameLayer->update( dTime );
	m_BackgroundLayer->update( dTime );
}


