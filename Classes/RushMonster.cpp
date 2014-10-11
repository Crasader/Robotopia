﻿#include "RushMonster.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "AimingMissile.h"
#include "MeleeMissile.h"

USING_NS_CC;

bool RushMonster::init()
{
	if (!Monster::init())
	{
		return false;
	}

	m_Type = OT_RUSH_MONSTER;

	m_Animations[RM_STAND] = GET_RESOURCE_MANAGER()->createAnimation(AT_RUSHMONSTER_STAND);
	m_Animations[RM_MOVE] = GET_RESOURCE_MANAGER()->createAnimation(AT_RUSHMONSTER_MOVE);
	m_Animations[RM_RUSH] = GET_RESOURCE_MANAGER()->createAnimation(AT_RUSHMONSTER_RUSH);
	

	m_MainSprite = Sprite::create();
	m_MainSprite->setScale(2);

	this->addChild(m_MainSprite);

	changeState(RM_STAND);

	m_DelayTime = rand() % 3 + 4;
	m_MoveSpeed = 30;
	m_IsOnGravity = true;

	m_Info.maxHp = 100;
	m_Info.hp = m_Info.maxHp;

	this->scheduleUpdate();

	return true;
}

void RushMonster::collisionOccured(InteractiveObject* enemy, Directions dir)
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
		break;
	case OT_MELEE_MISSILE:
		auto bullet = (MeleeMissile*)enemy;

		m_Info.hp -= bullet->getDamage();

		if (m_Info.hp <= 0)
		{
			m_IsDestroyed = true;
		}
		break;
	}
}

void RushMonster::changeState(State state)
{
	//이미 해당 상태인 경우 아무 처리도 하지 않는다.
	if (m_State == state)
	{
		return;
	}
	m_State = state;
	m_MainSprite->stopAllActions();

	auto animate = Animate::create(m_Animations[state]);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(RushMonster::endAnimation, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_MainSprite->runAction(RepeatForever::create(sequence));
}

void RushMonster::endAnimation(cocos2d::Ref* sender)
{
}

void RushMonster::update(float dTime)
{

	Point pos = this->getPosition();
	Rect rect = this->getRect();

	if (m_Velocity.x > 0)
		rect.origin.x += rect.size.width / 2;
	else
		rect.origin.x -= rect.size.width / 2;

	rect.origin.y -= rect.size.height/2;
	

	for (auto& obj : GET_STAGE_MANAGER()->getObjectsByPosition(rect.origin))
	{
		if (obj->getType() == OT_BLOCK)
		{
			pos.x += m_Velocity.x*dTime;
			break;
		}
	}
	
	pos.y += m_Velocity.y*dTime;
	this->setPosition(pos);


	if (isSeePlayer())
	{
		changeState(RM_RUSH);
	}
	else if(m_State == RM_RUSH)
	{
		m_Velocity.x = 0;
		changeState(RM_STAND);
	}
	
	if (m_State == RM_RUSH)
	{
		auto gameLayer = (GameLayer*)this->getParent();
		auto playerX = gameLayer->getPlayer()->getPosition().x;

		if (playerX < this->getPosition().x)
		{
			m_IsRightDirection = false;
		}
		else
		{
			m_IsRightDirection = true;
		}

		m_MainSprite->setFlippedX(m_IsRightDirection);
		m_Velocity.x = m_MoveSpeed * 4 ;
		if (!m_IsRightDirection)
		{
			m_Velocity.x = -m_Velocity.x;
		}
	}
	else 
	{
		m_DelayTime -= dTime;

		if (m_DelayTime < 0)
		{
			if (m_State == RM_STAND)
			{
				m_IsRightDirection = rand() % 2;
				m_MainSprite->setFlippedX(m_IsRightDirection);
				m_DelayTime = 2;
				m_Velocity.x = m_MoveSpeed;

				if (!m_IsRightDirection)
				{
					m_Velocity.x = -m_Velocity.x;
				}

				changeState(RM_MOVE);
			}
			else if (m_State == RM_MOVE)
			{
				m_DelayTime = 4 + rand() % 3;
				changeState(RM_STAND);
				m_Velocity.x = 0;
			}
		}
	}

	m_Velocity.y -= GRAVITY*dTime;
	m_IsFlying = true;
}

cocos2d::Rect RushMonster::getRect()
{
	m_Width = m_MainSprite->getContentSize().width * 2;
	m_Height = m_MainSprite->getContentSize().height * 2;

	Point pos = this->getPosition();
	Point Anchor = this->getAnchorPoint();

	return Rect(pos.x - Anchor.x*m_Width, pos.y - Anchor.y*m_Height, m_Width, m_Height);
}

bool RushMonster::isSeePlayer()
{
	Rect vision = this->getRect();

	vision.origin.x -= 100;
	vision.origin.y += 20;
	vision.size.width += 300;
	vision.size.height += 50;

	auto objList = ((GameLayer*)this->getParent())->getObjectsByRect(vision);
	auto player = ((GameLayer*)this->getParent())->getPlayer();

	if (std::find(objList.begin(), objList.end(), player) == objList.end())
	{
		return false;
	}

	for (auto object : objList)
	{
		if (object->getType() == OT_BLOCK)
		{
			auto playerX = player->getPositionX();
			auto objectX = object->getPositionX();
			auto myX = this->getPositionX();
			if (( playerX - objectX) *(myX - objectX) <= 0)
			{
				return false;
			}
		}
	}

	return true;
}
