//Missile.h
//
//게임에서 사용하는 모든 미사일의 상위 클래스 
//플레이어 미사일인지, 충돌시  m_IsDestroyed 변환 여부 조건에 따라 체크구현
//
//작성자 : 김성연
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