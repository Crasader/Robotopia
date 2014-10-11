#pragma once
#include "cocos2d.h"
#include "Utils.h"

class GameLayer;
class BackgroundLayer;
class UILayer;
class WorldScene : public cocos2d::Scene
{
public:
	static WorldScene*			createScene();
	void						initCurrentSceneWithData( cocos2d::Vec2 boxNum , cocos2d::Size boxSize ,
												 std::map<int , ObjectType> mapData , char* BGpath );
	virtual bool				init();
	GameLayer*					getGameLayer() {return m_GameLayer; }
	UILayer*					getUILayer() {return m_UILayer; }
	CREATE_FUNC( WorldScene );

private:
	enum ZOrder
	{
		BACKGROUND ,
		GAMELAYER ,
		UILAYER ,
	};
	GameLayer*			m_GameLayer;
	BackgroundLayer*	m_BackgroundLayer;
	UILayer*			m_UILayer;
};
