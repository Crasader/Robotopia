#include "EffectManager.h"
#include "GameManager.h"
USING_NS_CC;


bool EffectManager::init()
{
	m_MainSprite = Sprite::create();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::useEffect(EffectType selectedEffect, Rect obRect, int effectPlayNum, Point AnchorPoint, Vec2 velocity)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		useEffectLinearMissileCollision(obRect, effectPlayNum, AnchorPoint, velocity);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
}


void EffectManager::useEffect(EffectType selectedEffect, Point obPoint, Size obSize, int effectPlayNum, Point AnchorPoint, Vec2 velocity)
{
	Rect obRect(obPoint.x, obPoint.y, obSize.width, obSize.height);
	useEffect(selectedEffect, obRect, effectPlayNum, AnchorPoint, velocity);
	return;
}

//EndLine////////////////////////////////////////////////

void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, Rect effectRect, int effectPlayNum)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		useEffectLinearMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
	return;
}


void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, Point effectPoint, Size effectSize, int effectPlayNum)
{
	Rect effectRect(effectPoint.x, effectPoint.y, effectSize.width, effectSize.height);
	useEffectSelectedSizeByUser(selectedEffect, effectRect, effectPlayNum);
	return;
}

//EndLine///////////////////////////////////////////////

void EffectManager::useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, Point AnchorPoint, Vec2 velocity)
{
	float needEffectScale = 0.5;
	
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.1f);

	float ratioX = obRect.size.width / m_MainSprite->getContentSize().width;
	float ratioY = obRect.size.height / m_MainSprite->getContentSize().height;
	
	m_MainSprite->setScaleX(ratioX * needEffectScale);
	m_MainSprite->setScaleY(ratioY * needEffectScale);

	float addPosX, addPosY;
	//�̰� ����Ʈ���� anchorPoint�� ������ �ʾ��� �� �⺻���� �����ġ�� ������ ���ΰ��� �ٸ���. 
	//��Ŀ����Ʈ default ���� -1�� ���� ���̱� ������ 0���� ������ ���� ������ ��ġ�� �׷�����. 
	if (AnchorPoint.x < 0 || AnchorPoint.y < 0)
	{
		//LinearMissileCollision���� ���� �̻��� �տ��� �߰��� �׷����� �ϰ� ��Ǫ��
		if (velocity.x >0)
		{
			addPosX = obRect.origin.x + 0.25f * obRect.size.width;
			addPosY = obRect.origin.y + 0.25f * obRect.size.height;
		}
		else if (velocity.x == 0)
		{
			addPosX = 0;
			addPosY = 0;
		}
		else
		{
			addPosX = obRect.origin.x - 0.25f * obRect.size.width;
			addPosY = obRect.origin.y - 0.25f * obRect.size.height;
		}
	}
	else
	{
		addPosX = obRect.origin.x + (AnchorPoint.x - 0.5) * obRect.size.width;
		addPosY = obRect.origin.y + (AnchorPoint.y - 0.5) * obRect.size.height;
	}
	
	m_MainSprite->setPosition(addPosX, addPosY);
	m_MainSprite->runAction(Repeat::create(Animate::create(m_MainAnimation), effectPlayNum));

	return;
}

void EffectManager::useEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 0.5;

	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.1f);

	float ratioX = effectRect.size.width / m_MainSprite->getContentSize().width;
	float ratioY = effectRect.size.height / m_MainSprite->getContentSize().height;

	m_MainSprite->setScaleX(ratioX);
	m_MainSprite->setScaleY(ratioY);

	m_MainSprite->setPosition(effectRect.origin.x, effectRect.origin.y);
	m_MainSprite->runAction(Repeat::create(Animate::create(m_MainAnimation), effectPlayNum));


	return;
}


