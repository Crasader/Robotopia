#include "StageManager.h"

USING_NS_CC;

bool StageManager::init()
{
	UserDefault::getInstance()->setIntegerForKey( "mapWidth" , 48 );
	UserDefault::getInstance()->setIntegerForKey( "mapHeight" , 20 );
	UserDefault::getInstance()->setIntegerForKey( "boxWidth" , 32 );
	UserDefault::getInstance()->setIntegerForKey( "boxHeight" , 32 );
	UserDefault::getInstance()->setStringForKey( "mapData" , MAPDATA );

	m_WorldScene = WorldScene::create();
	m_Player = Player::create();
	Director::getInstance()->runWithScene( m_WorldScene );

	return true;
}

