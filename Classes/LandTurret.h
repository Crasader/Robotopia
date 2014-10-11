#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandTurret : public LandObject
{
public:
	OVERRIDE bool		init();
	OVERRIDE void		update(float dTime);
	virtual void		collisionOccured( InteractiveObject* enemy , Directions dir )
	{
	};

	CREATE_FUNC( LandTurret );
private:
	float			m_AttackSpeed;
};
