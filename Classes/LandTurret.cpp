#include "LandTurret.h"
#include "GameManager.h"

USING_NS_CC;

bool LandTurret::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "turret.png" );
	this->setAnchorPoint( Point::ZERO );
	this->addChild( m_MainSprite );

	m_Type = OT_FLOOR;
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	return true;
}

void LandTurret::update( float dTime )
{
	static float accTime = 0;
	accTime += dTime;
	if( accTime > m_AttackSpeed )
	{

	}
}

