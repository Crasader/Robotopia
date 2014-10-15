#pragma once
#include "cocos2d.h"
#include "Utils.h"

class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	OVERRIDE bool			init();
	void					menuCallback( Ref* sender );
	CREATE_FUNC( MenuScene );
};
