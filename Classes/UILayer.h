#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Player.h"

class Minimap;
class WorldMenu;
class EquipmentWindow;
class BarContainer;
class Gear;
class StoreWindow;

class UILayer : public cocos2d::Layer
{
public:
	virtual bool			init();
	void					update( float dTime );

	CREATE_FUNC( UILayer );

	void					initializeRobotSetting();
	void					initializeUILayer();
	
	void					showStore();
	void					hideStore();

protected:

	int									m_WinWidth , m_WinHeight;
	
	BarContainer*						m_BarContainer;
	EquipmentWindow*					m_EquipmentWindow;
	Minimap*							m_Minimap;
	WorldMenu*							m_WorldMenu;
	Gear*								m_Gear;
	StoreWindow*						m_StoreWindow;

	bool								m_IsMouseDown;

	bool								m_DragOn;
	cocos2d::Sprite*					m_DragItem;
	cocos2d::Point						m_prevPoint;
	cocos2d::Sprite*					m_TestItem;

	cocos2d::Rect						getRectWithVertice(float v1, float v2, float v3, float v4);
	void								onMouseDown(cocos2d::Event *event);
	void								onMouseDown2(cocos2d::Event *event);
	void								onMouseUp(cocos2d::Event *event);
	void								onMouseUp2(cocos2d::Event *event);
	void								onMouseMove(cocos2d::Event *event);
	void								onMouseMove2(cocos2d::Event *event);
	void								onMouseScroll(cocos2d::Event *event);
};
