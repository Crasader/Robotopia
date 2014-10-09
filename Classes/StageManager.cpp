
#include "GameManager.h"
#include "GameLayer.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool StageManager::init()
{
	m_WorldScene = nullptr;
	m_CurrentFloor = 1;

	GET_DATA_MANAGER()->getFloorData( m_CurrentFloor , m_FloorData , &m_CurrentStageData );
	return true;
}

void StageManager::changeStage(int stageNum)
{
	int boxNumWidth = m_CurrentStageData[stageNum].width;
	int boxNumHeight = m_CurrentStageData[stageNum].width;
	Size boxSize = Size( 32 , 32 );
	std::map<int , ObjectType> data = m_CurrentStageData[stageNum].data;
	m_WorldScene = WorldScene::createSceneWithData( Vec2( boxNumWidth , boxNumHeight ) , boxSize , data , "background.png" );
	Director::getInstance()->replaceScene( m_WorldScene );
}

const Player* StageManager::getPlayer()
{
	if( m_WorldScene == nullptr )
	{
		return nullptr;
	}
	return ( m_WorldScene->getGameLayer() )->getPlayer();
}

std::vector<InteractiveObject*> StageManager::getObjectsByRect( cocos2d::Rect checkRect )
{
	std::vector<InteractiveObject*> results;
	results.clear();
	if( m_WorldScene == nullptr )
	{
		return results;
	}
	return ( m_WorldScene->getGameLayer() )->getObjectsByRect( checkRect );
}

std::vector<InteractiveObject*> StageManager::getObjectsByPosition( cocos2d::Point checkPosition )
{
	std::vector<InteractiveObject*> results;
	results.clear();
	if( m_WorldScene == nullptr )
	{
		return results;
	}
	return ( m_WorldScene->getGameLayer() )->getObjectsByPosition( checkPosition );
}

ObjectType StageManager::getMapDataInPosition( cocos2d::Point position )
{
	ObjectType resultType = OT_NONE;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->getMapDataInPosition( position );
}


ObjectType StageManager::getMapDataInPositionWithIdx( int xIdx , int yIdx )
{
	ObjectType resultType = OT_NONE;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->getMapDataInPositionWithIdx( xIdx , yIdx );
}

InteractiveObject* StageManager::addObject( ObjectType type , cocos2d::Point position )
{
	InteractiveObject* resultType = nullptr;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->addObject( type , position );
}

InteractiveObject* StageManager::addObjectByIdx( ObjectType type , int xIdx , int yIdx )
{
	InteractiveObject* resultType = nullptr;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->addObjectByMapdata( type , xIdx , yIdx );
}

InteractiveObject* StageManager::addObjectByIdx( int xIdx , int yIdx )
{
	InteractiveObject* resultType = nullptr;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->addObjectByMapdata( xIdx , yIdx );
}

void StageManager::addEffectOnGameLayer( cocos2d::Sprite* effect )
{
	m_WorldScene->getGameLayer()->addEffect( effect );
}

