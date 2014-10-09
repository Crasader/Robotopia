//EffectManager.h
// 
//
//��� �ñ�� �ҷ����� �ʿ��� �˾Ƽ� ����� ��
//������ ���ؼ� �����غ� ������ ������
//�ۼ��� : �輺��

#pragma once

#include "cocos2d.h"
#include "Utils.h"

class EffectManager
{
public:
	bool init();
	void removeSprAfterAni(cocos2d::Ref* sender);

	//�Ű����� ����, 
	// 1. ����ϰ� ���� effect �̸�,
	// 2. �ε��� ����� �Ǵ� ������Ʈ�� Rect(point�� size�� �������� ����)
	// 3. �ε��� ����
	// 4. effectPlayNum  
	
	void createEffect(EffectType selectedEffect, cocos2d::Rect enemyRect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffect(EffectType selectedEffect, cocos2d::Point enemyPoint, cocos2d::Size enemySize, 
					  cocos2d::Point ownPoint, cocos2d::Size ownSize, Directions collisionDir, int effectPlayNum);

	//�Ű����� ����, 
	// 1. ����ϰ� ���� effect �̸�, 
	// 2. ����Ʈ�� ��Ÿ���� ���ϴ� ��ġ�� ���ϴ� ũ�⸦ ���� Rect(ũ���� ��� -1,-1���� ������ ����Ʈ�� ����)
	// 3. effectPlayNum
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum);
	void createEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, cocos2d::Size effectSize, int effectPlayNum);

private:
	void createEffectLinearMissileCollision(cocos2d::Rect enemyRect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum);
	void createEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	cocos2d::Sprite*	effectSpr;
	cocos2d::Animation* m_MainAnimation;
};

