//LinearMissile.h
//
//���������� ������ �̻���  
//
//
//�ۼ��� : �輺��

#pragma once

#include "Missile.h"
#include "cocos2d.h"

class MeleeMissile : public Missile
{
public:
	OVERRIDE bool   init();
	void		    update(float dTime);
	OVERRIDE void	collisionOccured(InteractiveObject* enemy, Directions dir);
	void			setAttribute(bool m_IsPlayerMissile, float velocity, float degree, float setDamage);
	CREATE_FUNC(MeleeMissile);
private:
	void			isDestroyedToTureAfterAni();


};