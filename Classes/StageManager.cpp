#include "StageManager.h"
#include "GameLayer.h"

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

