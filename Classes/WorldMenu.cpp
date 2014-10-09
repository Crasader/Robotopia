#include "WorldMenu.h"
#include "Utils.h"

USING_NS_CC;

bool WorldMenu::init()
{
	m_WorldMenuOn = false;
	this->scheduleUpdate();

	return true;
}

void WorldMenu::update(float dTime)
{

}

void WorldMenu::showWorldMenu()
{
	auto sprBarContainer = Sprite::create("BarContainer.png");
	sprBarContainer->setAnchorPoint(Point(0, 1));
	sprBarContainer->setPosition(Point(120, m_WinHeight - 20));
	this->addChild(sprBarContainer, 10);

	m_WorldMenuOn = true;
}

void WorldMenu::hideWorldMenu()
{
	m_WorldMenuOn = false;
}
