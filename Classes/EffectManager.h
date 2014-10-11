//EffectManager.h
// 
//
//��� �ñ�� �ҷ����� �ʿ��� �˾Ƽ� ����� ��
//createEffect�� ���ؼ� ���ϴ� ����Ʈ ��밡�� 
//
//�ۼ��� : �輺��

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

	//�Ű����� ����, 
	// 1. ����ϰ� ���� effect �̸�,
	// 2. �ڱ� �ڽ��� Rect(point�� size�� �������� ����)
	// 3. �ε��� ����(������ DIR_NONE)
	// 4. effectPlayNum  
	
	void createEffect(EffectType selectedEffect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffect(EffectType selectedEffect, cocos2d::Point ownPoint, cocos2d::Size ownSize, Directions collisionDir, int effectPlayNum);

	//�Ű����� ����, 
	// 1. ����ϰ� ���� effect �̸�, 
	// 2. ����Ʈ�� ��Ÿ���� ���ϴ� ��ġ�� ���ϴ� ũ�⸦ ���� Rect
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


	//////////////////�浹 ���� �ֵ�
	void createEffectRoundSmokeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	bool m_IsOnBGM;
};

