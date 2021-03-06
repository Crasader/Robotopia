//BarContainer.h
//
//HP bar, STE bar 구성 (코드 개판 5분 전)
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

class BarContainer : public cocos2d::Node
{

public:
	virtual bool						init();
	void								update(float dTime);
	
	CREATE_FUNC(BarContainer);


private:
	enum BarContainerEnum
	{
		LABEL_HPSTATUS,
		LABEL_STEAMSTATUS,
		SPRITE_FOREHP,
		SPRITE_BACKHP,
	};

	int									m_ShowVersion;
	int									m_WinWidth, m_WinHeight;
	int									m_prevHP;
	cocos2d::Sprite*					m_STEbarSpr;
	cocos2d::Sprite*					m_MonsterHPContainerSpr;
	cocos2d::Sprite*					m_MonsterHPSpr;
	cocos2d::Sprite*					m_WindowHP;
	cocos2d::Sprite*					m_WindowSTE;

	void								drawCurrentHP(int currentHP, int maxHP);
	void								drawCurrentSTE(int currentSTE, int maxSTE);
	void								drawMonsterHP(int currentHP, int maxHP);
	
	void								setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE);
};