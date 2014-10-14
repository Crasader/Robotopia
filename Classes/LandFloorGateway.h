#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandFloorGateway : public LandObject
{
public:
	OVERRIDE bool		init();
	virtual void		collisionOccured( InteractiveObject* enemy , Directions dir );
	void				gotoNextFloor(cocos2d::Ref* sender);
	CREATE_FUNC( LandFloorGateway );

private:
	cocos2d::Animation*		m_OpenAnimation;
	bool					m_IsOpen;
};
