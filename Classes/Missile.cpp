#include "Missile.h"
#include "GameManager.h"


bool Missile::init()
{
	if (!InteractiveObject::init())
	{
		return false;
	}

	//타입 추가 되면 여기 활성화

	m_Degree = 0;
	m_IsOnGravity = false;


	return true;
}

void Missile::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	m_IsPlayerMissile = IsPlayerMissile();


	//플레이어 미사일과 몬스터 미사일을 구분지어서 사라지는 부분
	if (m_IsPlayerMissile)
	{
		switch (enemy->getType())
		{
		case OT_MONSTER:
			m_IsDestroyed = true;
			break;
		case OT_RUSH_MONSTER:
			m_IsDestroyed = true;

			break;
		}
	}
	else
	{
		switch (enemy->getType())
		{
		case OT_PLAYER:
			m_IsDestroyed = true;
			break;
		}
	}


	//플레이어 미사일이든 몬스터 미사일이든 공통으로 충돌했을 때 사라지는 부분
	switch (enemy->getType())
	{
	case OT_FLOOR:
		m_IsDestroyed = true;
		break;
	case OT_BLOCK:
		m_IsDestroyed = true;
		break;

	case OT_VILLAGER:

		m_IsDestroyed = true;
		break;
	}

	if (m_IsDestroyed)
	{
		GET_EFFECT_MANAGER()->createEffect(ET_AIMING_MISSILE_COLLISION, enemy->getRect(), this->getRect(), dir, 1);
	}

}



