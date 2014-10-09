//WorldMenu.h
//
//WorldScene에서 ESC 입력 시 뜨는 WorldMenu
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class WorldMenu : public UILayer
{
public:
	static cocos2d::Scene*			createScene();
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(WorldMenu);

	void							showWorldMenu();
	void							hideWorldMenu();

private:


};