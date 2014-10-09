#pragma once
#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	void					menuCallback( Ref* sender );
	CREATE_FUNC( MenuScene );
};
