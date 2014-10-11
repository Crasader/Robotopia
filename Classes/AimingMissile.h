//AimingMissile.h
//  
//Ÿ���� ��� �Ѿư��� ���� �ƴ�, ó�� �̻����� ���� �� �����ϴ� Ÿ������ ����.
//
//�ۼ��� : �輺��


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
