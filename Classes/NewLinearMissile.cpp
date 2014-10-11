
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

	return true;
}


void NewLinearMissile::setAttribute(bool isPlayerMissile, float velocity, float degree, float setDamage)
{
	m_IsPlayerMissile = isPlayerMissile;
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}

	m_Degree = degree;
	m_Velocity.x = cos(PIE / 180 * degree) * velocity;
	m_Velocity.y = sin(PIE / 180 * degree) * abs(velocity);

	m_Damage = setDamage;
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
	bool effectAdd = false;


	//�÷��̾� �̻��ϰ� ���� �̻����� ������� ������� �κ�
	if (m_IsPlayerMissile)
	{
		switch (enemy->getType())
		{
		case OT_MONSTER:

			effectAdd = true;
			break;
		case OT_RUSH_MONSTER:
			effectAdd = true;

			break;
		}
	}
	else
	{
		switch (enemy->getType())
		{
		case OT_PLAYER:
			effectAdd = true;
			break;
		}
	}


	
	if (effectAdd)
	{
		GET_EFFECT_MANAGER()->createEffect(ET_NEW_LINEAR_MISSILE_COLLISION, this->getRect(), dir, 1);
	}

	return;
}


