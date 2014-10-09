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

	m_WorldMenuOn = true;
}

void WorldMenu::hideWorldMenu()
{

	m_WorldMenuOn = false;
}
