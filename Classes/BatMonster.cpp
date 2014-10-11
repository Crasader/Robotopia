#include "BatMonster.h"
#include"GameManager.h"


USING_NS_CC;

bool BatMonster::init()
{
	if (!Monster::init())
	{
		return false;
	}

	m_Type = OT_BAT_MONSTER;

	m_Animations[BM_FIND] = GET_RESOURCE_MANAGER()->createAnimation(AT_MONSTER_BAT);
	m_Animations[BM_ATTACK] = GET_RESOURCE_MANAGER()->createAnimation(AT_MONSTER_BAT);

	m_AnimationNum = BM_STATE_NUM;


	m_MainSprite = Sprite::create();

	this->addChild(m_MainSprite);
	m_MoveSpeed = 30;
	m_IsOnGravity = true;

	m_Info.maxHp = 100;
	m_Info.hp = m_Info.maxHp;

	return true;
}

void BatMonster::collisionOccured(InteractiveObject* enemy, Directions dir)
{

}

void BatMonster::update(float dTime)
{

}
