#include "WorldMenu.h"
USING_NS_CC;

bool WorldMenu::init()
{
	m_WorldMenuOn = false;
	m_WorldMenuContainerSpr = Sprite::create("WorldMenuContainer.png");
	m_WorldMenuContainerSpr->setAnchorPoint(Point(0, 0));
	m_WorldMenuContainerSpr->setPosition(Point(0, 0));
	m_WorldMenuContainerSpr->setVisible(false);
	this->addChild(m_WorldMenuContainerSpr);
	
	//메뉴가 많으면 배열에 스프라이트 넣고 돌리기
	m_ButtonSaveQuitSpr = Sprite::create("WorldMenuSaveAndQuit.png");
	m_ButtonSaveQuitSpr->setPosition(Point(m_WorldMenuContainerSpr->getContentSize().width / 2, m_WorldMenuContainerSpr->getContentSize().height / 2));
	m_WorldMenuContainerSpr->addChild(m_ButtonSaveQuitSpr);
	return true;
}

void WorldMenu::update(float dTime)
{

}

void WorldMenu::showWorldMenu()
{
	m_WorldMenuContainerSpr->setVisible(true);
	m_WorldMenuOn = true;
}

void WorldMenu::hideWorldMenu()
{
	m_WorldMenuContainerSpr->setVisible(false);
	m_WorldMenuOn = false;
}

void WorldMenu::changeButtonState(ButtonState buttonState)
{
	switch (buttonState)
	{
	case NORMAL:
		m_ButtonSaveQuitSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("WorldMenuSaveAndQuit.png"));
		break;
	case HIGHLIGHT:
		m_ButtonSaveQuitSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("WorldMenuSaveAndQuit_Highlight.png"));
		break;
	case CLICKED:
		m_ButtonSaveQuitSpr->setTexture(Director::getInstance()->getTextureCache()->addImage("WorldMenuSaveAndQuit_Clicked.png"));
		break;
	}
}
