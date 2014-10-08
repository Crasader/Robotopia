//EffectManager.h
// 
//
//사용 시기는 불러오는 쪽에서 알아서 맞춰야 됨
//구조에 대해서 생각해볼 여지가 많은듯
//작성자 : 김성연

#pragma once

#include "cocos2d.h"
#include "Utils.h"

class EffectManager
{
public:
	bool init();

	void useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	//void useEffect(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, cocos2d::Point AnchorPoint);

private:
	void useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	cocos2d::Sprite*	m_MainSprite;
	cocos2d::Animation* m_MainAnimation;
};

