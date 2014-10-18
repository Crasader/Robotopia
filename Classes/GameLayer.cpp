
#include "GameManager.h"
#include "GameLayer.h"
#include "LandFloor.h"
#include "LandBlock.h"
#include "LandFloorGateway.h"
#include "RushMonster.h"
#include "BatMonster.h"
#include "Boss.h"
#include "Villager.h"
#include "NewLinearMissile.h"
#include "AimingMissile.h"
#include "LinearMissile.h"
#include "MeleeMissile.h"
#include "SteamPack.h"
#include "LandGateway.h"
#include "LandTurret.h"
#include "LandTrap.h"
#include "View.h"
#include "Player.h"
#include "InteractiveObject.h"
#include "ItemLeg.h"

USING_NS_CC;

#define MAX_BOX_OBJECTS 10
#define MAX_GATEWAY_NUM 100
#define	MAX_OBJECT_NUM 1024
#define MAX_COLLISION_INFO 1024

bool GameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	m_IsShaking = false;
	m_IsVisited = false;
	m_Objects.clear();
	m_InteractiveObjects.clear();
	m_CollisionInformations.clear();
	m_AddObjects.clear();
	m_Gateways.clear();
	memset( m_MapData , 0 , sizeof( ObjectType )*MAX_POSITION_NUM );
	memset( m_ObjectPositionsHash , 0 , sizeof( std::vector<InteractiveObject*> )*MAX_POSITION_NUM );

	m_Gateways.reserve( MAX_GATEWAY_NUM );
	m_InteractiveObjects.reserve( MAX_OBJECT_NUM );
	m_CollisionInformations.reserve( MAX_COLLISION_INFO );
	return true;
}

bool GameLayer::initWorldFromData( Vec2 boxNum , Size boxSize , std::map<int , ObjectType> MapData , char* BGpath )
{
	m_IsInit = true;
	m_BoxWidthNum = boxNum.x;
	m_BoxHeightNum = boxNum.y;
	m_BoxSize = boxSize;
	m_MapRect.setRect( 0 , 0 , m_BoxSize.width * m_BoxWidthNum , m_BoxSize.height * m_BoxHeightNum );

	for( int yIdx = 0; yIdx < m_BoxHeightNum; yIdx++ )
	{
		for( int xIdx = 0; xIdx < m_BoxWidthNum; xIdx++ )
		{
			m_MapData[yIdx*m_BoxWidthNum + xIdx] = MapData[yIdx*m_BoxWidthNum + xIdx];
			addObjectByMapdata( xIdx , yIdx );
		}
	}
	addMovingBackground( BGpath );
	makeHashTable();
	m_IsInit = false;
	return true;
}




//타입별 객체를 월드 위치좌표에 추가해준다.
InteractiveObject*	 GameLayer::addObject( ObjectType type , Point position )
{
	InteractiveObject* object;
	GameLayer::ZOrder zOrder;
	switch( type )
	{
		case OT_PLAYER:
			object = Player::create();
			zOrder = GameLayer::ZOrder::LAND_OBJECT;
			m_Player = (Player*)object;
			break;
		case OT_FLOOR:
			object = LandFloor::create();
			zOrder = GameLayer::ZOrder::LAND_OBJECT;
			break;
		case OT_BLOCK:
			object = LandBlock::create();
			zOrder = GameLayer::ZOrder::LAND_OBJECT;
			break;
 		case OT_LINEAR_MISSILE:
			object = LinearMissile::create();
 			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_AIMING_MISSILE:
			object = AimingMissile::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_RUSH_MONSTER:
			object = RushMonster::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_VILLAGER:
			object = Villager::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_GATEWAY:
			object = LandGateway::create();
			zOrder = GameLayer::ZOrder::LAND_OBJECT;
			m_Gateways.push_back( (LandGateway*)object );
			break;
		case OT_MELEE_MISSILE:
			object = MeleeMissile::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_STEAM_PACK:
			object = SteamPack::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_NEW_LINEAR_MISSILE:
			object = NewLinearMissile::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_TURRET:
			object = LandTurret::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_BAT_MONSTER:
			object = BatMonster::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_ITEM_LEG:
			object = ItemLeg::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_TRAP:
			object = LandTrap::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		case OT_FLOOR_GATEWAY:
			object = LandFloorGateway::create();
			zOrder = GameLayer::ZOrder::LAND_OBJECT;
			break;
		case OT_BOSS:
			object = Boss::create();
			zOrder = GameLayer::ZOrder::GAME_OBJECT;
			break;
		default:
			return nullptr;
	}
	object->retain();
	object->setAnchorPoint( Point( 0.5 , 0.5 ) );
	object->setPosition( position );
	if( m_IsInit )
	{
		m_Objects.push_back( object );
	}
	else
	{
		m_AddObjects.push_back( object );
	}
	this->addChild( object , zOrder );
	return object;
}

