#include "StoreWindow.h"

USING_NS_CC;

bool StoreWindow::init()
{
	m_StoreWindowOn = false;
	m_StoreWindowSpr = Sprite::create("StoreWindow.png");
	m_StoreWindowSpr->setVisible(false);
	m_StoreWindowSpr->setAnchorPoint(Point(0, 0));
	m_StoreWindowSpr->setPosition(Point(100, 100));
	
	this->addChild(m_StoreWindowSpr);
}

void StoreWindow::update(float dTime)
{

}

void StoreWindow::showStore()
{
	m_StoreWindowSpr->setVisible(true);
	m_StoreWindowOn = true;
}

void StoreWindow::hideStore()
{
	m_StoreWindowSpr->setVisible(false);
	m_StoreWindowOn = false;
}

