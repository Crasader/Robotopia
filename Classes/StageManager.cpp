#include "StageManager.h"

USING_NS_CC;

bool StageManager::init()
{
	m_WorldScene = WorldScene::create();
	m_Player = Player::create();
	Director::getInstance()->runWithScene( m_WorldScene );

	return true;
}

