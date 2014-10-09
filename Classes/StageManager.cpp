
#include "GameManager.h"
#include "GameLayer.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool StageManager::init()
{
	m_WorldScene = nullptr;
	m_CurrentFloor = 1;
	m_CurrentStageNum = 0;
	GET_DATA_MANAGER()->getFloorData( m_CurrentFloor , &m_FloorData , &m_CurrentFloorData );
	return true;
}

void StageManager::changeStage( size_t stageNum )
{
	m_CurrentStageNum = stageNum;
	_ASSERT( stageNum <= m_FloorData.stageNum );
	int boxNumWidth = m_CurrentFloorData[stageNum].width;
	int boxNumHeight = m_CurrentFloorData[stageNum].width;
	Size boxSize = Size( 32 , 32 );
	std::map<int , ObjectType> data = m_CurrentFloorData[stageNum].data;
	m_WorldScene = WorldScene::createScene();
 	m_WorldScene->initCurrentSceneWithData( Vec2( boxNumWidth , boxNumHeight ) , boxSize , data , "background.png" );
	Director::getInstance()->replaceScene( m_WorldScene );
	addObject( OT_PLAYER , Point(90, 90));
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

ObjectType StageManager::getStageDataInPosition( cocos2d::Point position )
{
	ObjectType resultType = OT_NONE;
	if( m_WorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_WorldScene->getGameLayer() )->getMapDataInPosition( position );
}


ObjectType StageManager::getStageDataInPositionWithIdx( int xIdx , int yIdx )
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

cocos2d::Vec2 StageManager::positionToIdxOfStage( cocos2d::Point position )
{
	Vec2 resultIdx = Vec2(-1,-1);
	if( m_WorldScene == nullptr )
	{
		return resultIdx;
	}
	return ( m_WorldScene->getGameLayer() )->positionToIdxOfMapData( position );
}

cocos2d::Vec2 StageManager::positionToIdxOfFloor( cocos2d::Point position )
{
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).y;
	int floorXIdx = m_CurrentFloorData[m_CurrentStageNum].x + stageXIdx / MODULE_BASE_WIDTH;
	int floorYIdx = m_CurrentFloorData[m_CurrentStageNum].y + stageYIdx / MODULE_BASE_HEIGHT;

	return Vec2( floorXIdx , floorYIdx );
}

int StageManager::getFloorDataByIdx( int xIdx , int yIdx )
{
	return m_FloorData.data[m_FloorData.width*yIdx + xIdx];
}

