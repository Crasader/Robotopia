#pragma once
#include "cocos2d.h"
#include "WorldScene.h"
#include "Player.h"

class UILayer : public WorldScene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	CREATE_FUNC(UILayer);

	void update(float dTime);

private:
	enum UILayerEnum
	{
		LABEL_HPSTATUS,
		LABEL_STEAMSTATUS,
		SPRITE_FOREHP,
		SPRITE_BACKHP,
	};

	const Player*						m_Player;
	int									m_WinWidth, m_WinHeight;
	int									m_prevHP;
	cocos2d::Vector<cocos2d::Sprite*>	m_STEs;
	
	//void							setMaxHP(int maxHP); 혹시 피통이 늘어날 수도 있으니까
	void							drawCurrentHP(int currentHP, int maxHP);
	void							setMaxSTE(int maxSTE);
	void							drawCurrentSTE(int currentSTE);
	void							setLabels(int currentHP, int maxHP, int currentSTE, int maxSTE);
};