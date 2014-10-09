#include "LandBlock.h"
#include "GameManager.h"

USING_NS_CC;

bool LandBlock::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "block.png" );
	this->addChild( m_MainSprite , 10 );
// 	m_PieceSprite = GET_RESOURCE_MANAGER()->createSprite( "blockPiece.png" );
// 	float bufferX = (m_PieceSprite->getContentSize().width - m_MainSprite->getContentSize().width)* 0.5;
// 	float bufferY = ( m_PieceSprite->getContentSize().height - m_MainSprite->getContentSize().height )*0.5;
// 	m_PieceSprite->setPosition( bufferX , bufferY );
// 	this->addChild( m_PieceSprite , 0 );

	m_Type = OT_BLOCK;

	return true;
}

