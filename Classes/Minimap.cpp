#include "Minimap.h"

USING_NS_CC;

#define MINIMAP_SCALE 30
#define ROOM_RECT_MARGIN 3

bool Minimap::init()
{
	m_MinimapWinOn = false;

	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto sprMinimap = Sprite::create("Minimap_Container.png");
	auto sprMinimapTrigger = Sprite::create("Minimap_Trigger.png");
	auto sprMinimapWinContainer = Sprite::create("Minimap_Win.png");
	auto sprMinimapClose = Sprite::create("Minimap_Close.png");
	auto sprPlayerPosition = Sprite::create("Minimap_Player.png");
	m_MinimapBgRect = DrawNode::create();
	Rect testRect = Rect(0, 0, 50, 50);
	m_MinimapFrame = SpriteFrame::create("Minimap_Frame.png", testRect);

	sprMinimap->setAnchorPoint(Point(1, 1));
	sprMinimap->setOpacity(150);
	sprMinimap->setPosition(Point(m_WinWidth, m_WinHeight));

	sprMinimapTrigger->setAnchorPoint(Point(1, 1));
	sprMinimapTrigger->setPosition(Point(sprMinimap->getContentSize().width, sprMinimap->getContentSize().height));

	sprMinimapWinContainer->setAnchorPoint(Point(0.5, 0.5));
	sprMinimapWinContainer->setPosition(Point(m_WinWidth / 2, m_WinHeight / 2));
	sprMinimapWinContainer->setVisible(false);

	sprMinimapClose->setAnchorPoint(Point(1, 1));
	sprMinimapClose->setPosition(Point(sprMinimapWinContainer->getContentSize().width, sprMinimapWinContainer->getContentSize().height));

	sprPlayerPosition->setAnchorPoint(Point(0.5, 0.5));
	sprPlayerPosition->setPosition(Point(sprMinimap->getContentSize().width / 2, sprMinimap->getContentSize().height / 2));
	sprPlayerPosition->setOpacity(200);

	m_fd = GET_STAGE_MANAGER()->getFloorData();
	m_VisitedRoom = GET_STAGE_MANAGER()->getVisitedStageNums();

	Vec2 points[] =
	{
		Vec2(0, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, 0),
		Vec2(0, 0),
	};
	m_MinimapBgRect->drawPolygon(points, 4, Color4F(Color4B(100, 20, 20, 0)), 0, Color4F(1.0f, 0.3f, 0.3f, 1)); //Color4F(Rf, Gf, Bf, Opacityf) or Color4F(Color4B(Rb, Gb, Bb, Opacityb))
	m_MinimapBgRect->setAnchorPoint(Point(0.5, 0.5));
	
	for (int j = 0; j < m_fd.height; ++j)
	{
		for (int i = 0; i < m_fd.width; ++i)
		{
			int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(i, j);
			for (auto room : m_VisitedRoom)
			{
				if (room == roomNum)
				{
					drawRoomRect(i, j);
				}
			}
		}
	}

// 	this->addChild(sprMinimap, 10, MINIMAP);
// 	this->addChild(sprMinimapWinContainer, 25, MINIMAP_WIN);
// 	sprMinimapWinContainer->addChild(sprMinimapClose, 26, MINIMAP_WIN_CLOSE);
// 	sprMinimapWinContainer->addChild(sprPlayerPosition);
// 	sprMinimap->addChild(sprMinimapTrigger, 20, MINIMAP_WIN_OPEN);
// 	sprMinimap->addChild(sprPlayerPosition, 15, MINIMAP_PLAYER);
// 	sprPlayerPosition->addChild(m_MinimapBgRect, -10);

	return true;
}

void Minimap::update(float dTime)
{
	int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
	Point playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	Vec2 playerRoomOrigin = GET_STAGE_MANAGER()->positionToIdxOfFloor(playerPosition);
	this->removeAllChildren();
	init();
	m_MinimapBgRect->setPosition(Point(-1 * (playerRoomOrigin.x * MINIMAP_SCALE + 6), -1 * (playerRoomOrigin.y * MINIMAP_SCALE + 6)));
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

		//플레이어 현재 방 색깔 구분
		int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
		if (currentRoom == roomNum)
		{
			roomRect->drawPolygon(points, 4, Color4F(Color4B(212, 24, 26, 100)), 0, Color4F(0.2f, 0.7f, 0.3f, 1));
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


void Minimap::showMinimapWin()
{
// 	Sprite* sprMinimap = (Sprite*)this->getChildByTag(MINIMAP);
// 	Sprite* sprMinimapWinContainer = (Sprite*)this->getChildByTag(MINIMAP_WIN);
// 	Sprite* sprMinimapWinOpen = (Sprite*)sprMinimap->getChildByTag(MINIMAP_WIN_OPEN);
// 	Sprite* sprMinimapWinClose = (Sprite*)sprMinimapWinContainer->getChildByTag(MINIMAP_WIN_CLOSE);
// 	
// 	sprMinimapWinContainer->setVisible(true);
// 	sprMinimapWinOpen->setVisible(false);
// 	sprMinimapWinClose->setVisible(true);
// 	m_MinimapWinOn = true;
}

void Minimap::hideMinimapWin()
{
// 	Sprite* sprMinimap = (Sprite*)this->getChildByTag(MINIMAP);
// 	Sprite* sprMinimapWinContainer = (Sprite*)this->getChildByTag(MINIMAP_WIN);
// 	Sprite* sprMinimapWinOpen = (Sprite*)sprMinimap->getChildByTag(MINIMAP_WIN_OPEN);
// 	Sprite* sprMinimapWinClose = (Sprite*)sprMinimapWinContainer->getChildByTag(MINIMAP_WIN_CLOSE);
// 
// 	sprMinimapWinContainer->setVisible(false);
// 	sprMinimapWinOpen->setVisible(true);
// 	sprMinimapWinClose->setVisible(false);
// 	m_MinimapWinOn = false;
}
