#include "BatMonster.h"
#include "GameManager.h"
#include "AimingMissile.h"
#include "MeleeMissile.h"


USING_NS_CC;

bool BatMonster::init()
{
	if (!Monster::init())
	{
		return false;
	}

	m_Type = OT_BAT_MONSTER;

	m_Animations[BM_FIND] = GET_RESOURCE_MANAGER()->createAnimation(AT_MONSTER_BAT, 0.1f);
	m_Animations[BM_ATTACK] = GET_RESOURCE_MANAGER()->createAnimation(AT_MONSTER_BAT, 0.05f);

	m_AnimationNum = BM_STATE_NUM;


	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_MONSTER_BAT);

	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	this->addChild(m_MainSprite);
	m_MoveSpeed = 70;
	m_IsOnGravity = true;
	m_IsOverlapable = true;
	m_IsRightDirection = false;
	m_AttackTime = 0;

	m_Info.maxHp = 40;
	m_Info.hp = m_Info.maxHp;

	changeState(BM_FIND);

	return true;
}

void BatMonster::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	switch (enemy->getType())
	{
	case OT_LINEAR_MISSILE:
	case OT_MELEE_MISSILE:
	case OT_NEW_LINEAR_MISSILE:
		GET_STAGE_MANAGER()->setLastMonster(this);

		auto bullet = (MeleeMissile*)enemy;

		m_Info.hp -= bullet->getDamage();

		if (m_Info.hp <= 0 && !m_IsDestroyed)
		{
			GET_STAGE_MANAGER()->addObject(OT_STEAM_PACK, this->getPosition());
			m_IsDestroyed = true;
		}
		break;

	}
}

void BatMonster::update(float dTime)
{
	auto pos = this->getPosition();

	pos.x += m_Velocity.x*dTime;
	pos.y += m_Velocity.y*dTime;

	this->setPosition(pos);


	if (m_State == BM_FIND)
	{
		auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
		float distance = sqrt((pos.x - playerPos.x)*(pos.x - playerPos.x) + (pos.y - playerPos.y)*(pos.y - playerPos.y));

		if (distance >= 300)
		{

			if (playerPos.x < pos.x)
			{
				m_MainSprite->setFlippedX(false);
				m_IsRightDirection = true;
				m_Velocity.x = -m_MoveSpeed;
			}
			else
			{
				m_MainSprite->setFlippedX(true);
				m_IsRightDirection = false;
				m_Velocity.x = m_MoveSpeed;
			}

			if (playerPos.y > pos.y - 50)
			{
				m_Velocity.y = m_MoveSpeed;
			}
			else
			{
				m_Velocity.y = -m_MoveSpeed;
			}
		}
		else if (distance <= 100)
		{
			if (playerPos.x < pos.x)
			{
				m_MainSprite->setFlippedX(true);
				m_IsRightDirection = false;
				m_Velocity.x = m_MoveSpeed;
			}
			else
			{
				m_MainSprite->setFlippedX(false);
				m_IsRightDirection = true;
				m_Velocity.x = m_MoveSpeed;
			}

			if (playerPos.y > pos.y - 50)
			{
				m_Velocity.y = m_MoveSpeed;
			}
			else
			{
				m_Velocity.y = -m_MoveSpeed;
			}
		}
		else
		{
			if (playerPos.y > pos.y - 50)
			{
				m_Velocity.y = m_MoveSpeed;
			}
			else
			{
				changeState(BM_ATTACK);
			}
		}
	}
	else
	{
		m_AttackTime += dTime;

		if (m_AttackTime >= 4)
		{
			changeState(BM_FIND);
			m_AttackTime = 0;
		}
	}
}

void BatMonster::changeState(State state)
{
	//이미 해당 상태인 경우 아무 처리도 하지 않는다.
	if (m_State == state)
	{
		return;
	}

	if (state == BM_ATTACK)
	{
		m_Velocity.x = 0;
		m_Velocity.y = 0;
	}
	m_State = state;
	m_MainSprite->stopAllActions();

	auto animate = Animate::create(m_Animations[state]);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(BatMonster::endAnimation, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_MainSprite->runAction(RepeatForever::create(sequence));
}

void BatMonster::endAnimation(Ref* sender)
{
	if (m_State == BM_ATTACK && m_AttackTime>=2)
	{
		auto myPosition = this->getPosition();
		auto playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
		
		auto missile = (AimingMissile*)(GET_STAGE_MANAGER()->addObject(OT_AIMING_MISSILE, myPosition));
		missile->setAttribute(false, 200, myPosition, playerPosition, 8);
	}
}

Rect BatMonster::getRect()
{
	m_Width = m_MainSprite->getContentSize().width * 2;
	m_Height = m_MainSprite->getContentSize().height * 2;

	Point pos = this->getPosition();
	Point Anchor = this->getAnchorPoint();

	return Rect(pos.x - Anchor.x*m_Width, pos.y - Anchor.y*m_Height, m_Width, m_Height);
}
