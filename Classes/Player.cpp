#include "Player.h"
#include "GameLayer.h"
#include "AimingMissile.h"
#include "LinearMissile.h"
#include "GameManager.h"
#include "LandGateway.h"
#include "MeleeMissile.h"

USING_NS_CC;

bool Player::init()
{
	if (!InteractiveObject::init())
	{
		return false;
	}

	m_Type = OT_PLAYER;
	m_MoveSpeed = 200;
	m_AnimationNum = PS_STATE_NUM;
	m_Animations[PS_STAND] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_STAND);
	m_Animations[PS_WALK] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_WALK);
	m_Animations[PS_JUMP] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_JUMP);
	m_Animations[PS_ATTACK] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_ATTACK,0.3f);
	m_IsRightDirection = true;
	m_AttackEnd = false;
	m_IsActiveFly = false;

	m_MaxHp = 100;
	m_Hp = m_MaxHp;

	m_MaxSteam = 20;
	m_Steam = m_MaxSteam;
	m_ActiveFlyingTime = 0;

	m_MainSprite = Sprite::create();

	changeState(PS_STAND);

	this->addChild(m_MainSprite);
	this->scheduleUpdate();

	return true;
}

void Player::collisionOccured(InteractiveObject* enemy, Directions dir)
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
			if (m_State == PS_JUMP)
			{
				GET_EFFECT_MANAGER()->createEffect(ET_PLAYER_LANDING, this->getRect(), DIR_DOWN, 1);
			}
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
	case OT_GATEWAY:
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
	}
}

void Player::update(float dTime)
{
	Point pos = this->getPosition();

	//좌표 변경 처리
	pos.x += m_Velocity.x*dTime;
	pos.y += m_Velocity.y*dTime;
	
	//키, 상태 처리
	KeyState leftState = GET_INPUT_MANAGER()->getKeyState(KC_LEFT);
	KeyState rightState = GET_INPUT_MANAGER()->getKeyState(KC_RIGHT);


	if (leftState == KS_HOLD)
	{
		m_Velocity.x = -m_MoveSpeed;
		m_IsRightDirection = false;
		m_MainSprite->setFlippedX(true);

	}
	else if (rightState == KS_HOLD)
	{
		m_Velocity.x = m_MoveSpeed;
		m_IsRightDirection = true;
		m_MainSprite->setFlippedX(false);
	}
	else
	{
		m_Velocity.x = 0;
	}

	if (GET_INPUT_MANAGER()->getKeyState(KC_FLY) == KS_HOLD)
	{
		m_IsActiveFly = true;

		if (m_Velocity.y <= -300)
		{
			m_Velocity.y = -300;
		}

		if (m_Velocity.y <= 300)
		{
			m_Velocity.y += 1500 * dTime;
		}

		int x = rand() % (int)(m_Width / 1.5);
		Point pos = Point(this->getPosition().x + x - m_Width/2, this->getPosition().y - m_Height / 2);

		GET_EFFECT_MANAGER()->createEffectSelectedSizeByUser(ET_ROUND_SMOKE, Rect(pos.x, pos.y, -1, -1), 1);
	}

	if (GET_INPUT_MANAGER()->getKeyState(KC_ATTACK) == KS_HOLD)
	{
		changeState(PS_ATTACK);
	}

	if (m_IsFlying)
	{ 
		if (m_State != PS_ATTACK)
		{
			changeState(PS_JUMP);
		}
	}
	else
	{
		if (GET_INPUT_MANAGER()->getKeyState(KC_ATTACK) && (m_State == PS_STAND || m_State == PS_WALK))
		{
			changeState(PS_ATTACK);
		}

		if (m_State != PS_ATTACK)
		{
			if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP))
			{
				m_Velocity.y = 600;
			}
			else if (leftState == KS_HOLD)
			{
				changeState(PS_WALK);

			}
			else if (rightState == KS_HOLD)
			{
				changeState(PS_WALK);
			}
			else
			{
				changeState(PS_STAND);
			}
		}
	}

	Rect nowRect = m_MainSprite->getTextureRect();
	Rect targetRect = SpriteFrameCache::getInstance()->getSpriteFrameByName("player_attack2.png")->getRect();
	if (nowRect.origin.x == targetRect.origin.x &&nowRect.origin.y == targetRect.origin.y&& !m_AttackEnd)
	{
		auto gameLayer = (GameLayer*)this->getParent();

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

		auto object = (MeleeMissile*)gameLayer->addObject(OT_MELEE_MISSILE, pos);


		if (m_IsRightDirection)
		{
			object->setMoveAttribute(true, 1, 0);
		}
		else
		{
			object->setMoveAttribute(true, -1, 0);
		}

		m_AttackEnd = true;
	}

	m_IsActiveFly = false;
	m_Velocity.y -= GRAVITY*dTime;
	
	if (m_Velocity.y < -500)
	{
		m_Velocity.y = -500;
	}
	
	m_IsFlying = true;

	m_ActiveFlyingTime += dTime;

	if (m_ActiveFlyingTime >= 10)
	{
		m_ActiveFlyingTime = 0;
		m_Steam--;
	}

	this->setPosition(pos);
}

void Player::changeState(State state)
{
	//이미 해당 상태인 경우 아무 처리도 하지 않는다.
	if (m_State == state)
	{
		return;
	}
	m_State = state;
	m_MainSprite->stopAllActions();

	if (state == PS_ATTACK)
	{
		m_AttackEnd = false;
	}

	auto animate = Animate::create(m_Animations[state]);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Player::endAnimation, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);
	auto finalAction = RepeatForever::create(sequence);

	m_MainSprite->runAction(finalAction);
}

void Player::endAnimation(cocos2d::Ref* sender)
{
	if (m_State == PS_ATTACK)
	{
		changeState(PS_STAND);
	}
}

cocos2d::Rect Player::getRect()
{
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	return InteractiveObject::getRect();
}

