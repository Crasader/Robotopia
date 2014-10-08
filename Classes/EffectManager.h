//EffectManager.h
//  
//��� ����Ʈ���� �ִϸ��̼��� ���� 
//��� �ñ�� �ҷ����� �ʿ��� �˾Ƽ� ����� ��
//������ ���ؼ� �����غ� ������ ������
//�ۼ��� : �輺��

#pragma once

#include "cocos2d.h"
#include "Utils.h"

class EffectManager : cocos2d::Node
{
public:
	
	virtual bool init();

	void		 useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum);
	CREATE_FUNC(EffectManager);


private:
	void									    useETLMC(cocos2d::Rect obRect, int effectPlayNum);
	cocos2d::Sprite*							m_ETMainSprite;
	std::map < EffectType, cocos2d::Animation*>	m_ETAnimations;
};