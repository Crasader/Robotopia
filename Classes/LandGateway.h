#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandGateway : public LandObject
{
public:
	OVERRIDE bool		init();
	OVERRIDE void		collisionOccured( InteractiveObject* enemy , Directions dir );
	void				gotoNextLevel( Ref* sender );
	void				findNextStage();
	Direction			findCentinelNeighborDir(cocos2d::Vec2 stageIdx);
	cocos2d::Vec2		findNeighbor( cocos2d::Vec2 Idx , Direction dir );
	bool				IsOpen() {return m_isOpen; }
	CREATE_FUNC( LandGateway );

private:
	int					m_NextFloorNum;
	cocos2d::Vec2		m_NextFloorIdx;
	cocos2d::Animation*	m_OpenAnimaion;
	cocos2d::Animation*	m_ActivateAnimation;
	bool				m_isOpen;
	bool				m_IsActive;
};