//맵데이터를 보고 객체를 추가한다. 인덱스 활용
InteractiveObject*	GameLayer::addObjectByMapdata( ObjectType type , int xIdx , int yIdx )
{
	return addObject( type , Point(xIdx*m_BoxSize.width , yIdx*m_BoxSize.height ));
}

//맵데이터를 보고 객체를 추가한다. 인덱스만 받아도 충분
InteractiveObject*	GameLayer::addObjectByMapdata( int xIdx , int yIdx )
{
	ObjectType ot = m_MapData[yIdx*m_BoxWidthNum + xIdx];
	return addObjectByMapdata( ot , xIdx , yIdx );
}

void GameLayer::update( float dTime )
{
	static float accTime = 0.f;
	if( m_IsVisited == false)
	{
		m_IsVisited = true;
		initGateways();
	}

	if( m_Player != nullptr )
	{
		if( m_IsShaking )
		{
			int shakingTime = 2.0f;
			accTime += dTime;
			View::setViewPortShake( this , m_Player->getRect().origin , Point( 0.5 , 0.5 ) ); 
			if( accTime > shakingTime )
			{
				m_IsShaking = false;
				accTime = 0.f;
			}
		}
		else
		{
			View::setViewPort( this , m_Player->getRect().origin , Point( 0.5 , 0.5 ) );
		}

		findActiveObjects();
		collisionCheck( dTime );
		collisionProc( dTime );
  		for( auto& object : m_InteractiveObjects )
		{
			object->update( dTime );
		}
		editHashTable();
		removeObjects();
		m_CollisionInformations.clear();
	}
}

void GameLayer::makeHashTable()
{
	int x = 0;
	int y = 0;
	int sum = 0;
	for( auto object : m_Objects )
	{
		x = positionToIdxOfStageData( object->getPosition() ).x;
		y = positionToIdxOfStageData( object->getPosition() ).y;
		sum = y*m_BoxWidthNum + x;
		if( sum >= 0 && sum < m_BoxHeightNum*m_BoxWidthNum )
		{
			m_ObjectPositionsHash[sum].push_back( object );
		}
	}
}

void GameLayer::findActiveObjects()
{
	float winPosX = -this->getPosition().x;
	float winPosY = -this->getPosition().y;
	Size winSize = Director::getInstance()->getWinSize();
	Point start = positionToIdxOfStageData( Vec2(winPosX , winPosY) );
	Point end = positionToIdxOfStageData( Vec2( winPosX + winSize.width , winPosY + winSize.height ) );
	m_InteractiveObjects.clear();
	for( auto& addObject : m_AddObjects )
	{
		m_InteractiveObjects.push_back( addObject );
	}

	for( int xIdx = start.x; xIdx < end.x + 1; ++xIdx )
	{
		for( int yIdx = start.y; yIdx < end.y + 1; ++yIdx )
		{

			int sum = xIdx + yIdx * m_BoxWidthNum;
			if( xIdx < 0 || yIdx < 0 || xIdx + yIdx * m_BoxWidthNum > m_BoxWidthNum*m_BoxHeightNum )
			{
				continue;
			}
			auto objects = m_ObjectPositionsHash[sum];
			for( auto& object : objects)
			{
				m_InteractiveObjects.push_back( object );
			}
		}
	}
}

void GameLayer::collisionCheck(float dTime)
{
	for( auto& subject: m_InteractiveObjects )
	{
		if( subject->getType() != OT_BLOCK && subject->getType() != OT_FLOOR && subject->getType() != OT_TRAP )
		{
			collisionCheckbyHash( subject , dTime );
		}
	}
}

void GameLayer::collisionProc( float dTime )
{
	for( auto& collisionInfo : m_CollisionInformations )
	{
		collisionInfo.subject->collisionOccured( collisionInfo.object , collisionInfo.directions );
	}

	m_CollisionInformations.clear();
}


void GameLayer::collisionCheckbyHash( InteractiveObject* subject, float dTime )
{
	Directions collisionDirections;

	int curX = positionToIdxOfStageData( subject->getPosition() ).x;
	int curY = positionToIdxOfStageData( subject->getPosition() ).y;

	for( int xIdx = curX - 2; xIdx < curX + 3; ++xIdx )
	{
		for( int yIdx = curY - 2; yIdx < curY + 3; ++yIdx )
		{
			int sum = xIdx*yIdx + xIdx;
			if( sum < m_BoxWidthNum*m_BoxHeightNum && sum >= 0 )
			{
				auto objects = m_ObjectPositionsHash[sum];
				for( auto& object : objects )
				{
					if( object != subject )
					{
						collisionDirections = subject->collisionCheck( object , dTime );
						if( collisionDirections )
						{
							m_CollisionInformations.push_back(CollisionInformation( subject , object , collisionDirections ));
						}
					}
				}
			}
		}
	}
}


