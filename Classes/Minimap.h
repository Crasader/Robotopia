//Minimap.h
//
//Minimap
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class Minimap : public UILayer
{
public:
	static cocos2d::Scene*			createScene();
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(Minimap);

private:


};