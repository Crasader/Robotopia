#include "EffectManager.h"
#include "GameManager.h"
USING_NS_CC;





bool EffectManager::init()
{
	m_MainSprite = Sprite::create();
	return true;
}

void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Rect obRect, int effectPlayNum, Point AnchorPoint)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		useEffectLinearMissileCollision(obRect, effectPlayNum, AnchorPoint);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
}


void EffectManager::useEffect(EffectType selectedEffect, cocos2d::Point obPoint, cocos2d::Size obSize, int effectPlayNum, Point AnchorPoint)
{
	Rect obRect(obPoint.x, obPoint.y, obSize.width, obSize.height);
	useEffect(selectedEffect, obRect, effectPlayNum, AnchorPoint);
	return;
}

void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Rect effectRect, int effectPlayNum, cocos2d::Point AnchorPoint)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		//useEffectLinearMissileCollision(obRect, effectPlayNum, AnchorPoint);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
	return;
}

void EffectManager::useEffectSelectedSizeByUser(EffectType selectedEffect, cocos2d::Point effectPoint, 
												cocos2d::Size effectSize, int effectPlayNum, cocos2d::Point AnchorPoint)
{
	Rect effectRect(effectPoint.x, effectPoint.y, effectSize.width, effectSize.height);
	useEffectSelectedSizeByUser(selectedEffect, effectRect, effectPlayNum, AnchorPoint);
	return;
}


void EffectManager::useEffectLinearMissileCollision(cocos2d::Rect obRect, int effectPlayNum, Point AnchorPoint)
{
	float needEffectScale = 0.5;
	
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite("ETLinearMissileCollision1.png");
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation("ETLinearMissileCollision%d.png", 1, 9, 0.1f);

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
		addPosX = obRect.origin.x + 0.25f * obRect.size.width;
		addPosY = obRect.origin.y + 0.25f * obRect.size.height;
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


