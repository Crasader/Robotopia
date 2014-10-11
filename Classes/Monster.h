//Monster.h
//
// 모든 몬스터들의 최상위 클래스.
//
//작성자 : 남현욱
//
#pragma once
#include "InteractiveObject.h"

struct MonsterInfo
{
	int hp;
	int maxHp;
};

class Monster : public InteractiveObject
{
public:
	OVERRIDE bool			init();
	ABSTRACT void			collisionOccured(InteractiveObject* enemy, Directions dir) = 0;
	MonsterInfo				getInfo(){ return m_Info; }
	int						getHp() { return m_Info.hp; }
	int						getMaxHp() { return m_Info.maxHp; }
	void					setHp(int hp, bool isRelative = false) { if (!isRelative) m_Info.hp = hp; else m_Info.hp += hp; }
	void					setMaxHp(int maxHp, bool isRelative = false) { if (!isRelative) m_Info.maxHp = maxHp; else m_Info.maxHp += maxHp; }

protected:
	MonsterInfo				m_Info;
};