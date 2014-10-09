#include "StageManager.h"
#include "GameLayer.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool StageManager::init()
{
	m_WorldScene = nullptr;

	return true;
}

void StageManager::changeStage()
{
	//Data manager에게 넘겨받아야할 데이터
	int boxNumWidth = 48;
	int boxNumHeight = 20;
	Size boxSize = Size( 32 , 32 );
	std::map<int , ObjectType> data;

	char* rawValue;
	char rawData[1024*10];

	strcpy( rawData , MAPDATA );
	rawValue = strtok( rawData , " \n" );

	int value;
	for( int yIdx = boxNumHeight - 1; yIdx >= 0; yIdx-- )
	{
		for( int xIdx = 0; xIdx <boxNumWidth; xIdx++ )
		{
			value = atoi( rawValue );
			data[boxNumWidth * yIdx + xIdx] = ( ObjectType )value;
			rawValue = strtok( nullptr , " \n" );
		}
	}
	auto m_WorldScene = WorldScene::createSceneWithData( Vec2( boxNumWidth , boxNumHeight ) , boxSize , data , "background.png" );
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
