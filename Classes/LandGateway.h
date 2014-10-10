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
	cocos2d::Point		findNextPosition();
	Direction			findCentinelNeighborDir(cocos2d::Vec2 stageIdx);
	Direction			findCentinelNeighborDir( cocos2d::Vec2 stageIdx , int stageNum );
	Direction			findReverseDirection(Direction dir);
	cocos2d::Vec2		findNeighbor( cocos2d::Vec2 Idx , Direction dir );
	cocos2d::Point		adjustSettingPosition( cocos2d::Vec2 Idx , Direction dir );
	bool				IsOpen() {return m_isOpen; }
	CREATE_FUNC( LandGateway );

private:
	Direction			m_NextDirection;
	int					m_CurStageNum;
	int					m_NextFloorNum;
	cocos2d::Point		m_LinkingPoint;
	cocos2d::Vec2		m_NextFloorIdx;
	cocos2d::Animation*	m_OpenAnimaion;
	cocos2d::Animation*	m_ActivateAnimation;
	bool				m_isOpen;
	bool				m_IsActive;
};
