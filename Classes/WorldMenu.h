//WorldMenu.h
//
//WorldScene에서 ESC 입력 시 뜨는 WorldMenu
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class WorldMenu : public cocos2d::Node
{
public:
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(WorldMenu);

	void							showWorldMenu();
	void							hideWorldMenu();

private:
	int								m_WinWidth, m_WinHeight;


};