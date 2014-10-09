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
	void removeSprAfterAni(cocos2d::Ref* sender);

	//매개변수 설명, 
	// 1. 사용하고 싶은 effect 이름,
	// 2. 부딪힌 대상이 되는 오브젝트의 Rect(point와 size로 넣을수도 있음)
	// 3. 부딪힌 방향
	// 4. effectPlayNum  
	
	void createEffect(EffectType selectedEffect, cocos2d::Rect enemyRect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffect(EffectType selectedEffect, cocos2d::Point enemyPoint, cocos2d::Size enemySize, 
					  cocos2d::Point ownPoint, cocos2d::Size ownSize, Directions collisionDir, int effectPlayNum);

	//매개변수 설명, 
	// 1. 사용하고 싶은 effect 이름, 
	// 2. 이펙트가 나타나길 원하는 위치와 원하는 크기를 담은 Rect(크기의 경우 -1,-1값을 넣으면 디폴트로 생성)
	// 3. effectPlayNum
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum);
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, cocos2d::Size effectSize, int effectPlayNum);

private:
	void createEffectLinearMissileCollision(cocos2d::Rect enemyRect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	cocos2d::Sprite*	effectSpr;
	cocos2d::Animation* m_MainAnimation;
};

