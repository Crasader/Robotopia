//Missile.h
//
//���ӿ��� ����ϴ� ��� �̻����� ���� Ŭ���� 
//�÷��̾� �̻�������, �浹��  m_IsDestroyed ��ȯ ���� ���ǿ� ���� üũ����
//
//�ۼ��� : �輺��
//

#pragma once

#include "cocos2d.h"
#include "InteractiveObject.h"
#define PIE 3.141592

class Missile : public InteractiveObject
{
public:
	OVERRIDE bool	init();
	bool			IsPlayerMissile(){ return m_IsPlayerMissile; }
	void			collisionOccured(InteractiveObject* enemy, Directions dir);
	
protected:
	bool    m_IsPlayerMissile;
	float	m_Degree;
	
};