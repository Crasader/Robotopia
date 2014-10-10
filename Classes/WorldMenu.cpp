#include "WorldMenu.h"
USING_NS_CC;

bool WorldMenu::init()
{
	m_WorldMenuOn = false;
	m_sprWorldMenuContainer = Sprite::create("WorldMenuContainer.png");
	m_sprWorldMenuContainer->setAnchorPoint(Point(0, 0));
	m_sprWorldMenuContainer->setPosition(Point(0, 0));
	m_sprWorldMenuContainer->setVisible(false);
	this->addChild(m_sprWorldMenuContainer);
	
	this->scheduleUpdate();

	return true;
}

void WorldMenu::update(float dTime)
{

}

void WorldMenu::showWorldMenu()
{
	m_sprWorldMenuContainer->setVisible(true);
	m_WorldMenuOn = true;
}

void WorldMenu::hideWorldMenu()
{
	m_sprWorldMenuContainer->setVisible(false);
	m_WorldMenuOn = false;
}
