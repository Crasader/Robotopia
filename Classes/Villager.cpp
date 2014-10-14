#include "Villager.h"
#include "GameManager.h"

USING_NS_CC;

bool Villager::init()
{
	if( !InteractiveObject::init() )
	{
		return false;
	}
	m_Type = OT_VILLAGER;
	m_MainSprite = Sprite::createWithSpriteFrameName( "Villager.png" );
	m_IsOnStore = false;
	this->addChild( m_MainSprite );
	return true;
}

void Villager::update( float dTime )
{
	Point pos = this->getPosition();

	//��ǥ ���� ó��
	pos.x += m_Velocity.x*dTime;
	pos.y += m_Velocity.y*dTime;

	m_Velocity.y -= GRAVITY*dTime;
	m_IsFlying = true;

	this->setPosition( pos );
}

void Villager::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	switch( enemy->getType() )
	{
		case OT_FLOOR:
			if( dir & DIR_DOWN )
			{
				m_IsFlying = false;
				m_Velocity.y = 0;
			}
			break;
		case OT_BLOCK:
			if( dir & DIR_DOWN )
			{
				m_IsFlying = false;
				m_Velocity.y = 0;
			}
			if( dir&DIR_LEFT || dir&DIR_RIGHT )
			{
				m_Velocity.x = 0;
			}
			if( dir&DIR_UP )
			{
				m_Velocity.y = 0;
			}
			break;
		case OT_PLAYER:
			if( !m_IsOnStore && GET_INPUT_MANAGER()->getKeyState( KC_UP ) )
			{
				m_IsOnStore = true;
				GET_STAGE_MANAGER()->showStore();
			}
	}
}

cocos2d::Rect Villager::getRect()
{
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	return InteractiveObject::getRect();
}

