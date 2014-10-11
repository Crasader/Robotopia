//EffectManager.h
// 
//
//사용 시기는 불러오는 쪽에서 알아서 맞춰야 됨
//createEffect를 통해서 원하는 이펙트 사용가능 
//
//작성자 : 김성연

#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Utils.h"

enum EffectType
{
	ET_LINEAR_MISSILE_COLLISION,
	ET_AIMING_MISSILE_COLLISION,
	ET_NEW_LINEAR_MISSILE_COLLISION,
	ET_MELEE_MISIILE_COLLSION,
	ET_PLAYER_LANDING,
	ET_ROUND_SMOKE,
};

enum SoundType
{
	SO_SCENE1_BGM,
	SO_SCENE2_BGM,
	SO_SAGA_BGM,
	SO_MELEE_MISSILE,
	SO_JUMP,
};

class EffectManager
{
public:
	bool init();
	void removeSprAfterAni(cocos2d::Ref* sender);

	//매개변수 설명, 
	// 1. 사용하고 싶은 effect 이름,
	// 2. 자기 자신의 Rect(point와 size로 넣을수도 있음)
	// 3. 부딪힌 방향(없으면 DIR_NONE)
	// 4. effectPlayNum  
	
	void createEffect(EffectType selectedEffect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffect(EffectType selectedEffect, cocos2d::Point ownPoint, cocos2d::Size ownSize, Directions collisionDir, int effectPlayNum);

	//매개변수 설명, 
	// 1. 사용하고 싶은 effect 이름, 
	// 2. 이펙트가 나타나길 원하는 위치와 원하는 크기를 담은 Rect
	// 3. effectPlayNum
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum);
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, cocos2d::Size effectSize, int effectPlayNum);

	void createSound(SoundType selectedSound, bool isRepeated);


private:
	void createEffectLinearMissileCollision(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	void createEffectAimingMissileCollision( cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectAimingMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	void createEffectPlayerLanding(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectPlayerLandingSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	void createEffectMeleeMissileCollision(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectMeleeMissileCollisionByUser(cocos2d::Rect effectRect, int effectPlayNum);

	void createEffectNewLinearMissileCollsion(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectNewLinearMissileCollsionByUser(cocos2d::Rect effectRect, int effectPlayNum);


	//////////////////충돌 없는 애들
	void createEffectRoundSmokeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	bool m_IsOnBGM;
};

