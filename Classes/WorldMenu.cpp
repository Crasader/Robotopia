#include "WorldMenu.h"
USING_NS_CC;

bool WorldMenu::init()
{
	m_WorldMenuOn = false;
	m_WorldMenuContainerSpr = Sprite::create("WorldMenuContainer.png");
	m_WorldMenuContainerSpr->setAnchorPoint(Point(0, 0));
	m_WorldMenuContainerSpr->setPosition(Point(0, 0));
	m_WorldMenuContainerSpr->setVisible(false);
	this->addChild(m_WorldMenuContainerSpr);
	

	return true;
}

void WorldMenu::update(float dTime)
{

}

void WorldMenu::showWorldMenu()
{
	m_WorldMenuContainerSpr->setVisible(true);
	m_WorldMenuOn = true;
}

void WorldMenu::hideWorldMenu()
{
	m_WorldMenuContainerSpr->setVisible(false);
	m_WorldMenuOn = false;
}
