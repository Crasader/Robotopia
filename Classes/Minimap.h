//Minimap.h
//
//Minimap
//
//작성자 : 우재우
//

#pragma once
#include "cocos2d.h"
#include "WorldScene.h"
#include "UILayer.h"

class Minimap : public UILayer
{
public:
	static cocos2d::Scene*			createScene();
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(Minimap);

private:


};