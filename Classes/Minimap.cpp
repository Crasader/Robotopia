#include "Minimap.h"

USING_NS_CC;

#define MINIMAP_SCALE 30
#define MINIMAPWIN_SCALE 40
#define ROOM_RECT_MARGIN 3

bool Minimap::init()
{
	m_MMWinOn = false;
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto sprMM = Sprite::create("Minimap_Container.png");
	auto sprMMWinContainer = Sprite::create("Minimap_Win.png");
	auto sprMMOpen = Sprite::create("Minimap_Trigger.png");
	auto sprMMWClose = Sprite::create("Minimap_Close.png");
	auto sprMMPlayerPosition = Sprite::create("Minimap_Player.png");

	sprMM->setAnchorPoint(Point(1, 1));
	sprMM->setOpacity(150);
	sprMM->setPosition(Point(m_WinWidth, m_WinHeight));

	sprMMOpen->setAnchorPoint(Point(1, 1));
	sprMMOpen->setPosition(Point(sprMM->getContentSize().width, sprMM->getContentSize().height));

	sprMMWinContainer->setAnchorPoint(Point(0.5, 0.5));
	sprMMWinContainer->setPosition(Point(m_WinWidth / 2, m_WinHeight / 2));
	sprMMWinContainer->setVisible(m_MMWinOn);

	sprMMWClose->setAnchorPoint(Point(1, 1));
	sprMMWClose->setPosition(Point(sprMMWinContainer->getContentSize().width, sprMMWinContainer->getContentSize().height));

	sprMMPlayerPosition->setAnchorPoint(Point(0.5, 0.5));
	sprMMPlayerPosition->setPosition(Point(sprMM->getContentSize().width / 2, sprMM->getContentSize().height / 2));
	sprMMPlayerPosition->setOpacity(200);

	m_fd = GET_STAGE_MANAGER()->getFloorData();

	m_MMBgRect = createBgRect(MINIMAP_SCALE);
	m_MMWBgRect = createBgRect(MINIMAP_WIN_BGRECT);

	this->addChild(sprMM, 10, MINIMAP);
	sprMM->addChild(sprMMOpen, 20, MINIMAP_WIN_OPEN);
	sprMM->addChild(sprMMPlayerPosition, 15, MINIMAP_PLAYER);
	sprMMPlayerPosition->addChild(m_MMBgRect, -10, MINIMAP_BGRECT);

	this->addChild(sprMMWinContainer, 25, MINIMAP_WIN);
	sprMMWinContainer->addChild(sprMMWClose, 26, MINIMAP_WIN_CLOSE);
	sprMMWinContainer->addChild(m_MMWBgRect, 30, MINIMAP_WIN_BGRECT);

	return true;
}

void Minimap::update(float dTime)
{
	Player* player = GET_STAGE_MANAGER()->getPlayer();
	if (player == nullptr)
	{
		return;
	}
	int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
	Point playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	Vec2 playerRoomOrigin = GET_STAGE_MANAGER()->positionToIdxOfFloor(playerPosition);
	Sprite* sprMM = (Sprite*)this->getChildByTag(MINIMAP);
	Sprite* sprMMPlayerPosition = (Sprite*)sprMM->getChildByTag(MINIMAP_PLAYER);
	sprMMPlayerPosition->removeChildByTag(MINIMAP_BGRECT);
	m_MMBgRect = createBgRect(MINIMAP_SCALE);
	sprMMPlayerPosition->addChild(m_MMBgRect, -10, MINIMAP_BGRECT);
	drawRoomRect(m_MMBgRect, MINIMAP_SCALE);
	m_MMBgRect->setPosition(Point(-1 * (playerRoomOrigin.x * MINIMAP_SCALE + 6), -1 * (playerRoomOrigin.y * MINIMAP_SCALE + 6)));
}

