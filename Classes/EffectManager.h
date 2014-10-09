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

	//�Ű����� ����, 1. ����ϰ� ���� effect �̸�, 2. ����� �Ǵ� ������Ʈ�� Rect(point�� size�� �������� ����), 
	//			   3.effectPlayNum  4.����� �Ǵ� ������Ʈ�� ����ʿ� ȿ���� ��Ÿ���������� ���� ��Ŀ����Ʈ (0~1) (-1,-1)�� ������ ����Ʈ ��ġ�� ȿ���� ������
	void useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, cocos2d::Point AnchorPoint);

	//�Ű����� ����, 1. ����ϰ� ���� effect �̸�, 2. ����Ʈ�� ��Ÿ���� ���ϴ� ��ġ�� ���ϴ� ũ�⸦ ���� Rect(ũ���� ��� -1,-1���� ������ ����Ʈ�� ����)
	//			   3. effectPlayNum
	void useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum);
	void useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, cocos2d::Size effectSize, int effectPlayNum);

private:
	void useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, cocos2d::Point AnchorPoint);
	void useEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum);

	cocos2d::Sprite*	m_MainSprite;
	cocos2d::Animation* m_MainAnimation;
};

