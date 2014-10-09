#include "EquipmentWindow.h"
#include "GameManager.h"
#include "Utils.h"

USING_NS_CC;

bool EquipmentWindow::init()
{
	m_CharWinOn = false;

	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_sprCharWinContainer = Sprite::create("Char_Window.png");
	m_sprCharWinContainer->setAnchorPoint(Point(0, 1));
	m_sprCharWinContainer->setPosition(Point(m_WinWidth - 30, m_WinHeight - 160));
	this->addChild(m_sprCharWinContainer, 12);

	this->scheduleUpdate();
	return true;
}

void EquipmentWindow::update(float dTime)
{

}

void EquipmentWindow::showCharacterWindow()
{
	if (m_sprCharWinContainer->getNumberOfRunningActions() == 0)
	{
		auto action_0 = MoveTo::create(0.4, Point(m_WinWidth - 270, m_WinHeight - 160));
		auto action_1 = EaseBackIn::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = true;
	}
}

void EquipmentWindow::hideCharacterWindow()
{
	if (m_sprCharWinContainer->getNumberOfRunningActions() == 0)
	{
		auto action_0 = MoveTo::create(0.7, Point(m_WinWidth - 30, m_WinHeight - 160));
		auto action_1 = EaseBounceOut::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = false;
	}
}
