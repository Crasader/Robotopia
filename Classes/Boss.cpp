#include "Boss.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "AimingMissile.h"
#include "MeleeMissile.h"
#include "NewLinearMissile.h"

USING_NS_CC;

bool Boss::init()
{
	if (!Monster::init())
	{
		return false;
	}

	m_Type = OT_BOSS;

	m_Animations[BO_STAND] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_STAND);
	m_Animations[BO_ATTACK] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_ATTACK);
	m_Animations[BO_MOVE] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_WALK);
	m_Animations[BO_JUMP] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_JUMP);


	m_MainSprite = Sprite::create();

	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	m_MainSprite->setColor(Color3B(185, 30, 30));

	this->addChild(m_MainSprite);

	changeState(BO_STAND);

	m_AIState = BA_WAIT;
	m_WaitTime = 0;
	m_AttackNum = 0;
	m_RushNum = 0;

	m_MoveSpeed = 300;
	m_IsOnGravity = true;
	m_IsGotoBottom = false;
	m_IsAttackEnd = false;

	m_Info.maxHp = 1700;
	m_Info.hp = m_Info.maxHp;

	m_IsRightDirection = false;
	m_MainSprite->setFlippedX(true);

	return true;
}

void Boss::changeState(State state)
{
	//이미 해당 상태인 경우 아무 처리도 하지 않는다.
	if (m_State == state)
	{
		return;
	}

	m_State = state;
	m_MainSprite->stopAllActions();

	auto animate = Animate::create(m_Animations[state]);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Boss::endAnimation, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_MainSprite->runAction(RepeatForever::create(sequence));
}

void Boss::endAnimation(cocos2d::Ref* sender)
{
	if (m_State == BO_ATTACK)
	{
		m_AttackNum++;

		if (m_AttackNum % 5 != 0)
		{
			changeState(BO_JUMP);
			m_Velocity.y = 520;
		}
		else
		{
			changeState(BO_JUMP);
			m_IsGotoBottom = true;
		}
	}
}

void Boss::update(float dTime)
{
	auto pos = getPosition();
	
	pos.x += m_Velocity.x*dTime;
	pos.y += m_Velocity.y*dTime;
	this->setPosition(pos);

	m_Velocity.y -= GRAVITY*dTime;


	switch (m_AIState)
	{
	case BA_WAIT:
		m_WaitTime += dTime;
		if (m_WaitTime >= 3)
		{
			m_WaitTime = 0;
			m_AIState = BA_ATTACK;
		}
		break;
	case BA_ATTACK:
		switch (m_State)
		{
		case BO_STAND:
			if (m_IsAttackEnd)
			{
				if (m_IsGotoBottom)
				{
					m_IsGotoBottom = false;
				}
				m_IsAttackEnd = false;
			}
			else if(m_State != BO_ATTACK)
			{
				m_WaitTime += dTime;
				if (m_WaitTime >= 0.5)
				{
					m_WaitTime = 0;
					changeState(BO_ATTACK);
				}
			}
			break;
		}
		break;
	case BA_RUSH:
		break;
	}

	Rect nowRect = m_MainSprite->getTextureRect();
	Rect targetRect = SpriteFrameCache::getInstance()->getSpriteFrameByName("player_attack2.png")->getRect();
	if (nowRect.origin.x == targetRect.origin.x &&nowRect.origin.y == targetRect.origin.y&& !m_IsAttackEnd)
	{
		m_AttackNum++;

		Point pos = this->getPosition();

		pos.y += 3;
		if (m_IsRightDirection)
		{
			pos.x += 70;
		}
		else
		{
			pos.x -= 70;
		}

		auto object = (NewLinearMissile*)GET_STAGE_MANAGER()->addObject(OT_NEW_LINEAR_MISSILE, pos);

		if (m_IsRightDirection)
		{
			object->setAttribute(false, 300, 0, 11);
		}
		else
		{
			object->setAttribute(false, -300, 0, 11);
		}

		m_IsAttackEnd = true;
	}
}

void Boss::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	switch (enemy->getType())
	{
	case OT_FLOOR:
		if (!m_IsGotoBottom)
		{
			if (dir & DIR_DOWN)
			{
				m_IsFlying = false;
				m_Velocity.y = 0;
				if (m_State == BO_JUMP)
				{
					changeState(BO_STAND);
				}
			}
		}
		break;
	case OT_BLOCK:
		if (dir & DIR_DOWN)
		{
			m_IsFlying = false;
			m_Velocity.y = 0;
			if (m_State == BO_JUMP)
			{
				changeState(BO_STAND);
			}
		}
		if (dir&DIR_LEFT || dir&DIR_RIGHT)
		{
			m_Velocity.x = 0;
		}
		if (dir&DIR_UP)
		{
			m_Velocity.y = 0;
		}
		break;
	case OT_LINEAR_MISSILE:
	case OT_MELEE_MISSILE:
	case OT_NEW_LINEAR_MISSILE:
		GET_STAGE_MANAGER()->setLastMonster(this);
		auto bullet = (MeleeMissile*)enemy;

		m_Info.hp -= bullet->getDamage();

		if (m_Info.hp <= 0 && !m_IsDestroyed)
		{
			GET_STAGE_MANAGER()->rebirth();
		}
		break;
	}
}

cocos2d::Rect Boss::getRect()
{
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	Point pos = this->getPosition();
	Point Anchor = this->getAnchorPoint();

	return Rect(pos.x - Anchor.x*m_Width, pos.y - Anchor.y*m_Height, m_Width, m_Height);
}
