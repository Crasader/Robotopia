#pragma once
#include "cocos2d.h"
#include "Utils.h"

class KeyStateSentinel;
class GameLayer;
class BackgroundLayer;
class UILayer;
class WorldScene : public cocos2d::Scene
{
public:
	static WorldScene*			createScene();
	void						initCurrentSceneWithData( cocos2d::Vec2 boxNum , cocos2d::Size boxSize ,
												 std::map<int , ObjectType> mapData , char* BGpath );
	OVERRIDE bool				init();
	void						update(float dTime);
	void						onEnter();
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
	float				m_ShakeTime;
	GameLayer*			m_GameLayer;
	BackgroundLayer*	m_BackgroundLayer;
	UILayer*			m_UILayer;
	KeyStateSentinel*	m_KeySentinel;
};
