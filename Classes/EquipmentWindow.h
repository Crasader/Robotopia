//EquipmentWindow.h
//
//Equipment, Status, Inventory ����
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class EquipmentWindow : public UILayer
{
public:
	virtual bool					init();
	void							update(float dTime);
	void							showCharacterWindow();
	void							hideCharacterWindow();

	CREATE_FUNC(EquipmentWindow);

private:
	bool							m_WindowOn;

};