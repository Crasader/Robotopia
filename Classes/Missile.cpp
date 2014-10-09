#include "Missile.h"
#include "GameManager.h"


bool Missile::init()
{
	if (!InteractiveObject::init())
	{
		return false;
	}

	//Ÿ�� �߰� �Ǹ� ���� Ȱ��ȭ

	m_Degree = 0;
	m_IsOnGravity = false;


	return true;
}

void Missile::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	m_IsPlayerMissile = IsPlayerMissile();


	//�÷��̾� �̻��ϰ� ���� �̻����� ������� ������� �κ�
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


	//�÷��̾� �̻����̵� ���� �̻����̵� �������� �浹���� �� ������� �κ�
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



