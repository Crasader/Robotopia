#include "Minimap.h"

USING_NS_CC;

#define MINIMAP_SCALE 30
#define ROOM_RECT_MARGIN 3

bool Minimap::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto sprMinimap = Sprite::create("Minimap_Container.png");
	sprMinimap->setAnchorPoint(Point(1, 1));
	sprMinimap->setOpacity(150);
	sprMinimap->setPosition(Point(m_WinWidth, m_WinHeight));
	this->addChild(sprMinimap);

	auto sprMinimapFrame = Sprite::create();
	Rect testRect = Rect(0, 0, 200, 150);
	m_MinimapFrame = SpriteFrame::create("Minimap_Frame.png", testRect);
	sprMinimapFrame->setAnchorPoint(Point(0, 0));
	sprMinimapFrame->setPosition(Point(10, 10));
	sprMinimapFrame->setOpacity(50);
	sprMinimapFrame->setDisplayFrame(m_MinimapFrame);
	sprMinimap->addChild(sprMinimapFrame);

	auto sprPlayerPosition = Sprite::create("Minimap_Player.png");
	sprPlayerPosition->setAnchorPoint(Point(0.5, 0.5));
	sprPlayerPosition->setPosition(Point(sprMinimap->getContentSize().width / 2, sprMinimap->getContentSize().height / 2));
	sprPlayerPosition->setOpacity(200);
	sprMinimapFrame->addChild(sprPlayerPosition, 15, MINIMAP_PLAYER);

	m_fd = GET_STAGE_MANAGER()->getFloorData();
	m_VisitedRoom = GET_STAGE_MANAGER()->getVisitedStageNums();

	m_MinimapBgRect = DrawNode::create();
	Vec2 points[] =
	{
		Vec2(0, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, m_fd.height * MINIMAP_SCALE),
		Vec2(m_fd.width * MINIMAP_SCALE, 0),
		Vec2(0, 0),
	};
	m_MinimapBgRect->drawPolygon(points, 4, Color4F(Color4B(51, 51, 51, 0)), 0, Color4F(1.0f, 0.3f, 0.3f, 1)); //Color4F(Rf, Gf, Bf, Opacityf) or Color4F(Color4B(Rb, Gb, Bb, Opacityb))
	sprPlayerPosition->setAnchorPoint(Point(0, 0));
	sprPlayerPosition->addChild(m_MinimapBgRect, -10);
	

// 	auto minimapFrame = SpriteFrame::create("CharWindow.png", testRect);
// 	this->addChild(minimapFrame);
// 
// 	Sprite* pSprite = Sprite::create();
// 	SpriteFrame* frame = SpriteFrame::create("CharWindow.png", testRect);
// 	pSprite->setPosition(Point(500, 200));
// 	pSprite->setDisplayFrame(frame);
// 	this->addChild(pSprite);

// 	Texture2D *pTexture = SourceSpriteObj->getTexture();
// 	
// 	Sprite*DestSpriteObj = Sprite::s(pTexture, CGRect);
	
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

	this->scheduleUpdate();
	return true;
}

void Minimap::update(float dTime)
{
	int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
	Point playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	Vec2 playerRoomOrigin = GET_STAGE_MANAGER()->positionToIdxOfFloor(playerPosition);
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
