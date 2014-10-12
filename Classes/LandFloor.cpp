#include "LandFloor.h"
#include "GameManager.h"

USING_NS_CC;

bool LandFloor::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "floor.png" );
	this->setAnchorPoint( Point::ZERO );
	this->addChild( m_MainSprite);

	m_Type = OT_FLOOR;
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;
	m_IsOverlapable = true;

	return true;
}

