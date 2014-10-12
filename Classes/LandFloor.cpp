#include "LandFloor.h"
#include "GameManager.h"

USING_NS_CC;

bool LandFloor::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = Sprite::create();
	this->addChild( m_MainSprite);
	m_PieceSprite = GET_RESOURCE_MANAGER()->createSprite( "FloorPiece.png" );
	float bufferX = (m_PieceSprite->getContentSize().width - m_MainSprite->getContentSize().width)* 0.5;
	float bufferY = ( m_PieceSprite->getContentSize().height - m_MainSprite->getContentSize().height )*0.5;
	m_PieceSprite->setPosition( bufferX , bufferY );
	this->addChild( m_PieceSprite);

	m_Type = OT_FLOOR;
	m_Width = 32;
	m_Height = 32;

	m_IsOverlapable = true;

	return true;
}

