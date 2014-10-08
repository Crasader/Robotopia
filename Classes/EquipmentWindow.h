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

class EquipmentWindow : public UILayer
{
public:
	static cocos2d::Scene*			createScene();
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(EquipmentWindow);

private:


};