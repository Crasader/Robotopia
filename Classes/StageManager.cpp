
#include <string>
#include "GameManager.h"
#include "GameLayer.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool StageManager::init()
{
	m_WorldScene = nullptr;
	m_CurrentFloor = 1;
	m_CurrentStageNum = 0;
	m_PlayerInfo.Hp = 0 , m_PlayerInfo.MaxHp = 0 , m_PlayerInfo.Steam = 0 , m_PlayerInfo.MaxSteam = 0;
	GET_DATA_MANAGER()->getFloorData( m_CurrentFloor , &m_FloorData , &m_CurrentFloorData );
	return true;
}

void StageManager::changeStage( size_t stageNum , Point nextPlayerPosition)
{
	addVisitedStage( stageNum );
	savePlayerInfo();
	m_CurrentStageNum = stageNum;
	int boxNumWidth = m_CurrentFloorData[stageNum].width;
	int boxNumHeight = m_CurrentFloorData[stageNum].height;
	m_BoxSize = Size( 32 , 32 );
	m_StageRect = Rect( 0 , 0 , m_BoxSize.width * boxNumWidth , m_BoxSize.height * boxNumHeight );
	std::map<int , ObjectType> data = m_CurrentFloorData[stageNum].data;
	m_WorldScene = WorldScene::createScene();
	m_WorldScene->initCurrentSceneWithData( Vec2( boxNumWidth , boxNumHeight ) , m_BoxSize , data , "background.png" );
	Director::getInstance()->replaceScene( m_WorldScene );
	loadPlayer(nextPlayerPosition);
}

Player* StageManager::getPlayer()
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
	Vec2 idx = positionToIdxOfStage( position );
	return getStageDataInPositionWithIdx( idx.x , idx.y );
}


ObjectType StageManager::getStageDataInPositionWithIdx( int xIdx , int yIdx )
{
	return getStageDataInPositionWithIdx( xIdx , yIdx , m_CurrentStageNum );
}

ObjectType StageManager::getStageDataInPositionWithIdx( int xIdx , int yIdx , int stageNum )
{
	StageData stageData = m_CurrentFloorData[stageNum];
	return stageData.data[yIdx*stageData.width + xIdx];
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

void StageManager::addEffectOnGameLayer( cocos2d::Sprite* effect )
{
	m_WorldScene->getGameLayer()->addEffect( effect );
}

void StageManager::addEffectOnGameLayer( cocos2d::Sprite* effect , Point position , Point AnchorPoint )
{
	effect->setAnchorPoint( AnchorPoint );
	effect->setPosition( position );
	m_WorldScene->getGameLayer()->addEffect( effect );
}

cocos2d::Vec2 StageManager::positionToIdxOfStage( cocos2d::Point position )
{
	Vec2 curPosIdx = Vec2( -1 , -1 );
	if( m_StageRect.containsPoint( position ) )
	{
		curPosIdx.x = position.x / m_BoxSize.width;
		curPosIdx.y = position.y / m_BoxSize.height;
	}
	return curPosIdx;
}

cocos2d::Vec2 StageManager::positionToIdxOfFloor( cocos2d::Point position )
{
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).y;
	int floorXIdx = m_CurrentFloorData[m_CurrentStageNum].x + (stageXIdx - 1) / MODULE_BASE_WIDTH;
	int curFloorY = m_CurrentFloorData[m_CurrentStageNum].y;
	int curPositionAddY = (stageYIdx-1) / MODULE_BASE_HEIGHT;
	int floorYIdx = curFloorY + curPositionAddY;

	return Vec2( floorXIdx , floorYIdx );
}

int StageManager::getFloorDataByIdx( int xIdx , int yIdx )
{
	return m_FloorData.data[m_FloorData.width*yIdx + xIdx];
}

void StageManager::addVisitedStage( int stage )
{
	bool isVisited = false;
	for( auto visitedStage : m_VisitedStageNums )
	{
		if( stage == visitedStage )
		{
			isVisited = true;
			break;
		}
	}
	if( !isVisited )
	{
		m_VisitedStageNums.push_back( stage );
	}
}

cocos2d::Point StageManager::idxOfStageDataToPosiion( cocos2d::Vec2 idx )
{
	return Point( idx.x*m_BoxSize.width , idx.y*m_BoxSize.height );
}

void StageManager::savePlayerInfo()
{
	auto player = getPlayer();
	if( player == nullptr )
	{
		return;
	}
	m_PlayerInfo.Hp = player->getHp();
	m_PlayerInfo.MaxHp = player->getMaxHp();
	m_PlayerInfo.Steam = player->getSteam();
	m_PlayerInfo.MaxSteam = player->getMaxSteam();

}

void StageManager::loadPlayer( Point setPosition )
{
	addObject( OT_PLAYER , setPosition );
	auto player = getPlayer();
	player->setHp( m_PlayerInfo.Hp );
	player->setMaxHp( m_PlayerInfo.MaxHp );
	player->setSteam( m_PlayerInfo.Steam );
	player->setMaxSteam( m_PlayerInfo.MaxSteam );
}
