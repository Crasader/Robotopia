
#include "GameManager.h"
#include "MeleeMissile.h"

USING_NS_CC;

bool MeleeMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}


	m_Type = OT_MELEE_MISSILE;

	m_MainSprite = Sprite::create();
	//�̺κп� ���� ���� �ʿ�
	//m_MainSprite->setZOrder(-100);
	m_Animations[0] = GET_RESOURCE_MANAGER()->createAnimation(AT_MELEE_MISSILE_FLYING, 0.02f);
	int aniPlayNum = 1;


	auto action = Repeat::create(Animate::create(m_Animations[0]), aniPlayNum);
	auto callback = CallFunc::create(CC_CALLBACK_0(MeleeMissile::isDestroyedToTureAfterAni, this));
	m_MainSprite->runAction(Sequence::create(action, callback, NULL));
	

	this->addChild(m_MainSprite);
	this->scheduleUpdate();
	return true;
}

void MeleeMissile::update(float dTime)
{
	return;
}

void MeleeMissile::isDestroyedToTureAfterAni()
{
	m_IsDestroyed = true;
}

void MeleeMissile::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	m_IsPlayerMissile = IsPlayerMissile();


	//�÷��̾� �̻��ϰ� ���� �̻����� ������� ������� �κ�
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


	//�÷��̾� �̻����̵� ���� �̻����̵� �������� �浹���� �� ������� �κ�
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
		
		GET_EFFECT_MANAGER()->createEffect(ET_MELEE_MISIILE_COLLSION, this->getRect(), dir, 1);
	}
	return;
}

//�ӵ��� �����δ� 0������ ������ ���� ������ velocity�� + �� �־��ּ���
void MeleeMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree)
{
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}
}

