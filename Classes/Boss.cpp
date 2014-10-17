#include "Boss.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "AimingMissile.h"
#include "MeleeMissile.h"

USING_NS_CC;

bool Boss::init()
{
	if (!Monster::init())
	{
		return false;
	}

	m_Type = OT_BOSS;

	m_Animations[BO_STAND] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_STAND);


	m_MainSprite = Sprite::create("");

	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	m_MainSprite->setScale(2);

	this->addChild(m_MainSprite);

	changeState(BO_STAND);

	m_MoveSpeed = 30;
	m_IsOnGravity = true;

	m_Info.maxHp = 2200;
	m_Info.hp = m_Info.maxHp;

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

}

void Boss::update(float dTime)
{

}

void Boss::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	switch (enemy->getType())
	{
	case OT_FLOOR:
		if (dir & DIR_DOWN)
		{
			m_IsFlying = false;
			m_Velocity.y = 0;
		}
		break;
	case OT_BLOCK:
		if (dir & DIR_DOWN)
		{
			m_IsFlying = false;
			m_Velocity.y = 0;
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
			GET_STAGE_MANAGER()->addObject(OT_STEAM_PACK, this->getPosition());
			m_IsDestroyed = true;
		}
		break;
	}
}
