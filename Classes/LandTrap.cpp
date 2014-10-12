#include "LandTrap.h"
#include "GameManager.h"

USING_NS_CC;

bool LandTrap::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( ST_TRAP );
	this->addChild( m_MainSprite );
	m_ActivateAnimation = GET_RESOURCE_MANAGER()->createAnimation( AT_TRAP_ACTIVATE , 0.2f);
	m_IsActive = false;
	m_Type = OT_TRAP;
	m_IsOverlapable = true;
	return true;
}

void LandTrap::update( float dTime )
{
	if( !m_IsActive )
	{
		static float accTime = 0.f;
		accTime += dTime;
		float firePeriod = 3.f;
		if( accTime > firePeriod )
		{
			m_IsActive = true;
			accTime = 0.f;
			auto animate = Animate::create( m_ActivateAnimation );
			auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandTrap::endAnimation , this ) );
			auto action = Sequence::create( animate , callfunc , NULL );
			m_MainSprite->runAction( action );
		}
	}
}

void LandTrap::endAnimation( cocos2d::Ref* sender )
{
	m_IsActive = false;
}

