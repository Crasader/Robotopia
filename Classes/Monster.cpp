#include "Monster.h"

bool Monster::init()
{
	if (!InteractiveObject::init())
	{
		return false;
	}

	m_Type = OT_MONSTER;
	m_IsOverlapable = false;

	return true;
}