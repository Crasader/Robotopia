
#include "MeleeMissile.h"

USING_NS_CC;

bool MeleeMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	//m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_MELLEMISSILE_FLYING);

	//m_Type = OT_MELEE_MISSILE;

	//m_MainSprite = Sprite::create();
	//m_Animations[0] = GET_RESOURCE_MANAGER()->createAnimation(AT_MELEEMISSILE_FLYING, 0.05f);
	//int aniPlayNum = 2;


	//auto action = Repeat::create(Animate::create(m_AniMation[0]), aniPlayNum);
	//auto callback = CallFunc::create(CC_CALLBACK_0(MeleeMissile::isDestroyedToTureAfterAni, this));
	//m_MainSprite->runAction(Sequence::create(action, callback, NULL));
	

	//m_MainSprite->setZOrder(-100);
	this->addChild(m_MainSprite);
	return true;
}

void MeleeMissile::update(float dTime)
{

}

void MeleeMissile::isDestroyedToTureAfterAni()
{
	m_IsDestroyed = true;
}

