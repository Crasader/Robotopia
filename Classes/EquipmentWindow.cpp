#include "EquipmentWindow.h"
#include "GameManager.h"
#include "Utils.h"

USING_NS_CC;

bool EquipmentWindow::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	this->scheduleUpdate();
	return true;
}

void EquipmentWindow::update(float dTime)
{

}

void EquipmentWindow::showCharacterWindow()
{

}

void EquipmentWindow::hideCharacterWindow()
{

}
