
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
	//이부분에 대한 생각 필요
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
	
	bool meleeEffectAdd = false;
	switch (enemy->getType())
	{
	case OT_MONSTER:
		meleeEffectAdd = true;
		break;
	case OT_RUSH_MONSTER:
		meleeEffectAdd = true;
		break;;
	default:
		break;
	}

	if (meleeEffectAdd)
	{
		GET_EFFECT_MANAGER()->createEffect(ET_MELEE_MISIILE_COLLSION, this->getRect(), dir, 1);
	}
	return;
}

//속도가 실제로는 0이지만 오른쪽 보고 있으면 velocity에 + 값 넣어주세요
void MeleeMissile::setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree)
{
	if (velocity < 0)
	{
		m_MainSprite->setFlippedX(true);
	}
}

