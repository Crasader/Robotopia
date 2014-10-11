//LinearMissile.h
//
//���������� ������ �̻���  
//
//
//�ۼ��� : �輺��


#pragma once

#include "cocos2d.h"
#include "Missile.h"

class LinearMissile : public Missile
{
public:
	OVERRIDE bool   init();
	void		    update(float dTime);
	void		    setAttribute(bool m_IsPlayerMissile, float velocity, float degree, float setDamage);
	OVERRIDE void	collisionOccured(InteractiveObject* enemy, Directions dir);
	CREATE_FUNC(LinearMissile);

private:
	
};