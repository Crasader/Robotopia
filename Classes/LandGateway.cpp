#include "LandGateway.h"
#include "GameManager.h"
#include "GameLayer.h"

USING_NS_CC;

bool LandGateway::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	findNextStage();
	this->addChild( m_MainSprite );
	m_OpenAnimaion = GET_RESOURCE_MANAGER()->createAnimation( AT_GATEWAY_ACT , 0.5f );
	m_OpenAnimaion->retain();
	m_isOpen = false;
	m_IsActive = false;

	return true;
}

void LandGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( !m_isOpen && enemy->getType() == OT_PLAYER && m_IsActive )
	{
		m_isOpen = true;
		auto animate = Animate::create( m_OpenAnimaion );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandGateway::gotoNextLevel , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}

void LandGateway::findNextStage()
{
	int result = 0;
	Point curPos = this->getPosition();
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).y;
	Direction sentinelDir = findCentinelNeighborDir( Vec2( stageXIdx , stageYIdx ) );

	int floorXIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).x;
	int floorYIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).y;
	m_NextFloorIdx = findNeighbor( Vec2( floorXIdx , floorYIdx ) , sentinelDir );
	result = GET_STAGE_MANAGER()->getFloorDataByIdx( m_NextFloorIdx.x , m_NextFloorIdx.y );

	if( result != 0 )
	{
		m_IsActive = true;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayActive.png" );
	}
	else
	{
		m_IsActive = false;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayUnactive.png" );
	}

	m_NextFloorNum = result;
	
}

void LandGateway::gotoNextLevel(Ref* sender)
{
	//다음 월드 씬으로 변경해주는 함수호출
	GET_STAGE_MANAGER()->changeStage( m_NextFloorNum );

}

Direction LandGateway::findCentinelNeighborDir( Vec2 stageIdx )
{
	int result = 1;
	while( result < 16 )
	{
		if( GET_STAGE_MANAGER()->getStageDataInPositionWithIdx( 
			findNeighbor( stageIdx , ( Direction )result ).x , findNeighbor( stageIdx , ( Direction )result ).y ) == OT_SENTINEL )
		{
			break;
		}
		result *= 2;
	}
	return ( Direction )result;
}

Vec2 LandGateway::findNeighbor( cocos2d::Vec2 Idx , Direction dir )
{
	int x = Idx.x;
	int y = Idx.y;

	switch( dir )
	{
		case DIR_LEFT:
			x--;
			break;
		case DIR_RIGHT:
			x++;
			break;
		case DIR_UP:
			y++;
			break;
		case DIR_DOWN:
			y--;
			break;
		default:
			break;
	}
	return Vec2( x , y );
}

