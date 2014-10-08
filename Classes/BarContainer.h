//BarContainer.h
//
//HP bar, STE bar 구성
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class BarContainer : public UILayer
{

public:
	static cocos2d::Scene*				createScene();
	virtual bool						init();
	void								update(float dTime);
	
	CREATE_FUNC(BarContainer);


private:
	int									m_prevHP;
	cocos2d::Vector<cocos2d::Sprite*>	m_STEs;

	//void								setMaxHP(int maxHP); 혹시 피통이 늘어날 수도 있으니까
	void								drawCurrentHP(int currentHP, int maxHP);
	void								setMaxSTE(int maxSTE);
	void								drawCurrentSTE(int currentSTE);
	void								setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE);
};