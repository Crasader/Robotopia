#include "EquipmentWindow.h"

USING_NS_CC;

bool EquipmentWindow::init()
{
	Player* player = GET_STAGE_MANAGER()->getPlayer();
	if (player == nullptr)
	{
		return false;
	}

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

		drawWinHP(currentHP, maxHP);
		drawWInSTE(currentSTE, maxSTE);

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
	float scaleHP = (float)currentHP / (maxHP * 2);
	auto sprHP = Sprite::create("HP_Block1.png");
	sprHP->setScale(0.4f);
	sprHP->setScaleX(scaleHP);
	sprHP->setPosition(Point(126, 347));
	m_sprCharWinContainer->addChild(sprHP, 13);
}

void EquipmentWindow::drawWInSTE(int currentSTE, int maxSTE)
{
	float scaleSTE = (float)currentSTE / (maxSTE * 2);
	auto sprSTE = Sprite::create("HP_Block2.png");
	sprSTE->setScale(0.4f);
	sprSTE->setScaleX(scaleSTE);
	sprSTE->setPosition(Point(126, 331));
	m_sprCharWinContainer->addChild(sprSTE, 13);
}

Rect EquipmentWindow::getTriggerRect()
{
	Point containerPosition = m_sprCharWinContainer->getPosition();
	Size triggerSize = m_sprCharWinTrigger->getContentSize();
	auto triggerRect = Rect(containerPosition.x - 30, containerPosition.y + 250 - triggerSize.height, triggerSize.width, triggerSize.height);
	return triggerRect;
}
