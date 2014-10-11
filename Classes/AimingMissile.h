//AimingMissile.h
//  
//타겟을 계속 쫓아가는 것은 아님, 처음 미사일이 나갈 때 위차하는 타겟으로 향함.
//
//작성자 : 김성연


#pragma once

#include "cocos2d.h"
#include "Missile.h"

class AimingMissile : public Missile
{
public:
	OVERRIDE bool	 init();
	void			 setAttribute(bool isPlayerMissile, float velocity, cocos2d::Point myPos, cocos2d::Point targetPos, float setDamage);
	OVERRIDE void	 collisionOccured(InteractiveObject* enemy, Directions dir);
	void			 update(float dTime);
	CREATE_FUNC(AimingMissile);
private:
	
};
