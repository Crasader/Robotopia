#include "Player.h"
#include "GameLayer.h"
#include "AimingMissile.h"
#include "LinearMissile.h"
#include "GameManager.h"
#include "LandGateway.h"
#include "LandTrap.h"
#include "MeleeMissile.h"
#include "NewLinearMissile.h"

USING_NS_CC;

bool Player::init()
{
	if (!InteractiveObject::init())
	{
		return false;
	}

	m_Type = OT_PLAYER;
	m_Info.speed = 200;
	m_Info.attackSpeed = 0.05f;
	m_AnimationNum = PS_STATE_NUM;
	m_Animations[PS_STAND] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_STAND);
	m_Animations[PS_WALK] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_WALK);
	m_Animations[PS_JUMP] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_JUMP);
	m_Animations[PS_HIT] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_JUMP);
	m_Animations[PS_ATTACK] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_ATTACK, m_Info.attackSpeed);
	m_Animations[PS_ATTACK2] = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_ATTACK, m_Info.attackSpeed * 20);
	m_IsRightDirection = true;
	m_AttackEnd = false;
	m_IsActiveFly = false;
	m_IsOverlapable = false;
	m_IsInvincible = false;
	m_IsCrashed = false;

	m_Info.maxHp = 100;
	m_Info.hp = m_Info.maxHp;

	m_Info.maxSteam = 2000;
	m_Info.steam = m_Info.maxSteam;
	m_ActiveFlyingTime = 0;
	m_AttackNum = 0;
	m_HitTime = 0;

	m_GearWeight[1] = 0.8;
	m_GearWeight[2] = 1;
	m_GearWeight[3] = 1.2;

	m_MainSprite = Sprite::create();

	changeState(PS_STAND);

	this->addChild(m_MainSprite);

	return true;
}

void Player::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	switch (enemy->getType())
	{
	case OT_FLOOR:
		if (m_IsCrashed == true)
		{
			break;
		}
		if (dir & DIR_DOWN)
		{
			if (m_State == PS_JUMP)
			{
				GET_EFFECT_MANAGER()->createEffect(ET_PLAYER_LANDING, this->getRect(), DIR_DOWN, 1);
			}
			if (m_State == PS_HIT)
			{
				GET_EFFECT_MANAGER()->createEffect(ET_PLAYER_LANDING, this->getRect(), DIR_DOWN, 1);
				changeState(PS_STAND);
				startInvincible();
			}
			m_IsFlying = false;
			m_Velocity.y = 0;
		}
		break;
	case OT_BLOCK:
		if (m_IsCrashed == true)
		{
			break;
		}
		if (dir & DIR_DOWN)
		{
			if (m_State == PS_JUMP)
			{
				GET_EFFECT_MANAGER()->createEffect(ET_PLAYER_LANDING, this->getRect(), DIR_DOWN, 1);
			}
			if (m_State == PS_HIT)
			{
				GET_EFFECT_MANAGER()->createEffect(ET_PLAYER_LANDING, this->getRect(), DIR_DOWN, 1);
				changeState(PS_STAND);
				startInvincible();
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
	case OT_RUSH_MONSTER:
		if (m_State != PS_HIT && !m_IsInvincible)
		{
			m_IsCrashed = true;
			this->setHp(-5, true);
			changeState(PS_HIT);
			if (m_Velocity.x > 0)
			{
				m_IsRightDirection = true;
				m_MainSprite->setFlippedX(false);
				m_Velocity.x = -300/m_GearWeight[m_Info.gear];
			}
			else
			{
				m_IsRightDirection = false;
				m_MainSprite->setFlippedX(true);
				m_Velocity.x = 300 / m_GearWeight[m_Info.gear];
			}
			m_Velocity.y = 200;
			GET_EFFECT_MANAGER()->createSound(SO_PLAYER_AND_MONSTER_COLLISION, false);
		}
		break;
	case OT_AIMING_MISSILE:
		if (!((AimingMissile*)enemy)->IsPlayerMissile())
		{
			if (m_State != PS_HIT && !m_IsInvincible)
			{
				m_IsCrashed = true;
				this->setHp(-((AimingMissile*)enemy)->getDamage(), true);
				changeState(PS_HIT);
				if (m_Velocity.x > 0)
				{
					m_IsRightDirection = true;
					m_MainSprite->setFlippedX(false);
					m_Velocity.x = -300 / m_GearWeight[m_Info.gear];
				}
				else
				{
					m_IsRightDirection = false;
					m_MainSprite->setFlippedX(true);
					m_Velocity.x = 300 / m_GearWeight[m_Info.gear];
				}
				m_Velocity.y = 200 / m_GearWeight[m_Info.gear];
			}
		}
		break;
	case OT_TRAP:
		if (((LandTrap*)enemy)->isActive())
		{
			if (m_State != PS_HIT && !m_IsInvincible)
			{
				m_IsCrashed = true;
				this->setHp(-5 / m_GearWeight[m_Info.gear], true);
				changeState(PS_HIT);
				if (m_Velocity.x > 0)
				{
					m_IsRightDirection = true;
					m_MainSprite->setFlippedX(false);
					m_Velocity.x = -300 / m_GearWeight[m_Info.gear];
				}
				else
				{
					m_IsRightDirection = false;
					m_MainSprite->setFlippedX(true);
					m_Velocity.x = 300 / m_GearWeight[m_Info.gear];
				}
				m_Velocity.y = 200 / m_GearWeight[m_Info.gear];
			}
		}
	}
}

void Player::update(float dTime)
{
	Point pos = this->getPosition();

	//좌표 변경 처리
	pos.x += m_Velocity.x*dTime;
	pos.y += m_Velocity.y*dTime;

	this->setPosition(pos);

	if (m_Info.hp <= 0 || m_Info.steam <= 0)
	{
		Director::getInstance()->end();
	}
	
	//키 입력이 따른 상태 처리
	if (m_State != PS_HIT)
	{
		act(dTime);
	}

	//매 프레임마다 초기화되어야하는 정보들 초기화시킴
	reset(dTime);
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

	if (state == PS_ATTACK || state==PS_ATTACK2)
	{
		m_AttackEnd = false;
	}

	if (state == PS_HIT)
	{
		m_HitTime = 0;
		GET_EFFECT_MANAGER()->createEffect(ET_SWEAT, this->getRect(), DIR_NONE, 2);
		auto blink = Blink::create(1, 5);
		this->runAction(RepeatForever::create(blink));
	}

	auto animate = Animate::create(m_Animations[state]);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Player::endAnimation, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);
	auto finalAction = RepeatForever::create(sequence);

	m_MainSprite->runAction(finalAction);
}

