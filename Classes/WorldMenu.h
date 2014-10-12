//WorldMenu.h
//
//WorldScene에서 ESC 입력 시 뜨는 WorldMenu
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

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
	cocos2d::Sprite*				m_WorldMenuContainerSpr;
	cocos2d::Sprite*				m_ButtonSaveQuitSpr;
	cocos2d::Sprite*				m_ButtonSaveQuitClickedSpr;
	cocos2d::Sprite*				m_ButtonSaveQuitHighlightSpr;
};