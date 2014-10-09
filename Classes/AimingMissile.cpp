

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
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_AIMINGMISSILE_FLYING, 0.2f);
	m_Animations[0] = animation;
	m_MainSprite->runAction(RepeatForever::create(Animate::create(m_Animations[0])));

	this->addChild(m_MainSprite);

	
	this->scheduleUpdate();

	return true;
}



void AimingMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, Point myPos, Point targetPos)
{
	float distance = sqrt((myPos.x - targetPos.x)*(myPos.x - targetPos.x) + (myPos.y - targetPos.y) * (myPos.y - targetPos.y));
	float degree = 0;

	if (distance != 0)
	{
		m_Velocity.x = ((targetPos.x - myPos.x) / distance) * velocity;
		m_Velocity.y = ((targetPos.y - myPos.y) / distance) * velocity;
		degree = acos((myPos.x - targetPos.x) / distance) * 180/PIE;
	
	}
	else
	{
		m_Velocity.x = velocity;
		m_Velocity.y = 0;
	}



	m_MainSprite->setRotation(degree);

	return;
}

void AimingMissile::update(float dTime)
{
	Point pos = this->getPosition();

	pos.x += m_Velocity.x * dTime;
	pos.y += m_Velocity.y * dTime;

	this->setPosition(pos);
}

void AimingMissile::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	m_IsPlayerMissile = IsPlayerMissile();


	//플레이어 미사일과 몬스터 미사일을 구분지어서 사라지는 부분
	if (m_IsPlayerMissile)
	{
		switch (enemy->getType())
		{
		case OT_MONSTER:
			m_IsDestroyed = true;
			break;
		case OT_RUSH_MONSTER:
			m_IsDestroyed = true;

			break;
		}
	}
	else
	{
		switch (enemy->getType())
		{
		case OT_PLAYER:
			m_IsDestroyed = true;
			break;
		}
	}


	//플레이어 미사일이든 몬스터 미사일이든 공통으로 충돌했을 때 사라지는 부분
	switch (enemy->getType())
	{
	case OT_FLOOR:
		m_IsDestroyed = true;
		break;
	case OT_BLOCK:
		m_IsDestroyed = true;
		break;

	case OT_VILLAGER:

		m_IsDestroyed = true;
		break;
	}

	if (m_IsDestroyed)
	{
		GET_EFFECT_MANAGER()->createEffect(ET_AIMING_MISSILE_COLLISION, this->getRect(), dir, 1);
	}
	return;
}


