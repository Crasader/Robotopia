#include "UILayer.h"
#include "Utils.h"
#include "GameLayer.h"

USING_NS_CC;

bool UILayer::init()
{
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





