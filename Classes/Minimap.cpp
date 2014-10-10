#include "Minimap.h"

USING_NS_CC;

#define MINIMAPSCALE 30

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

	m_fd = GET_STAGE_MANAGER()->getFloorData();
	
	auto minimapBg = DrawNode::create();
	Vec2 points[] =
	{
		Vec2(0, m_fd.height * MINIMAPSCALE),
		Vec2(m_fd.width * MINIMAPSCALE, m_fd.height * MINIMAPSCALE),
		Vec2(m_fd.width * MINIMAPSCALE, 0),
		Vec2(0, 0),
	};
	minimapBg->drawPolygon(points, 4, Color4F(Color4B(51, 51, 51, 0)), 0, Color4F(1.0f, 0.3f, 0.3f, 1)); //Color4F(Rf, Gf, Bf, Opacityf) or Color4F(Color4B(Rb, Gb, Bb, Opacityb))
	minimapBg->setAnchorPoint(Point(0, 0));
	minimapBg->setPosition(Point(-200, -200));
	sprMinimap->addChild(minimapBg);

	for (int j = 0; j < m_fd.height; ++j)
	{
		for (int i = 0; i < m_fd.width; ++i)
		{
// 			auto roomRect = DrawNode::create();
// 			roomRect = drawRoomRect(i, j);
// 			minimapBg->addChild(roomRect);
		}
	}
	this->scheduleUpdate();
	return true;
}

void Minimap::update(float dTime)
{

}

DrawNode* Minimap::drawRoomRect(int xidx, int yidx)
{
	auto roomRect = DrawNode::create();
	int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
	int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(xidx, yidx);
	
	for (int i = 0; i < 4; ++i)
	{

	}

// 	Vec2 points[] =
// 	{
// 		Vec2(0, MINIMAPSCALE),
// 		Vec2(MINIMAPSCALE, MINIMAPSCALE),
// 		Vec2(MINIMAPSCALE, 0),
// 		Vec2(0, 0),
// 	};
// 	roomRect->drawPolygon(points, 4, Color4F(0.2f, 0.7f, 0.8f, 1), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
// 	roomRect->setAnchorPoint(Point(0, 0));
// 	roomRect->setPosition(Point(i * MINIMAPSCALE, j * MINIMAPSCALE));

	// 			int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(i, j);
	// 			int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
	// 			if (currentRoom == roomNum)
	// 			{
	// 				auto currentRoomRect = DrawNode::create();
	// 				Vec2 points[] =
	// 				{
	// 					Vec2(0, MINIMAPSCALE),
	// 					Vec2(MINIMAPSCALE, MINIMAPSCALE),
	// 					Vec2(MINIMAPSCALE, 0),
	// 					Vec2(0, 0),
	// 				};
	// 				currentRoomRect->drawPolygon(points, 4, Color4F(0.9f, 0.4f, 0.1f, 1), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
	// 				currentRoomRect->setAnchorPoint(Point(0, 0));
	// 				currentRoomRect->setPosition(Point(i * MINIMAPSCALE, j * MINIMAPSCALE));
	// 				minimapBg->addChild(currentRoomRect);
	// 			}
	// 			else if (roomNum != 0)
	// 			{
	// 				auto roomRect = DrawNode::create();
	// 				Vec2 points[] =
	// 				{
	// 					Vec2(0, MINIMAPSCALE),
	// 					Vec2(MINIMAPSCALE, MINIMAPSCALE),
	// 					Vec2(MINIMAPSCALE, 0),
	// 					Vec2(0, 0),
	// 				};
	// 				roomRect->drawPolygon(points, 4, Color4F(0.2f, 0.7f, 0.8f, 1), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
	// 				roomRect->setAnchorPoint(Point(0, 0));
	// 				roomRect->setPosition(Point(i * MINIMAPSCALE, j * MINIMAPSCALE));
	// 				minimapBg->addChild(roomRect);
	// 			}
	return roomRect;
}
