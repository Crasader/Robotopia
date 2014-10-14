#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Player.h"

class Minimap;
class WorldMenu;
class EquipmentWindow;
class BarContainer;
class Gear;

class UILayer : public cocos2d::Layer
{
public:
	virtual bool			init();
	void					update( float dTime );

	CREATE_FUNC( UILayer );

	void					initializeUILayer();

protected:

	int									m_WinWidth , m_WinHeight;
	
	BarContainer*						m_BarContainer;
	EquipmentWindow*					m_EquipmentWindow;
	Minimap*							m_Minimap;
	WorldMenu*							m_WorldMenu;
	Gear*								m_Gear;

	bool								m_IsMouseDown;
	void								onMouseDown(cocos2d::Event *event);
	void								onMouseUp(cocos2d::Event *event);
	void								onMouseMove(cocos2d::Event *event);
	void								onMouseScroll(cocos2d::Event *event);

};
