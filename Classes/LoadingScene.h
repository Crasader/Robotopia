#pragma once
#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	virtual void			update(float dTime);
	CREATE_FUNC( LoadingScene );

private:
	bool		m_Mutex;
};
