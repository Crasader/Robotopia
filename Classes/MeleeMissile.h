//LinearMissile.h
//
//일직선으로 나가는 미사일  
//
//
//작성자 : 김성연

#pragma once

#include "Missile.h"
#include "cocos2d.h"

class MeleeMissile : public Missile
{
public:
	OVERRIDE bool   init();
	void		    update(float dTime);
	OVERRIDE void	collisionOccured(InteractiveObject* enemy, Directions dir);
	void			setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree);
	CREATE_FUNC(MeleeMissile);
private:
	void			isDestroyedToTureAfterAni();


};