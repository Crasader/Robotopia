#include "UILayer.h"

#include "Minimap.h"
#include "WorldMenu.h"
#include "BarContainer.h"
#include "EquipmentWindow.h"

USING_NS_CC;

bool UILayer::init()
{
	this->scheduleUpdate();
	return true;
}


void UILayer::update(float dTime)
{
	KeyState charWinKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER_UI);
	KeyState enterKey = GET_INPUT_MANAGER()->getKeyState(KC_RETURN);
	KeyState escKey = GET_INPUT_MANAGER()->getKeyState(KC_MENU);
	KeyState upKey = GET_INPUT_MANAGER()->getKeyState(KC_UP);
	KeyState downKey = GET_INPUT_MANAGER()->getKeyState(KC_DOWN);
	
	if (charWinKey == KS_PRESS)
	{
		if (m_WorldMenu->getWorldMenuOn() == false)
		{
			if (m_EquipmentWindow->getCharWinOn() == false)
			{
				m_EquipmentWindow->showCharacterWindow();
			}
			else if (m_EquipmentWindow->getCharWinOn() == true)
			{
				m_EquipmentWindow->hideCharacterWindow();
			}
		}
	}
	
	if (enterKey == KS_PRESS)
	{

	}
	
	if (escKey == KS_PRESS)
	{
		if (m_WorldMenu->getWorldMenuOn() == false)
		{
			if (m_EquipmentWindow->getCharWinOn() == true)
			{
				m_EquipmentWindow->hideCharacterWindow();
			}
			else
			{
				m_WorldMenu->showWorldMenu();
			}
		}
		else
		{
			m_WorldMenu->hideWorldMenu();
		}
	}
}

void UILayer::initializeUILayer()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_BarContainer = BarContainer::create();
	m_EquipmentWindow = EquipmentWindow::create();
	m_Minimap = Minimap::create();
	m_WorldMenu = WorldMenu::create();
	this->addChild( m_BarContainer );
	this->addChild( m_EquipmentWindow );
	this->addChild( m_Minimap );
	this->addChild( m_WorldMenu );
}
