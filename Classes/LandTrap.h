#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandTrap : public LandObject
{
public:
	OVERRIDE bool		init();
	OVERRIDE void		update( float dTime );
	virtual void		collisionOccured( InteractiveObject* enemy , Directions dir ){};
	bool				isActive() {return m_IsActive; }
	void				endAnimation( cocos2d::Ref* sender );
	CREATE_FUNC( LandTrap );

private:
	bool				m_IsActive;
	Animation*			m_ActivateAnimation;
};
