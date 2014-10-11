//Minimap.h
//
//Minimap
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "DataManager.h"

class Minimap : public cocos2d::Node
{
public:
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(Minimap);

private:
	int								m_WinWidth, m_WinHeight;
	cocos2d::DrawNode*				m_MinimapBgRect;
	cocos2d::SpriteFrame*					m_MinimapFrame;
	FloorData						m_fd;
	std::vector<int>				m_VisitedRoom;

 	void							drawRoomRect(int xidx, int yidx);

	enum MiniMapEnum
	{
		MINIMAP_PLAYER,
	};
};

