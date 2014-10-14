//Gear.h
//
//Gear UI 备己
//
//累己磊 : 快犁快
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

class Gear : public cocos2d::Node
{
public:
	virtual bool		init();
	void				update(float dTime);

	CREATE_FUNC(Gear);

private:
	PlayerInfo			m_PlayerInfo;
	cocos2d::Sprite*	m_Gear1;
	cocos2d::Sprite*	m_Gear2;
	cocos2d::Sprite*	m_Gear3;
};