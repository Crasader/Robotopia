#pragma once
#include "cocos2d.h"
#include "Utils.h"

class LoadingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	OVERRIDE bool			init();
	void					initGame(float unused);
	CREATE_FUNC( LoadingScene );

private:
	bool		m_Mutex;
};
