#include "EquipmentWindow.h"

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
	this->addChild(m_sprCharWinContainer, 15);

	m_sprCharWinTrigger = Sprite::create("CharWindowTrigger.png");
	m_sprCharWinTrigger->setAnchorPoint(Point(0, 1));
	m_sprCharWinTrigger->setPosition(Point(-30, 250));
	m_sprCharWinContainer->addChild(m_sprCharWinTrigger);

	m_sprCharWinHP = Sprite::create("CharWindow_HP.png");
	m_sprCharWinHP->setAnchorPoint(Point(0, 0));
	m_sprCharWinHP->setPosition(Point(60, 342));
	m_sprCharWinContainer->addChild(m_sprCharWinHP, 13);

	m_sprCharWinSTE = Sprite::create("CharWindow_STE.png");
	m_sprCharWinSTE->setAnchorPoint(Point(0, 0));
	m_sprCharWinSTE->setPosition(Point(60, 326));
	m_sprCharWinContainer->addChild(m_sprCharWinSTE, 13);


	return true;
}

void EquipmentWindow::update(float dTime)
{
		PlayerInfo playerInfo = GET_STAGE_MANAGER()->getPlayer()->getInfo();
		drawWinHP(playerInfo.hp, playerInfo.maxHp);
		drawWInSTE(playerInfo.steam, playerInfo.maxSteam);
}

void EquipmentWindow::showCharacterWindow()
{
	if (m_sprCharWinContainer->getNumberOfRunningActions() == 0)
	{
		//여기다 아이템 리스트 받아와서 이미지 올리기!!!

		auto action_0 = MoveTo::create(0.5f, Point(m_WinWidth - 250, 25));
		auto action_1 = EaseBackIn::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = true;
	}
}

void EquipmentWindow::hideCharacterWindow()
{
	if (m_sprCharWinContainer->getNumberOfRunningActions() == 0)
	{
		auto action_0 = MoveTo::create(0.7f, Point(m_WinWidth, 25));
		auto action_1 = EaseBounceOut::create(action_0);
		m_sprCharWinContainer->runAction(action_1);
		m_CharWinOn = false;
	}
}

void EquipmentWindow::drawWinHP(int currentHP, int maxHP)
{
	float scaleHP = (float)currentHP / maxHP;
	m_sprCharWinHP->setScaleX(scaleHP);
}

void EquipmentWindow::drawWInSTE(int currentSTE, int maxSTE)
{
	float scaleSTE = (float)currentSTE / maxSTE;
	m_sprCharWinSTE->setScaleX(scaleSTE);
}

Rect EquipmentWindow::getTriggerRect()
{
	Point containerPosition = m_sprCharWinContainer->getPosition();
	Size triggerSize = m_sprCharWinTrigger->getContentSize();
	auto triggerRect = Rect(containerPosition.x - 30, containerPosition.y + 250 - triggerSize.height, triggerSize.width, triggerSize.height);
	return triggerRect;
}
