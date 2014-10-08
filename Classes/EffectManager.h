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

	void useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	//void useEffect(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, cocos2d::Point AnchorPoint);

private:
	void useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	cocos2d::Sprite*	m_MainSprite;
	cocos2d::Animation* m_MainAnimation;
};

