#include "Minimap.h"
#include "Utils.h"

USING_NS_CC;


bool Minimap::init()
{
	auto sprMinimap = Sprite::create("Minimap_Fake.png");
	sprMinimap->setAnchorPoint(Point(0, 1));
	sprMinimap->setOpacity(120);
	sprMinimap->setPosition(Point(m_WinWidth - 200, m_WinHeight - 15));
	this->addChild(sprMinimap);

	this->scheduleUpdate();
	return true;
}

void Minimap::update(float dTime)
{

}
