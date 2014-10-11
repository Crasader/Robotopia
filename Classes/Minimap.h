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
	bool							getMinimapWinOn() { return m_MinimapWinOn; }


	CREATE_FUNC(Minimap);

private:
	int								m_WinWidth, m_WinHeight;
	cocos2d::DrawNode*				m_MinimapBgRect;
	cocos2d::SpriteFrame*			m_MinimapFrame;
	FloorData						m_fd;
	std::vector<int>				m_VisitedRoom;

	bool							m_MinimapWinOn;

 	void							drawRoomRect(int xidx, int yidx);

	enum MiniMapEnum
	{
		MINIMAP_FRAME,
		MINIMAP_PLAYER,
		MINIMAP_WIN,
		MINIMAP_WIN_OPEN,
		MINIMAP_WIN_CLOSE,
	};
};

