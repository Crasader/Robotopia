#include "BarContainer.h"
#include "Utils.h"

USING_NS_CC;

bool BarContainer::init()
{
	m_prevHP = 0;
	m_STEs.clear();
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//HP Container
	auto sprBarContainer = Sprite::create("BarContainer.png");
	sprBarContainer->setAnchorPoint(Point(0, 1));
	sprBarContainer->setPosition(Point(0, m_WinHeight));
	this->addChild(sprBarContainer, 10);

	auto sprBarContainerBG = Sprite::create("BarContainerBG.png");
	sprBarContainerBG->setAnchorPoint(Point(0, 1));
	sprBarContainerBG->setPosition(Point(0, m_WinHeight));
	this->addChild(sprBarContainerBG, 5);

	auto sprHPBlock1 = Sprite::create("HP_Block1.png");
	sprHPBlock1->setAnchorPoint(Point(0, 1));
	sprHPBlock1->setPosition(Point(30, m_WinHeight - 3));
	this->addChild(sprHPBlock1, 8, SPRITE_FOREHP);

	auto sprHPBlock2 = Sprite::create("HP_Block2.png");
	sprHPBlock2->setAnchorPoint(Point(0, 1));
	sprHPBlock2->setPosition(Point(30, m_WinHeight - 3));
	this->addChild(sprHPBlock2, 7, SPRITE_BACKHP);

	//Label - 실제 개발에서는 문자를 이미지로 대체
	auto hpLabel = Label::createWithSystemFont("", "Thonburi", 15);
	hpLabel->setPosition(Point(155, m_WinHeight - 17));
	auto steLabel = Label::createWithSystemFont("", "Thonburi", 15);
	steLabel->setPosition(Point(155, m_WinHeight - 42));
	this->addChild(hpLabel, 10, LABEL_HPSTATUS);
	this->addChild(steLabel, 10, LABEL_STEAMSTATUS);

	this->scheduleUpdate();
	return true;
}

void BarContainer::update(float dTime)
{
	auto player = GET_STAGE_MANAGER()->getPlayer();
	if (player != nullptr)
	{
		int currentHP = GET_STAGE_MANAGER()->getPlayer()->getHp();
		int maxHP = GET_STAGE_MANAGER()->getPlayer()->getMaxHp();
		int currentSTE = GET_STAGE_MANAGER()->getPlayer()->getSteam();
		int maxSTE = GET_STAGE_MANAGER()->getPlayer()->getMaxSteam();

		drawCurrentHP(currentHP, maxHP);

		setMaxSTE(maxSTE);
		drawCurrentSTE(currentSTE);

		setLabels(currentHP, maxHP, currentSTE, maxSTE);
	}
}


void BarContainer::drawCurrentHP(int currentHP, int maxHP)
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

void BarContainer::setMaxSTE(int maxSTE)
{
	int sizeOfSTEs = m_STEs.size();
	if (maxSTE != sizeOfSTEs)
	{
		m_STEs.clear();
		for (int i = 0; i < maxSTE - sizeOfSTEs; ++i)
		{
			auto sprSTE = Sprite::create("STE_Block.png");
			sprSTE->setVisible(false);
			sprSTE->setPosition(Point(46 + (10 * i), m_WinHeight - 41));
			m_STEs.pushBack(sprSTE);
			this->addChild(sprSTE, 9);
		}
	}
}

void BarContainer::drawCurrentSTE(int currentSTE)
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

void BarContainer::setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE)
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