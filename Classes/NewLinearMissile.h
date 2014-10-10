//NewLinearMissile.h
//
//일직선으로 나가는 미사일  
//
//
//작성자 : 김성연


#pragma once

#include "cocos2d.h"
#include "Missile.h"

class NewLinearMissile : public Missile
{
public:
	OVERRIDE bool   init();
	void		    update(float dTime);
	void		    setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree);
	OVERRIDE void	collisionOccured(InteractiveObject* enemy, Directions dir);
	CREATE_FUNC(NewLinearMissile);

private:

};

