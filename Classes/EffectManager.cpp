#include "EffectManager.h"
#include "GameManager.h"
USING_NS_CC;


//bool EffectManager::init()
//{	
//	if (!Node::init())
//	{
//		return false;
//	}
//	m_ETMainSprite = Sprite::create();
//
//	m_ETAnimations[ET_LINEAR_MISSILE_COLLISION] = UtilFunctions::createAnimation("ETLinearMissileCollision", 1, 9, 0.01f);
//	
//	return true;
//}
//
//void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum)
//{
//	switch (selectedEffect)
//	{
//	case ET_LINEAR_MISSILE_COLLISION:
//		useETLMC(obRect, effectPlayNum);
//		break;
//	case ET_AIMING_MISSILE_COLLISION:
//		break;
//	case ET_PLAYER_FLOOR_COLLISION:
//		break;
//	default:
//		break;
//	}
//	
//}
//
//void EffectManager::useETLMC(cocos2d::Rect obRect, int effectPlayNum)
//{
//	float needEffectScale = 0.5;
//
//	//이게 좀 앞에서 Rect값을 이용해서 터지면 좋겠다. 
//	float ratioX = obRect.size.width / m_ETMainSprite->getContentSize().width;
//	float ratioY = obRect.size.height / m_ETMainSprite->getContentSize().height;
//
//	
//	auto animation = m_ETAnimations[ET_LINEAR_MISSILE_COLLISION];
//	
//	m_ETMainSprite->runAction(Repeat::create(Animate::create(m_ETAnimations[ET_LINEAR_MISSILE_COLLISION]),effectPlayNum));
//	this->addChild(m_ETMainSprite);
//	return;
//}


bool EffectManager::init()
{
	m_MainSprite = Sprite::create();
	return true;
}

void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, Point AnchorPoint)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		useEffectLinearMissileCollision(obRect, effectPlayNum, AnchorPoint);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
}


void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, Point AnchorPoint)
{
	Rect obRect(obPoint.x, obPoint.y, obSize.width, obSize.height);
	useEffect(selectedEffect, obRect, effectPlayNum, AnchorPoint);
	return;
}

void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum, cocos2d::Point AnchorPoint)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		//useEffectLinearMissileCollision(obRect, effectPlayNum, AnchorPoint);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
	return;
}

void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, 
												cocos2d::Size effectSize, int effectPlayNum, cocos2d::Point AnchorPoint)
{
	Rect effectRect(effectPoint.x, effectPoint.y, effectSize.width, effectSize.height);
	useEffectSelectedSizeByUser(selectedEffect, effectRect, effectPlayNum, AnchorPoint);
	return;
}


void EffectManager::useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, Point AnchorPoint)
{
	float needEffectScale = 0.5;

	//현욱이가 만들어 주면 여기 해제
	m_MainSprite = GET_RESOURCE_MANAGER()->createAnimation("ETLinearMissileCollision1.png");
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation("ETLinearMissileCollision%d.png", 1, 9, 0.1f);

	//이게 좀 앞에서 Rect값을 이용해서 터지면 좋겠다. 
	float ratioX = obRect.size.width / m_MainSprite->getContentSize().width;
	float ratioY = obRect.size.height / m_MainSprite->getContentSize().height;
	
	m_MainSprite->setScaleX(ratioX * needEffectScale);
	m_MainSprite->setScaleY(ratioY * needEffectScale);

	m_MainSprite->runAction(Repeat::create(Animate::create(m_MainAnimation), effectPlayNum));

	return;
}


