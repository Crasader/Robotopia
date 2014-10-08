

#include "AimingMissile.h"
#include "GameManager.h"
#include <math.h>

USING_NS_CC;

bool AimingMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}
	m_Type = OT_AIMING_MISSILE;

	m_MainSprite = Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation("AimingMissile%d.png", 1, 8, 0.1f);
	m_Animations[0] = animation;
	m_MainSprite->runAction(RepeatForever::create(Animate::create(m_Animations[0])));

	this->addChild(m_MainSprite);

	
	this->scheduleUpdate();

	return true;
}



void AimingMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, Point myPos, Point targetPos)
{
	float distance = sqrt((myPos.x - targetPos.x)*(myPos.x - targetPos.x) + (myPos.y - targetPos.y) * (myPos.y - targetPos.y));

	if (distance != 0)
	{
		m_Velocity.x = ((targetPos.x - myPos.x) / distance) * velocity;
		m_Velocity.y = ((targetPos.y - myPos.y) / distance) * velocity;
	
	}
	else
	{
		m_Velocity.x = velocity;
		m_Velocity.y = 0;
	}

	if (m_Velocity.x > 0)
	{
		m_MainSprite->setFlippedX(true);
	}

	return;
}

void AimingMissile::update(float dTime)
{
	Point pos = this->getPosition();

	pos.x += m_Velocity.x * dTime;
	pos.y += m_Velocity.y * dTime;

	this->setPosition(pos);
}


