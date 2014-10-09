#include "UILayer.h"
#include "Utils.h"
#include "GameLayer.h"
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

void UILayer::update( float dTime )
{

}
