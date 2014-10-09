#include "GameManager.h"
#include "GameLayer.h"
#include "LandFloor.h"
#include "LandBlock.h"
#include "RushMonster.h"
#include "Villager.h"
#include "LinearMissile.h"
#include "AimingMissile.h"
#include "LandGateway.h"
#include "View.h"
#include "Player.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool GameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	m_Player = nullptr;
	m_InteractiveObjects.clear();
	m_CollisionInformations.clear();
	m_ObjectsPositionHash.clear();
	this->scheduleUpdate();

	return true;
}

bool GameLayer::initWorldFromData( Vec2 boxNum , Size boxSize , std::map<int , ObjectType> MapData , char* BGpath )
{
	m_BoxWidthNum = boxNum.x;
	m_BoxHeightNum = boxNum.y;
	m_BoxSize = boxSize;
	m_MapData = MapData;
	m_MapRect.setRect( 0 , 0 , m_BoxSize.width * m_BoxWidthNum , m_BoxSize.height * m_BoxHeightNum );

	for( int yIdx = 0; yIdx < m_BoxHeightNum; yIdx++ )
	{
		for( int xIdx = 0; xIdx < m_BoxWidthNum; xIdx++ )
		{
			addObjectByMapdata( xIdx , m_BoxHeightNum - yIdx );
		}
	}
	addMovingBackground( BGpath );

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
			break;
		default:
			return nullptr;
	}
	object->setAnchorPoint( Point(0.5,0.5) );
	object->setPosition( position );
	m_InteractiveObjects.push_back( object );
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
	return addObjectByMapdata( m_MapData[yIdx*m_BoxWidthNum + xIdx] , xIdx , yIdx );
}

void GameLayer::update( float dTime )
{
	if( m_Player != nullptr )
	{
		View::setViewPort( this , m_Player->getRect().origin , Point( 0.5 , 0.5 ) );
		makeHash();
		collisionCheck( dTime );
		removeObject();
	}
}

void GameLayer::collisionCheck(float dTime)
{
	for( auto subject: m_InteractiveObjects )
	{
		collisionCheckbyHash( subject , dTime );
	}

	for( auto collisionInfo : m_CollisionInformations )
	{
		collisionInfo.subject->collisionOccured( collisionInfo.object , collisionInfo.directions );
	}
	m_CollisionInformations.clear();
	m_ObjectsPositionHash.clear();
}

void GameLayer::collisionCheckbyHash( InteractiveObject* subject, float dTime )
{
	Directions collisionDirections;

	int curX = positionToIdxOfMapData( subject->getPosition() ).x;
	int curY = positionToIdxOfMapData( subject->getPosition() ).y;

	for( int xIdx = curX - 2; xIdx < curX + 3; ++xIdx )
	{
		for( int yIdx = curY - 2; yIdx < curY + 3; ++yIdx )
		{
			for( auto object : m_ObjectsPositionHash[xIdx*yIdx + xIdx] )
			{
				collisionDirections = subject->collisionCheck( object , dTime );
				if( collisionDirections )
				{
					m_CollisionInformations.push_back( CollisionInformation( subject , object , collisionDirections ) );
				}
			}
		}
	}
}

void GameLayer::makeHash()
{
	int x = 0;
	int y = 0;
	for( auto object : m_InteractiveObjects )
	{
		x = positionToIdxOfMapData( object->getPosition() ).x;
		y = positionToIdxOfMapData( object->getPosition() ).y;
		m_ObjectsPositionHash[x*y + x].push_back( object );
	}
}



void GameLayer::removeObject()
{
	for( auto objectIter = m_InteractiveObjects.begin(); objectIter != m_InteractiveObjects.end(); )
	{
		auto object = *objectIter;
		if( object->isDestroyed() )
		{
			objectIter = m_InteractiveObjects.erase( objectIter );
			removeChild( object );
		}
		else
		{
			objectIter++;
		}
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

cocos2d::Vec2 GameLayer::positionToIdxOfMapData( cocos2d::Point position )
{
	Vec2 curPosIdx = Vec2(-1 , -1); 
	if( m_MapRect.containsPoint( position ) )
	{
		curPosIdx.x = position.x / m_BoxSize.width;
		curPosIdx.y = position.y / m_BoxSize.height;
	}
	_ASSERT( curPosIdx != Vec2( -1 , -1 ) ); //맵안에 있지 않은 위치
	return curPosIdx;
}

ObjectType GameLayer::getMapDataInPositionWithIdx( int xIdx , int yIdx )
{
	return m_MapData[yIdx*m_BoxHeightNum + xIdx];
}

ObjectType GameLayer::getMapDataInPosition( cocos2d::Point position )
{
	int xIdx = positionToIdxOfMapData( position ).x;
	int yIdx = positionToIdxOfMapData( position ).y;
	return getMapDataInPositionWithIdx( xIdx , yIdx );
}

std::vector<InteractiveObject*> GameLayer::getObjectsByPosition( cocos2d::Point position )
{
	std::vector<InteractiveObject*> collectObjects;

	for( auto object : m_InteractiveObjects )
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

	for( auto object : m_InteractiveObjects )
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



