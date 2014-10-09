#include "LinearMissile.h"
#include "GameManager.h"
#include "Utils.h"
#include <math.h>
#define PIE 3.141592

USING_NS_CC;

bool LinearMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	m_Type = OT_LINEAR_MISSILE;
	
	m_MainSprite = Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEAR_MISSILE, 0.05f);
	m_Animations[0] = animation;
	m_MainSprite->runAction(RepeatForever::create(Animate::create(m_Animations[0])));
	
	this->addChild(m_MainSprite);

	this->scheduleUpdate();
	return true;
}


void LinearMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree)
{
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}
	m_Degree = degree;
	m_Velocity.x = cos(PIE / 180 * degree)*velocity;
	m_Velocity.y = sin(PIE / 180 * degree)*abs(velocity);
}

void LinearMissile::update(float dTime)
{
	Point pos = this->getPosition();
	pos.x += m_Velocity.x * dTime;
	pos.y += m_Velocity.y * dTime;

	this->setPosition(pos);
}

