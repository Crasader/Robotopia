
#include "NewLinearMissile.h"

#include "GameManager.h"
#include "Utils.h"
#include <math.h>


USING_NS_CC;

bool NewLinearMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	m_Type = OT_NEW_LINEAR_MISSILE;

	m_MainSprite = Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_NEW_LINEAR_MISSILE_FLYING, 0.05f);
	m_Animations[0] = animation;
	m_MainSprite->runAction(RepeatForever::create(Animate::create(m_Animations[0])));

	this->addChild(m_MainSprite);

	this->scheduleUpdate();
	return true;
}


void NewLinearMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree)
{
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}

	m_Degree = degree;
	m_Velocity.x = cos(PIE / 180 * degree) * velocity;
	m_Velocity.y = sin(PIE / 180 * degree) * abs(velocity);
}

void NewLinearMissile::update(float dTime)
{
	Point pos = this->getPosition();
	pos.x += m_Velocity.x * dTime;
	pos.y += m_Velocity.y * dTime;

	this->setPosition(pos);
}

void NewLinearMissile::collisionOccured(InteractiveObject* enemy, Directions dir)
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
		// New
		GET_EFFECT_MANAGER()->createEffect(ET_NEW_LINEAR_MISSILE_COLLISION, this->getRect(), dir, 1);
	}
	return;
}


