//WorldMenu.h
//
//WorldScene���� ESC �Է� �� �ߴ� WorldMenu
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"
#include "UILayer.h"
#include "WorldScene.h"

class WorldMenu : public UILayer
{
public:
	virtual bool					init();
	void							update(float dTime);

	CREATE_FUNC(WorldMenu);

	void							showWorldMenu();
	void							hideWorldMenu();

private:


};