void Minimap::drawRoomRect(cocos2d::DrawNode* bgRect, int scale)
{
	m_VisitedRoom = GET_STAGE_MANAGER()->getVisitedStageNums();
	for (int j = 0; j < m_fd.height; ++j)
	{
		for (int i = 0; i < m_fd.width; ++i)
		{
			int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(i, j);
			for (auto room : m_VisitedRoom)
			{
				if (room == roomNum)
				{
					int roomNum = GET_STAGE_MANAGER()->getFloorDataByIdx(i, j);
					if (roomNum != 0)
					{
						auto roomRect = DrawNode::create();
						Vec2 vertices1 = Vec2(0, scale);
						Vec2 vertices2 = Vec2(scale, scale);
						Vec2 vertices3 = Vec2(scale, 0);
						Vec2 vertices4 = Vec2(0, 0);

						if (i != 0 && i != m_fd.width && j != 0 && j != m_fd.height)
						{
							if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(i - 1, j)) //Left
							{
								vertices1.x += ROOM_RECT_MARGIN;
								vertices4.x += ROOM_RECT_MARGIN;
							}
							if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(i, j + 1)) //Up
							{
								vertices1.y -= ROOM_RECT_MARGIN;
								vertices2.y -= ROOM_RECT_MARGIN;
							}
							if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(i + 1, j)) //Right
							{
								vertices2.x -= ROOM_RECT_MARGIN;
								vertices3.x -= ROOM_RECT_MARGIN;
							}
							if (roomNum != GET_STAGE_MANAGER()->getFloorDataByIdx(i, j - 1)) //Down
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
						roomRect->setPosition(Point(i * scale, j * scale));

						bgRect->addChild(roomRect, 25);
					}
				}
			}
		}
	}
}


void Minimap::showMinimapWin()
{
	Sprite* sprMM = (Sprite*)this->getChildByTag(MINIMAP);
	Sprite* sprMMWinContainer = (Sprite*)this->getChildByTag(MINIMAP_WIN);
	Sprite* sprMMWinOpen = (Sprite*)sprMM->getChildByTag(MINIMAP_WIN_OPEN);
	Sprite* sprMMWinClose = (Sprite*)sprMMWinContainer->getChildByTag(MINIMAP_WIN_CLOSE);
	


	sprMMWinContainer->setVisible(true);
	sprMMWinOpen->setVisible(false);
	sprMMWinClose->setVisible(true);
	m_MMWinOn = true;
}

void Minimap::hideMinimapWin()
{
	Sprite* sprMinimap = (Sprite*)this->getChildByTag(MINIMAP);
	Sprite* sprMinimapWinContainer = (Sprite*)this->getChildByTag(MINIMAP_WIN);
	Sprite* sprMinimapWinOpen = (Sprite*)sprMinimap->getChildByTag(MINIMAP_WIN_OPEN);
	Sprite* sprMinimapWinClose = (Sprite*)sprMinimapWinContainer->getChildByTag(MINIMAP_WIN_CLOSE);

	sprMinimapWinContainer->setVisible(false);
	sprMinimapWinOpen->setVisible(true);
	sprMinimapWinClose->setVisible(false);
	m_MMWinOn = false;
}

cocos2d::DrawNode* Minimap::createBgRect(int scale)
{
	auto bgRect = DrawNode::create();
	Vec2 points[] =
	{
		Vec2(0, m_fd.height *  scale),
		Vec2(m_fd.width *  scale, m_fd.height *  scale),
		Vec2(m_fd.width *  scale, 0),
		Vec2(0, 0),
	};
	bgRect->drawPolygon(points, 4, Color4F(Color4B(100, 20, 20, 0)), 0, Color4F(1.0f, 0.3f, 0.3f, 1)); //Color4F(Rf, Gf, Bf, Opacityf) or Color4F(Color4B(Rb, Gb, Bb, Opacityb))
	bgRect->setAnchorPoint(Point(0.5, 0.5));
	return bgRect;
}

// 	Rect testRect = Rect(0, 0, 50, 50);
// 	m_MinimapFrame = SpriteFrame::create("Minimap_Frame.png", testRect);
