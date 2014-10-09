//WorldMenu.h
//
//WorldScene���� ESC �Է� �� �ߴ� WorldMenu
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"

class WorldMenu : public cocos2d::Node
{
public:
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(WorldMenu);

	void							showWorldMenu();
	void							hideWorldMenu();
	bool							getWorldMenuOn() { return m_WorldMenuOn; }

private:
	int								m_WinWidth, m_WinHeight;
	bool							m_WorldMenuOn;
	cocos2d::Sprite*				m_sprWorldMenuContainer;


};