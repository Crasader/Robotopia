#include "LandFloorGateway.h"
#include "GameManager.h"

USING_NS_CC;

bool LandFloorGateway::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( ST_FLOORGATEWAY );
	m_MainSprite->setAnchorPoint( Point( 0.5 , 0 ) );
	this->addChild( m_MainSprite );
	m_OpenAnimation = GET_RESOURCE_MANAGER()->createAnimation( AT_FLOORGATEWAY_OPEN );

	m_Type = OT_FLOOR_GATEWAY;
	m_Width = 32;
	m_Height = 32;
	m_IsOverlapable = true;
	m_IsOpen = false;

	return true;
}

void LandFloorGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( !m_IsOpen && enemy->getType() == OT_PLAYER && GET_INPUT_MANAGER()->getKeyState( KC_UP ) )
	{
		m_IsOpen = true;
		auto animate = Animate::create( m_OpenAnimation );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandFloorGateway::gotoNextFloor , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}

void LandFloorGateway::gotoNextFloor( Ref* sender )
{
	GET_STAGE_MANAGER()->changeFloor( GET_STAGE_MANAGER()->getCurStageNum() + 1);
}

