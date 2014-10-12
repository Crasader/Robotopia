#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandTrap : public LandObject
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update( float dTime );
	virtual void			collisionOccured( InteractiveObject* enemy , Directions dir ){};
	bool					isActive();
	OVERRIDE cocos2d::Rect	getRect();
	void					endAnimation( cocos2d::Ref* sender );
	CREATE_FUNC( LandTrap );

private:
	timeval					m_InitTime;
	cocos2d::Animation*		m_ActivateAnimation;
};
