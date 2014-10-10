#include "Minimap.h"
#include "Utils.h"

USING_NS_CC;

#define MINIMAPSCALE 20

bool Minimap::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto sprMinimap = Sprite::create("Minimap_Frame.png");
	sprMinimap->setAnchorPoint(Point(0, 1));
	sprMinimap->setOpacity(120);
	sprMinimap->setPosition(Point(m_WinWidth - 200, m_WinHeight - 15));
	this->addChild(sprMinimap);

	FloorData fd = GET_STAGE_MANAGER()->getFloorData();
	auto minimapBg = DrawNode::create();
	Vec2 points[] =
	{
		Vec2(0, fd.height * MINIMAPSCALE),
		Vec2(fd.width * MINIMAPSCALE, fd.height * MINIMAPSCALE),
		Vec2(fd.width * MINIMAPSCALE, 0),
		Vec2(0, 0),
	};
	minimapBg->drawPolygon(points, 4, Color4F(0.5f, 0.5f, 0.5f, 1), 0, Color4F(1.0f, 0.3f, 0.3f, 1));
	minimapBg->setAnchorPoint(Point(0, 0));
	minimapBg->setPosition(Point());
	sprMinimap->addChild(minimapBg);

	for (int j = 0; j < fd.height; ++j)
	{
		for (int i = 0; i < fd.width; ++i)
		{
		}
	}
	this->scheduleUpdate();
	return true;
}

void Minimap::update(float dTime)
{

}