void Player::endAnimation(cocos2d::Ref* sender)
{
	if (m_State == PS_ATTACK || m_State == PS_ATTACK2)
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

void Player::act(float dTime)
{
	if (m_State == PS_STAND)
	{
		if (GET_INPUT_MANAGER()->getKeyState(KC_GEAR1) == KS_PRESS)
		{
			setGear(1);
			m_Animations[PS_ATTACK]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear]);
			m_Animations[PS_ATTACK2]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear] * 20);
		}
		if (GET_INPUT_MANAGER()->getKeyState(KC_GEAR2) == KS_PRESS)
		{
			setGear(2);
			m_Animations[PS_ATTACK]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear]);
			m_Animations[PS_ATTACK2]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear] * 20);
		}
		if (GET_INPUT_MANAGER()->getKeyState(KC_GEAR3) == KS_PRESS)
		{
			setGear(3);
			m_Animations[PS_ATTACK]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear]);
			m_Animations[PS_ATTACK2]->setDelayPerUnit(m_Info.attackSpeed*m_GearWeight[m_Info.gear] * 20);
		}
		if (GET_INPUT_MANAGER()->getKeyState(KC_SET_TRANSMITTER) == KS_PRESS)
		{
			GET_STAGE_MANAGER()->setTrasmitterStageNum();
		}
	}

	if (m_State != PS_ATTACK2)
	{
		KeyState leftState = GET_INPUT_MANAGER()->getKeyState(KC_LEFT);
		KeyState rightState = GET_INPUT_MANAGER()->getKeyState(KC_RIGHT);


		if (leftState == KS_HOLD)
		{
			m_Velocity.x = -m_Info.speed * m_GearWeight[m_Info.gear];
			m_IsRightDirection = false;
			m_MainSprite->setFlippedX(true);

		}
		else if (rightState == KS_HOLD)
		{
			m_Velocity.x = m_Info.speed* m_GearWeight[m_Info.gear];
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

			if (m_Velocity.y <= -300 * m_GearWeight[m_Info.gear])
			{
				m_Velocity.y = -300 * m_GearWeight[m_Info.gear];
			}

			if (m_Velocity.y <= 300 * m_GearWeight[m_Info.gear])
			{
				m_Velocity.y += 1500 * m_GearWeight[m_Info.gear] * dTime;
			}

			int x = rand() % (int)(m_Width / 1.5);
			Point pos = Point(this->getPosition().x + x - m_Width / 2, this->getPosition().y - m_Height / 2);

			GET_EFFECT_MANAGER()->createEffectSelectedSizeByUser(ET_ROUND_SMOKE, Rect(pos.x, pos.y, -1, -1), 1);
		}

		if (m_State != KC_ATTACK2)
		{
			if (GET_INPUT_MANAGER()->getKeyState(KC_ATTACK) == KS_HOLD)
			{
				changeState(PS_ATTACK);
			}
		}

		if (m_State == PS_WALK || m_State == PS_STAND)
		{
			if (GET_INPUT_MANAGER()->getKeyState(KC_ATTACK2) == KS_HOLD)
			{
				changeState(PS_ATTACK2);
				m_Velocity.x = 0;
				m_Info.steam -= 2500 * m_GearWeight[m_Info.gear];
			}
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
			if (m_State != PS_ATTACK && m_State != PS_ATTACK2)
			{
				if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_HOLD)
				{
					GET_EFFECT_MANAGER()->createSound(SO_JUMP, false);
					m_Velocity.y = 600 * m_GearWeight[m_Info.gear];
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
	}

	Rect nowRect = m_MainSprite->getTextureRect();
	Rect targetRect = SpriteFrameCache::getInstance()->getSpriteFrameByName("player_attack2.png")->getRect();
	if (nowRect.origin.x == targetRect.origin.x &&nowRect.origin.y == targetRect.origin.y&& !m_AttackEnd)
	{
		m_AttackNum++;
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

		if (m_State == PS_ATTACK)
		{
			auto object = (MeleeMissile*)gameLayer->addObject(OT_MELEE_MISSILE, pos);


			if (m_IsRightDirection)
			{
				object->setAttribute(true, 1, 0, 3 * m_GearWeight[m_Info.gear]);
			}
			else
			{
				object->setAttribute(true, -1, 0, 3 * m_GearWeight[m_Info.gear]);
			}
			m_Info.steam -= 150;
		}
		else if(m_State == PS_ATTACK2)
		{
			auto object = (NewLinearMissile*)gameLayer->addObject(OT_NEW_LINEAR_MISSILE, pos);


			if (m_IsRightDirection)
			{
				object->setAttribute(true, 200, 0, 8 * m_GearWeight[m_Info.gear]);
			}
			else
			{
				object->setAttribute(true, -200, 0, 8 * m_GearWeight[m_Info.gear]);
			}
		}

		m_AttackEnd = true;
	}
}

void Player::reset(float dTime)
{

	if (m_Velocity.y < -500)
	{
		m_Velocity.y = -500;
	}

	m_IsFlying = true;

	if (m_IsActiveFly)
	{
		m_ActiveFlyingTime += dTime;
		m_Info.steam -= dTime * 800 * m_GearWeight[m_Info.gear];
	}

	if (m_ActiveFlyingTime >= 1)
	{
		GET_EFFECT_MANAGER()->createSound(SO_PLAYER_FLYING, false);
		m_ActiveFlyingTime = 0;
	}

	if (m_State == PS_HIT)
	{
		m_HitTime += dTime;
		if (m_HitTime > 1)
		{
			changeState(PS_STAND);
			startInvincible();
		}
	}


	m_IsActiveFly = false;
	m_IsCrashed = false;
	m_Velocity.y -= GRAVITY*dTime;
}

void Player::startInvincible()
{
	m_IsInvincible = true;

	auto delay = DelayTime::create(1);
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Player::endInvincible, this));
	auto sequence = Sequence::create(delay, callfunc, NULL);

	this->runAction(sequence);
}

void Player::endInvincible(cocos2d::Ref* sender)
{
	m_IsInvincible = false;
	this->stopAllActions();
	this->setVisible(true);
}

void Player::setHp(int hp, bool isRelative /*= false*/)
{
	int changeHp = hp;

	if (isRelative)
	{
		changeHp += m_Info.hp / m_GearWeight[m_Info.gear];
	}
	if (changeHp > m_Info.maxHp)
	{
		changeHp = m_Info.maxHp;
	}
	m_Info.hp = changeHp;
}

void Player::setSteam(int steam, bool isRelative /*= false*/)
{
	int changeSteam = steam;

	if (isRelative)
	{
		changeSteam += m_Info.steam / m_GearWeight[m_Info.gear];
	}
	if (changeSteam > m_Info.maxSteam)
	{
		changeSteam = m_Info.maxSteam;
	}

	m_Info.steam = changeSteam;
}

