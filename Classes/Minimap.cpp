#include "Minimap.h"

USING_NS_CC;

#define MINIMAP_SCALE 30
#define ROOM_RECT_MARGIN 3

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
	
	m_MinimapBgRect = DrawNode::create();
	Vec2 points[] =
	{
		Vec2(0, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, 0),
		Vec2(0, 0),
	};
	m_MinimapBgRect->drawPolygon(points, 4, Color4F(Color4B(51, 51, 51, 0)), 0, Color4F(1.0f, 0.3f, 0.3f, 1)); //Color4F(Rf, Gf, Bf, Opacityf) or Color4F(Color4B(Rb, Gb, Bb, Opacityb))
	m_MinimapBgRect->setAnchorPoint(Point(0, 0));
	m_MinimapBgRect->setPosition(Point(-200, -200));
	sprMinimap->addChild(m_MinimapBgRect);

	for (int j = 0; j < m_fd.height; ++j)
	{
		for (int i = 0; i < m_fd.width; ++i)
		{
			drawRoomRect(i, j);
		}
	}
	this->scheduleUpdate();
	return true;
}

void Minimap::update(float dTime)
{

}

void Minimap::drawRoomRect(int xidx, int yidx)
{
	int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(xidx, yidx);
	if (roomNum != 0)
	{
		auto roomRect = DrawNode::create();
		Vec2 vertices1 = Vec2(0, MINIMAP_SCALE);
		Vec2 vertices2 = Vec2(MINIMAP_SCALE, MINIMAP_SCALE);
		Vec2 vertices3 = Vec2(MINIMAP_SCALE, 0);
		Vec2 vertices4 = Vec2(0, 0);

		if (xidx != 0 && xidx != m_fd.width && yidx != 0 && yidx != m_fd.height)
		{
			if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(xidx - 1, yidx)) //Left
			{
				vertices1.x += ROOM_RECT_MARGIN;
				vertices4.x += ROOM_RECT_MARGIN;
			}
			if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(xidx, yidx + 1)) //Up
			{
				vertices1.y -= ROOM_RECT_MARGIN;
				vertices2.y -= ROOM_RECT_MARGIN;
			}
			if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(xidx + 1, yidx)) //Right
			{
				vertices2.x -= ROOM_RECT_MARGIN;
				vertices3.x -= ROOM_RECT_MARGIN;
			}
			if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(xidx, yidx - 1)) //Down
			{
				vertices3.y += ROOM_RECT_MARGIN;
				vertices4.y += ROOM_RECT_MARGIN;
			}
		}

		Vec2 points[] =
		{
			vertices1,
			vertices2,
			vertices3,
			vertices4
		};

		//�÷��̾� ���� �� ���� ����
		int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
		if (currentRoom == roomNum)
		{
			roomRect->drawPolygon(points, 4, Color4F(Color4B(212, 24, 26, 120)), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
		}
		else if (roomNum != 0)
		{
			roomRect->drawPolygon(points, 4, Color4F(Color4B(117, 198, 185, 120)), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
		}

		roomRect->setAnchorPoint(Point(0, 0));
		roomRect->setPosition(Point(xidx * MINIMAP_SCALE, yidx * MINIMAP_SCALE));
		m_MinimapBgRect->addChild(roomRect);
	}
}
