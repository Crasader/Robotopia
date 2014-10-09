//EquipmentWindow.h
//
//Equipment, Status, Inventory 备己
//
//累己磊 : 快犁快
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class EquipmentWindow : public cocos2d::Node
{
public:
	virtual bool					init();
	void							update(float dTime);
	void							showCharacterWindow();
	void							hideCharacterWindow();

	CREATE_FUNC(EquipmentWindow);

private:
	int									m_WinWidth, m_WinHeight;
	cocos2d::Sprite*					m_sprCharWinContainer;
};