//Minimap.h
//
//Minimap
//
//�ۼ��� : �����
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
	cocos2d::Sprite*				m_sprMinimapWinTrigger;
	cocos2d::Sprite*				m_sprMinimapWinContainer;

 	void							drawRoomRect(int xidx, int yidx);

	enum MiniMapEnum
	{
		MINIMAP_PLAYER,
	};
};

