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
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "Gateway0.png" );
	this->addChild( m_MainSprite );
	m_OpenAnimaion = GET_RESOURCE_MANAGER()->createAnimation( AT_GATEWAY_OPEN , 0.5f);
	m_OpenAnimaion->retain();
	m_isOpen = false;

	return true;
}

void LandGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( m_isOpen == false && enemy->getType() == OT_PLAYER )
	{
		m_isOpen = true;
		auto animate = Animate::create( m_OpenAnimaion );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandGateway::gotoNextLevel , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}

void LandGateway::gotoNextLevel(Ref* sender)
{
	//다음 월드 씬으로 변경해주는 함수호출
}

