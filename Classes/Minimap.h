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
	void							showMinimapWin();
	void							hideMinimapWin();
	bool							getMinimapWinOn() { return m_MMWinOn; }
	cocos2d::Rect					getWinOpenRect();
	cocos2d::Rect					getWinCloseRect();

	CREATE_FUNC(Minimap);

private:
	int								m_WinWidth, m_WinHeight;
	cocos2d::DrawNode*				m_MMBgRect;
	cocos2d::DrawNode*				m_MMWBgRect;
	FloorData						m_fd;
	std::vector<int>				m_VisitedRoom;

	bool							m_MMWinOn;

	void							drawRoomRect(cocos2d::DrawNode* bgRect, int scale);
	cocos2d::DrawNode*				createBgRect(int scale);

	enum MiniMapEnum
	{
		MINIMAP,
		MINIMAP_PLAYER,
		MINIMAP_BGRECT,
		MINIMAP_WIN,
		MINIMAP_WIN_BGRECT,
		MINIMAP_WIN_PLAYER,
		MINIMAP_WIN_OPEN,
		MINIMAP_WIN_CLOSE,
	};
};

