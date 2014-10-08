#include "UILayer.h"
#include "Utils.h"
#include "GameLayer.h"

USING_NS_CC;

bool UILayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;
	
	m_Player = nullptr;
	m_prevHP = 0;

	//HP Container
	auto sprHPContainer = Sprite::create("Container_HP.png");
	sprHPContainer->setScale(0.75);
	sprHPContainer->setAnchorPoint(Point(0, 1));
	sprHPContainer->setPosition(Point(20, m_WinHeight - 20));
	this->addChild(sprHPContainer, 10);
	
	auto sprHPBlock1 = Sprite::create("HP_Block1.png");
	sprHPBlock1->setAnchorPoint(Point(0, 1));
	sprHPBlock1->setPosition(Point(21, m_WinHeight - 27));
	this->addChild(sprHPBlock1, 8, SPRITE_FOREHP);

	auto sprHPBlock2 = Sprite::create("HP_Block2.png");
	sprHPBlock2->setAnchorPoint(Point(0, 1));
	sprHPBlock2->setPosition(Point(21, m_WinHeight - 27));
	this->addChild(sprHPBlock2, 7, SPRITE_BACKHP);

	//STE Container
	auto sprSTEContainer = Sprite::create("Container_STE.png");
	sprSTEContainer->setScale(0.75);
	sprSTEContainer->setAnchorPoint(Point(0, 1));
	sprSTEContainer->setPosition(Point (20, m_WinHeight - 80));
	this->addChild(sprSTEContainer, 10);

	//Label - 실제 개발에서는 문자를 이미지로 대체
	auto hpLabel = Label::createWithSystemFont("", "Thonburi", 20);
	hpLabel->setPosition(Point(175, m_WinHeight - 45));
	auto steLabel = Label::createWithSystemFont("", "Thonburi", 20);
	steLabel->setPosition(Point(175, m_WinHeight - 100));
	this->addChild(hpLabel, 10, LABEL_HPSTATUS);
	this->addChild(steLabel, 10, LABEL_STEAMSTATUS);

	//Minimap_Fake 진짜는 아직 없다!!!
	auto sprMinimap = Sprite::create("Minimap_Fake.png");
	sprMinimap->setAnchorPoint(Point(0, 1));
	sprMinimap->setOpacity(120);
	sprMinimap->setPosition(Point(m_WinWidth - 200, m_WinHeight - 15));
	this->addChild(sprMinimap);
	
	this->scheduleUpdate();
	return true;
}

void UILayer::update(float dTime)
{
	if (m_Player == nullptr)
	{
		auto gameLayer = ((WorldScene*)this->getParent())->getGameLayer();
		m_Player = gameLayer->getPlayer();
	}

	int currentHP = m_Player->getHp();
	int maxHP = m_Player->getMaxHp();
	int currentSTE = m_Player->getSteam();
	int maxSTE = m_Player->getMaxSteam();

	drawCurrentHP(currentHP, maxHP);

	setMaxSTE(maxSTE);
	drawCurrentSTE(currentSTE);

	setLabels(currentHP, maxHP, currentSTE, maxSTE);

}


void UILayer::drawCurrentHP(int currentHP, int maxHP)
{
	Sprite* foreHP = (Sprite*)this->getChildByTag(SPRITE_FOREHP);
	Sprite* backHP = (Sprite*)this->getChildByTag(SPRITE_BACKHP);

	float scaleHP = (float)currentHP / maxHP;
	foreHP->setScaleX(scaleHP);
	if (currentHP < m_prevHP && backHP->getNumberOfRunningActions() == 0)
	{
		auto backHPaction = ScaleTo::create(1, scaleHP, 1);
		backHP->runAction(backHPaction);
	}
	else if (currentHP > m_prevHP)
	{
		backHP->setScaleX(scaleHP);
	}
	m_prevHP = currentHP;
}

void UILayer::setMaxSTE(int maxSTE)
{
	int sizeOfSTEs = m_STEs.size();
	if (maxSTE != sizeOfSTEs)
	{
		m_STEs.clear();
		for (int i = 0; i < maxSTE - sizeOfSTEs; ++i)
		{
			auto sprSTE = Sprite::create("STE_Block.png");
			sprSTE->setScale(0.8);
			sprSTE->setVisible(false);
			sprSTE->setPosition(Point(37 + (17 * i), m_WinHeight - 103));
			m_STEs.pushBack(sprSTE);
			this->addChild(sprSTE);
		}
	}
}

void UILayer::drawCurrentSTE(int currentSTE)
{
	int countSTE = 0;
	for (auto sprSTE : m_STEs)
	{
		if (countSTE < currentSTE)
		{
			sprSTE->setVisible(true);
		}
		else
		{
			sprSTE->setVisible(false);
		}
		countSTE++;
	}
}

void UILayer::setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE)
{
	std::string strCurrentHP = std::to_string(currentHP);
	std::string strMaxHP = std::to_string(maxHP);
	std::string strCurrentSTE = std::to_string(currentSTE);
	std::string strMaxSTE = std::to_string(maxSTE);

	std::stringstream sumHP;
	sumHP << strCurrentHP << " / " << strMaxHP;
	std::string hpStr = sumHP.str();

	std::stringstream sumSTE;
	sumSTE << strCurrentSTE << " / " << strMaxSTE;
	std::string steStr = sumSTE.str();

	Label* hpStatus = (Label*)this->getChildByTag(LABEL_HPSTATUS);
	hpStatus->setString(hpStr);
	Label* steamStatus = (Label*)this->getChildByTag(LABEL_STEAMSTATUS);
	steamStatus->setString(steStr);
}

