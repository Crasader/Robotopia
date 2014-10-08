//LinearMissile.h
//
//일직선으로 나가는 미사일  
//
//
//작성자 : 김성연


#pragma once

#include "cocos2d.h"
#include "Missile.h"

class LinearMissile : public Missile
{
public:
	OVERRIDE bool init();
	void		  update(float dTime);
	void		  setMoveAttribute(bool m_IsPlayerMissile, float velocity, float degree);

	CREATE_FUNC(LinearMissile);

private:
	
};