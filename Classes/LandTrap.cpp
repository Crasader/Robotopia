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
	m_MainSprite->setAnchorPoint( Point(0.5, 0) );
	m_MainSprite->setPosition( Point( 0 , -1*this->getRect().size.height) );
	this->addChild( m_MainSprite );
	m_ActivateAnimation = GET_RESOURCE_MANAGER()->createAnimation( AT_TRAP_ACTIVATE , 0.1f);
	m_Type = OT_TRAP;
	m_IsOverlapable = true;
	m_InitTime = GET_GAME_MANAGER()->getTime();
	return true;
}

void LandTrap::update( float dTime )
{
	if( isActive())
		{
			auto animate = Animate::create( m_ActivateAnimation );
			auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandTrap::endAnimation , this ) );
			auto action = Sequence::create( animate , callfunc , NULL );
			m_MainSprite->runAction( action );
		}
}

void LandTrap::endAnimation( cocos2d::Ref* sender )
{
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( ST_TRAP );
}

bool LandTrap::isActive()
{
	timeval curTime = GET_GAME_MANAGER()->getTime();
	int firePeriod = 5;
	if( ( curTime.tv_sec - m_InitTime.tv_sec ) % 10 > firePeriod )
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rect LandTrap::getRect()
{
	Rect resultRt;
	resultRt.setRect( this->getPosition().x , this->getPosition().y , 20 , 70 );
	return resultRt;
}

