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

	m_sprCharWinContainer = Sprite::create("CharWindow.png");
	m_sprCharWinContainer->setAnchorPoint(Point(0, 0));
	m_sprCharWinContainer->setPosition(Point(m_WinWidth, 25));
	this->addChild(m_sprCharWinContainer, 12);

	m_sprCharWinTrigger = Sprite::create("CharWindowTrigger.png");
	m_sprCharWinTrigger->setAnchorPoint(Point(0, 1));
	m_sprCharWinTrigger->setPosition(Point(-30, 250));
	m_sprCharWinContainer->addChild(m_sprCharWinTrigger);

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
		int currentHP = GET_STAGE_MANAGER()->getPlayer()->getHp();
		int maxHP = GET_STAGE_MANAGER()->getPlayer()->getMaxHp();
		int currentSTE = GET_STAGE_MANAGER()->getPlayer()->getSteam();
		int maxSTE = GET_STAGE_MANAGER()->getPlayer()->getMaxSteam();

		auto action_0 = MoveTo::create(0.5, Point(m_WinWidth - 250, 25));
		auto action_1 = EaseBackIn::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = true;
	}
}

void EquipmentWindow::hideCharacterWindow()
{
	if (m_sprCharWinContainer->getNumberOfRunningActions() == 0)
	{
		auto action_0 = MoveTo::create(0.7, Point(m_WinWidth, 25));
		auto action_1 = EaseBounceOut::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = false;
	}
}
