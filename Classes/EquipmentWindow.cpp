#include "EquipmentWindow.h"
#include "GameManager.h"
#include "Utils.h"

USING_NS_CC;

bool EquipmentWindow::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto sprCharWinContainer = Sprite::create("Char_Window.png");
	sprCharWinContainer->setAnchorPoint(Point(0, 1));
	sprCharWinContainer->setPosition(Point(m_WinWidth - 30, m_WinHeight - 100));
	this->addChild(sprCharWinContainer, 12);

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
