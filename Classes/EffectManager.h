//EffectManager.h
//  
//모든 이펙트들의 애니메이션을 가짐 
//사용 시기는 불러오는 쪽에서 알아서 맞춰야 됨
//구조에 대해서 생각해볼 여지가 많은듯
//작성자 : 김성연

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