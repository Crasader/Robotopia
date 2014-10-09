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

	//매개변수 설명, 1. 사용하고 싶은 effect 이름, 2. 대상이 되는 오브젝트의 Rect(point와 size로 넣을수도 있음), 
	//			   3.effectPlayNum  4.대상이 되는 오브젝트에 어느쪽에 효과가 나타날것인지에 대한 앵커포인트 (0~1) (-1,-1)을 넣으면 디폴트 위치에 효과가 생성됨
	void useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, cocos2d::Point AnchorPoint);

	//매개변수 설명, 1. 사용하고 싶은 effect 이름, 2. 이펙트가 나타나길 원하는 위치와 원하는 크기를 담은 Rect(크기의 경우 -1,-1값을 넣으면 디폴트로 생성)
	//			   3. effectPlayNum
	void useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum);
	void useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, cocos2d::Size effectSize, int effectPlayNum);

private:
	void useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	cocos2d::Sprite*	m_MainSprite;
	cocos2d::Animation* m_MainAnimation;
};

