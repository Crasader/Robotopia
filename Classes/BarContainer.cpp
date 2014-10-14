#include "BarContainer.h"

USING_NS_CC;

#define OLDVER 1
#define NEWVER 2

bool BarContainer::init()
{
	m_ShowVersion = NEWVER;
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	if (m_ShowVersion == OLDVER)
	{
		m_prevHP = 0;

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

		m_STEbarSpr = Sprite::create("STE_Block.png");
		m_STEbarSpr->setAnchorPoint(Point(1, 1));
		m_STEbarSpr->setPosition(Point(250, m_WinHeight - 32));
		this->addChild(m_STEbarSpr, 6);

		m_MonsterHPContainerSpr = Sprite::create("MonsterHPContainer.png");
		m_MonsterHPContainerSpr->setVisible(false);
		m_MonsterHPContainerSpr->setPosition(Point(m_WinWidth / 2, m_WinHeight - 50));
		this->addChild(m_MonsterHPContainerSpr);

		m_MonsterHPSpr = Sprite::create("MonsterHPBar.png");
		m_MonsterHPSpr->setAnchorPoint(Point(0, 1));
		m_MonsterHPSpr->setPosition(Point(3.5, m_MonsterHPContainerSpr->getContentSize().height - 3));
		m_MonsterHPContainerSpr->addChild(m_MonsterHPSpr, -2);

		//Label - 실제 개발에서는 문자를 이미지로 대체
		auto hpLabel = Label::createWithSystemFont("", "Thonburi", 15);
		hpLabel->setPosition(Point(155, m_WinHeight - 17));
		auto steLabel = Label::createWithSystemFont("", "Thonburi", 15);
		steLabel->setPosition(Point(155, m_WinHeight - 42));
		this->addChild(hpLabel, 10, LABEL_HPSTATUS);
		this->addChild(steLabel, 10, LABEL_STEAMSTATUS);
	}
	else if (m_ShowVersion == NEWVER)
	{
		m_WindowHP = Sprite::create("GameWindow_HP1.png");
		m_WindowHP->setAnchorPoint(Point(0, 1));
		m_WindowHP->setPosition(Point(0, m_WinHeight));
		m_WindowHP->setScale(1.5f);

		m_WindowSTE = Sprite::create("GameWindow_HP_STE.png");
		m_WindowSTE->setAnchorPoint(Point(0, 0));
		m_WindowSTE->setPosition(Point(110, m_WinHeight - 120));
		m_WindowSTE->setScale(1.2f);

		m_MonsterHPContainerSpr = Sprite::create("MonsterHPContainer.png");
		m_MonsterHPContainerSpr->setVisible(false);
		m_MonsterHPContainerSpr->setPosition(Point(m_WinWidth / 2, m_WinHeight - 50));
		this->addChild(m_MonsterHPContainerSpr);

		m_MonsterHPSpr = Sprite::create("MonsterHPBar.png");
		m_MonsterHPSpr->setAnchorPoint(Point(0, 1));
		m_MonsterHPSpr->setPosition(Point(3.5, m_MonsterHPContainerSpr->getContentSize().height - 3));
		m_MonsterHPContainerSpr->addChild(m_MonsterHPSpr, -2);

		auto hpLabel = Label::createWithSystemFont("", "Thonburi", 15);
		hpLabel->setPosition(Point(60, m_WinHeight - 115));
		this->addChild(hpLabel, 10, LABEL_HPSTATUS);

		this->addChild(m_WindowHP);
		this->addChild(m_WindowSTE);

	}
	return true;
}

void BarContainer::update(float dTime)
{
	if (m_ShowVersion == OLDVER)
	{
		auto player = GET_STAGE_MANAGER()->getPlayer();
		if (player != nullptr)
		{
			auto playerInfo = player->getInfo();

			drawCurrentHP(playerInfo.hp, playerInfo.maxHp);
			drawCurrentSTE(playerInfo.steam, playerInfo.maxSteam);

			setLabels(playerInfo.hp, playerInfo.maxHp, playerInfo.steam, playerInfo.maxSteam);
		}
		auto monster = GET_STAGE_MANAGER()->getLastMonster();
		if (monster != nullptr)
		{
			auto monsterInfo = monster->getInfo();
			drawMonsterHP(monsterInfo.hp, monsterInfo.maxHp);
			m_MonsterHPContainerSpr->setVisible(true);
			if (monsterInfo.hp <= 0)
			{
				m_MonsterHPContainerSpr->setVisible(false);
			}
		}
		else
		{
			m_MonsterHPContainerSpr->setVisible(false);
		}
	}
	else if (m_ShowVersion == NEWVER)
	{
		auto player = GET_STAGE_MANAGER()->getPlayer();
		if (player != nullptr)
		{
			auto playerInfo = player->getInfo();
			float scaleHP = (float)playerInfo.hp / playerInfo.maxHp;
			float scaleSTE = (float)playerInfo.steam / playerInfo.maxSteam;
			m_WindowSTE->setScaleY(scaleSTE);
			
			if (scaleHP <= 1.0f && scaleHP > 0.9f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP1.png"));
			}
			else if (scaleHP <= 0.9f && scaleHP > 0.7f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP2.png"));
			}
			else if (scaleHP <= 0.7f && scaleHP > 0.6f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP3.png"));
			}
			else if (scaleHP <= 0.6f && scaleHP > 0.5f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP4.png"));
			}
			else if (scaleHP <= 0.5f && scaleHP > 0.4f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP5.png"));
			}
			else if (scaleHP <= 0.4f && scaleHP > 0.3f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP6.png"));
			}
			else if (scaleHP <= 0.3f && scaleHP > 0.15f)
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP7.png"));
			}
			else
			{
				m_WindowHP->setTexture(Director::getInstance()->getTextureCache()->addImage("GameWindow_HP7.png"));
			}
			int hpConvert = (int)(scaleHP * 100);
			std::string strHPPrint = std::to_string(hpConvert);
			std::stringstream sumHP;
			sumHP << strHPPrint << " % ";
			std::string hpStr = sumHP.str();

			Label* hpStatus = (Label*)this->getChildByTag(LABEL_HPSTATUS);
			hpStatus->setString(hpStr);
		}
		auto monster = GET_STAGE_MANAGER()->getLastMonster();
		if (monster != nullptr)
		{
			auto monsterInfo = monster->getInfo();
			drawMonsterHP(monsterInfo.hp, monsterInfo.maxHp);
			m_MonsterHPContainerSpr->setVisible(true);
			if (monsterInfo.hp <= 0)
			{
				m_MonsterHPContainerSpr->setVisible(false);
			}
		}
		else
		{
			m_MonsterHPContainerSpr->setVisible(false);
		}
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

void BarContainer::drawCurrentSTE(int currentSTE, int maxSTE)
{
 	float scaleSTE = (float)currentSTE / maxSTE;
	m_STEbarSpr->setPosition(Point(200 * scaleSTE + 50, m_WinHeight - 32));
}

void BarContainer::drawMonsterHP(int currentHP, int maxHP)
{
	float scaleSTE = (float)currentHP / maxHP;
	m_MonsterHPSpr->setScaleX(scaleSTE);
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