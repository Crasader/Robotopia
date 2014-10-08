#include "EffectManager.h"

USING_NS_CC;

bool EffectManager::init()
{	
	if (!Node::init())
	{
		return false;
	}
	m_ETMainSprite = Sprite::create();

	m_ETAnimations[ET_LINEAR_MISSILE_COLLISION] = UtilFunctions::createAnimation("ETLinearMissileCollision", 1, 9, 0.01f);
	
	return true;
}

void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		useETLMC(obRect, effectPlayNum);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;
	default:
		break;
	}
	
}

void EffectManager::useETLMC(cocos2d::Rect obRect, int effectPlayNum)
{
	float needEffectScale = 0.5;

	//이게 좀 앞에서 Rect값을 이용해서 터지면 좋겠다. 
	float ratioX = obRect.size.width / m_ETMainSprite->getContentSize().width;
	float ratioY = obRect.size.height / m_ETMainSprite->getContentSize().height;

	
	auto animation = m_ETAnimations[ET_LINEAR_MISSILE_COLLISION];
	
	m_ETMainSprite->runAction(Repeat::create(Animate::create(m_ETAnimations[ET_LINEAR_MISSILE_COLLISION]),effectPlayNum));
	this->addChild(m_ETMainSprite);
	return;
}

