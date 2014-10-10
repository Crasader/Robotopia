//BarContainer.h
//
//HP bar, STE bar 구성
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


	int									m_WinWidth, m_WinHeight;
	int									m_prevHP;
	cocos2d::Vector<cocos2d::Sprite*>	m_STEs;

	//void								setMaxHP(int maxHP); 혹시 피통이 늘어날 수도 있으니까
	void								drawCurrentHP(int currentHP, int maxHP);
	void								setMaxSTE(int maxSTE);
	void								drawCurrentSTE(int currentSTE);
	void								setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE);
};