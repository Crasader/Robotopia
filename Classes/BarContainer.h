//BarContainer.h
//
//HP bar, STE bar ����
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"
#include "WorldScene.h"
#include "UILayer.h"

class BarContainer : public UILayer
{

public:
	virtual bool						init();
	void								update(float dTime);
	
	CREATE_FUNC(BarContainer);


private:
	int									m_prevHP;
	cocos2d::Vector<cocos2d::Sprite*>	m_STEs;

	//void								setMaxHP(int maxHP); Ȥ�� ������ �þ ���� �����ϱ�
	void								drawCurrentHP(int currentHP, int maxHP);
	void								setMaxSTE(int maxSTE);
	void								drawCurrentSTE(int currentSTE);
	void								setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE);
};