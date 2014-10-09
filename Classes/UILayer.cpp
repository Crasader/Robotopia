#include "UILayer.h"

#include "Minimap.h"
#include "WorldMenu.h"
#include "BarContainer.h"
#include "EquipmentWindow.h"

USING_NS_CC;

bool UILayer::init()
{
	m_Player = nullptr;

	this->scheduleUpdate();
	return true;
}


void UILayer::update(float dTime)
{
	KeyState charKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER_UI);

	if (charKey == KS_PRESS)
	{
		if (m_CharWinOn == false)
		{
			m_EquipmentWindow->showCharacterWindow();
			m_CharWinOn = true;
		}
		else if (m_CharWinOn == true)
		{
			m_EquipmentWindow->hideCharacterWindow();
			m_CharWinOn = false;
		}
	}

}

void UILayer::initializeUILayer()
{
	if (m_Player == nullptr)
	{
		//m_Player = GET_STAGE_MANAGER()->getPlayer();
	}
	
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
