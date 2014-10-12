//EquipmentWindow.h
//
//Equipment, Status, Inventory 备己
//
//累己磊 : 快犁快
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

class EquipmentWindow : public cocos2d::Node
{
public:
	virtual bool		init();
	void				update(float dTime);
	bool				getCharWinOn() { return m_CharWinOn; }
	void				showCharacterWindow();
	void				hideCharacterWindow();
	cocos2d::Rect		getTriggerRect();

	CREATE_FUNC(EquipmentWindow);

private:
	bool				m_CharWinOn;
	int					m_WinWidth, m_WinHeight;
	cocos2d::Sprite*	m_sprCharWinTrigger;
	cocos2d::Sprite*	m_sprCharWinContainer;
	cocos2d::Sprite*	m_sprCharWinHP;
	cocos2d::Sprite*	m_sprCharWinSTE;

	void				drawWinHP(int currentHP, int maxHP);
	void				drawWInSTE(int currentSTE, int maxSTE);
};