//NewLinearMissile.h
//
//���������� ������ �̻���  
//
//
//�ۼ��� : �輺��


#pragma once

#include "cocos2d.h"
#include "Missile.h"

class NewLinearMissile : public Missile
{
public:
	OVERRIDE bool   init();
	void		    update(float dTime);
	void		    setAttribute(bool isPlayerMissile, float velocity, float degree, float setDamage);
	OVERRIDE void	collisionOccured(InteractiveObject* enemy, Directions dir);
	CREATE_FUNC(NewLinearMissile);

private:

};

