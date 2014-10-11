#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandTurret : public LandObject
{
public:
	OVERRIDE bool		init();
	OVERRIDE void		update(float dTime);
	virtual void		collisionOccured( InteractiveObject* enemy , Directions dir ){};
	bool				isInRange(Point position);

	CREATE_FUNC( LandTurret );
private:
	float			m_AttackSpeed;
	float			m_Range;
	float			m_Damage;
};
