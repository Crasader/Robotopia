//StoryWindow.h
//
//NPC StroyTeller�� UI ����
//
//�ۼ��� : �����
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

class StoryWindow : public cocos2d::Node
{
public:
	virtual bool		init();
	void				update(float dTime);

	CREATE_FUNC(StoryWindow);

private:

};