#include "Missile.h"



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
