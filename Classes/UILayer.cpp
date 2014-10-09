#include "UILayer.h"
#include "Utils.h"
#include "GameLayer.h"

USING_NS_CC;

bool UILayer::init()
{
	
	this->scheduleUpdate();
	return true;
}

void UILayer::update(float dTime)
{


}

void UILayer::initializeUILayer()
{
	m_Player = nullptr;

	auto gameLayer = ((WorldScene*)this->getParent())->getGameLayer();
	m_Player = gameLayer->getPlayer();

	Size winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;


}





