#include "LandTurret.h"
#include "GameManager.h"
#include "AimingMissile.h"

USING_NS_CC;

bool LandTurret::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_AttackSpeed = 0.5f;
	m_Range = 320.0f;
	m_Damage = 5.0f;
	m_IsOverlapable = true; //충돌 안함
	m_MainSprite = Sprite::create( "turret.png" );
	this->setAnchorPoint( Point::ZERO );
	this->addChild( m_MainSprite );

	m_Type = OT_FLOOR;
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	return true;
}

void LandTurret::update( float dTime )
{
	Point myPosition = this->getPosition();
		Point playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	if( isInRange( playerPosition ) )
	{
		static float accTime = 0;
		accTime += dTime;
		if( accTime > m_AttackSpeed )
		{
			accTime = 0;
			auto missle = ( AimingMissile* )( GET_STAGE_MANAGER()->addObject( OT_AIMING_MISSILE , myPosition ) );
			missle->setAttribute( false , 200 , myPosition , playerPosition , m_Damage );
		}
	}
	
}

bool LandTurret::isInRange( Point position )
{
	return (m_Range > position.distance( this->getPosition() ));
}