void GameLayer::editHashTable()
{
	float winPosX = -this->getPosition().x;
	float winPosY = -this->getPosition().y;
	Size winSize = Director::getInstance()->getWinSize();
	Point start = positionToIdxOfStageData( Vec2( winPosX , winPosY ) );
	Point end = positionToIdxOfStageData( Vec2( winPosX + winSize.width , winPosY + winSize.height ) );
	for( int xIdx = start.x; xIdx < end.x + 1; ++xIdx )
	{
		for( int yIdx = start.y; yIdx < end.y + 1; ++yIdx )
		{

			int sum = xIdx + yIdx * m_BoxWidthNum;
			if( xIdx < 0 || yIdx < 0 || xIdx + yIdx * m_BoxWidthNum > m_BoxWidthNum*m_BoxHeightNum )
			{
				continue;
			}
			m_ObjectPositionsHash[sum].clear();
		}
	}
	int x = 0;
	int y = 0;
	int sum = 0;
	for( auto object : m_InteractiveObjects)
	{
		x = positionToIdxOfStageData( object->getPosition() ).x;
		y = positionToIdxOfStageData( object->getPosition() ).y;
		sum = y*m_BoxWidthNum+x;
		if( sum >= 0 && sum < m_BoxHeightNum*m_BoxWidthNum )
		{
			m_ObjectPositionsHash[sum].push_back( object );
		}
	}
}



void GameLayer::removeObjects()
{
	for( auto objectIter = m_Objects.begin(); objectIter != m_Objects.end(); )
	{
		auto object = *objectIter;
		
		if( (object->isDestroyed() || isOutOfStageMap( object->getPosition() )) && object->getType() != OT_PLAYER )
		{
			objectIter = m_Objects.erase( objectIter );
			removeChild( object );
		}
		else
		{
			objectIter++;
		}
	}
}

void GameLayer::removeObject( InteractiveObject* deleteObject )
{
	if( deleteObject == m_Player )
	{
		m_Player = nullptr;
	}
	auto deleteIter = std::find( m_Objects.begin() , m_Objects.end() , deleteObject );
	if( deleteIter != m_Objects.end() )
	{
		m_InteractiveObjects.erase(deleteIter);
		removeChild( deleteObject );
	}
}

void GameLayer::addMovingBackground( char* BGpath )
{
	auto backgroundSprite = GET_RESOURCE_MANAGER()->createSprite( BGpath );
	Size spriteSize = backgroundSprite->getContentSize();
	int xSpriteNum = ( m_MapRect.size.width / spriteSize.width );
	int ySpriteNum = ( m_MapRect.size.height / spriteSize.height );
	for( int yIdx = 0; yIdx <= ySpriteNum; ++yIdx )
	{
		for( int xIdx = 0; xIdx <= xSpriteNum; ++xIdx )
		{
			backgroundSprite = GET_RESOURCE_MANAGER()->createSprite( BGpath );
			backgroundSprite->setAnchorPoint( Point::ZERO );
			backgroundSprite->setPosition( xIdx*(spriteSize.width-10), yIdx*(spriteSize.height-10) );
			this->addChild( backgroundSprite , GameLayer::ZOrder::BACKGROUND);
		}
	}
}

cocos2d::Vec2 GameLayer::positionToIdxOfStageData( cocos2d::Point position )
{
	Vec2 curPosIdx = Vec2(-1 , -1); 
	curPosIdx.x = position.x / m_BoxSize.width;
	curPosIdx.y = position.y / m_BoxSize.height;
	return curPosIdx;
}

std::vector<InteractiveObject*> GameLayer::getObjectsByPosition( cocos2d::Point position )
{
	std::vector<InteractiveObject*> collectObjects;

	for( auto& object : m_Objects )
	{
		if( object->getRect().containsPoint( position ) )
		{
			collectObjects.push_back( object );
		}
	}
	return collectObjects;
}

std::vector<InteractiveObject*> GameLayer::getObjectsByRect( cocos2d::Rect checkRect )
{
	std::vector<InteractiveObject*> collectObjects;

	for( auto& object : m_Objects )
	{
		if( checkRect.intersectsRect( object->getRect() ) )
		{
			collectObjects.push_back( object );
		}
	}
	return collectObjects;
}

void GameLayer::addEffect( Sprite* sprite )
{
	this->addChild( sprite , ZOrder::EFFECT );
}

bool GameLayer::isOutOfStageMap( cocos2d::Point checkPosition )
{
	return !m_MapRect.containsPoint( checkPosition );
}

void GameLayer::initGateways()
{
	for( auto& gateway : m_Gateways )
	{
		gateway->findNextStage();
	}
}

