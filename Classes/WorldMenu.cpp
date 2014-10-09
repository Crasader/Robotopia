#include "WorldMenu.h"
#include "Utils.h"

USING_NS_CC;

bool WorldMenu::init()
{
	this->scheduleUpdate();

	return true;
}

void WorldMenu::update(float dTime)
{
	if (m_Player == nullptr)
	{
		return;
	}
}
