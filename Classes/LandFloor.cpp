#include "LandFloor.h"
#include "GameManager.h"

USING_NS_CC;

bool LandFloor::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = Sprite::create("Floor.png");
	this->addChild( m_MainSprite);

	m_Type = OT_FLOOR;
	m_Width = 32;
	m_Height = 32;

	m_IsOverlapable = true;
	return true;
}

