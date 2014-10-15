
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
	m_Damage = 2.0;

	m_MainSprite = Sprite::create();
	//�̺κп� ���� ���� �ʿ�
	//m_MainSprite->setZOrder(-100);
	m_Animations[0] = GET_RESOURCE_MANAGER()->createAnimation(AT_MELEE_MISSILE_FLYING, 0.02f);
	int aniPlayNum = 1;


	auto action = Repeat::create(Animate::create(m_Animations[0]), aniPlayNum);
	auto callback = CallFunc::create(CC_CALLBACK_0(MeleeMissile::isDestroyedToTureAfterAni, this));
	m_MainSprite->runAction(Sequence::create(action, callback, NULL));
	GET_EFFECT_MANAGER()->createSound(SO_MELEE_MISSILE, false);
	

	this->addChild(m_MainSprite);
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
	
	bool meleeEffectAdd = false;
	switch (enemy->getType())
	{
	case OT_MONSTER:
		meleeEffectAdd = true;
		break;
	case OT_RUSH_MONSTER:
		meleeEffectAdd = true;
		break;;
	case OT_BAT_MONSTER:
		meleeEffectAdd = true;
		break;
	default:
		break;
	}

	if (meleeEffectAdd)
	{
		GET_EFFECT_MANAGER()->createEffect(ET_MELEE_MISIILE_COLLSION, this->getRect(), dir, 1);
	}
	return;
}

//�ӵ��� �����δ� 0������ ������ ���� ������ velocity�� + �� �־��ּ���
void MeleeMissile::setAttribute(bool isPlayerMissile, float velocity, float degree, float setDamage)
{
	m_IsPlayerMissile = isPlayerMissile;
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}
	
	m_Damage = setDamage;
}

