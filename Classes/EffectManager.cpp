#include "EffectManager.h"
#include "GameManager.h"
#include "GameLayer.h"
USING_NS_CC;


bool EffectManager::init()
{
	effectSpr = Sprite::create();
	return true;
}

void EffectManager::removeSprAfterAni(Ref* sender)
{
	auto spr = (Sprite*)sender;
	spr->removeFromParent();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectManager::createEffect(EffectType selectedEffect, cocos2d::Rect enemyRect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		createEffectLinearMissileCollision(enemyRect, ownRect, collisionDir, effectPlayNum);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
}


void EffectManager::createEffect(EffectType selectedEffect, Point enemyPoint, Size enemySize, Point ownPoint, Size ownSize,
								 Directions collisionDir, int effectPlayNum)
{
	Rect enemyRect(enemyPoint.x, enemyPoint.y, enemySize.width, enemySize.height);
	Rect ownRect(ownPoint.x, ownPoint.y, ownSize.width, ownSize.width);
	createEffect(selectedEffect, enemyRect, ownRect, collisionDir, effectPlayNum);
	return;
}

//EndLine////////////////////////////////////////////////

void EffectManager::createEffectSelectedSizeByUser(EffectType selectedEffect, Rect effectRect, int effectPlayNum)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		createEffectLinearMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		break;
	case ET_PLAYER_FLOOR_COLLISION:
		break;

	}
	return;
}


void EffectManager::createEffectSelectedSizeByUser(EffectType selectedEffect, Point effectPoint, Size effectSize, int effectPlayNum)
{
	Rect effectRect(effectPoint.x, effectPoint.y, effectSize.width, effectSize.height);
	createEffectSelectedSizeByUser(selectedEffect, effectRect, effectPlayNum);
	return;
}

//EndLine///////////////////////////////////////////////


void EffectManager::createEffectLinearMissileCollision(cocos2d::Rect enemyRect, Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 1.5f;
	
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.2f);

	float ratioX = ownRect.size.width / effectSpr->getContentSize().width;
	float ratioY = ownRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);
	

	float setPosX = 0;
	float setPosY = 0;

	//발사된 녀석의 면을 중심으로 하기 때문에
	//만나는 애들이 포지션에 대한 앵커포인터가 0,0으로 되어 있다. 
	switch (collisionDir)
	{
	case DIR_UP:
		setPosX = ownRect.origin.x + (ownRect.size.width/2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_DOWN:
		setPosX = ownRect.origin.x + (ownRect.size.width/2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_LEFT:
		setPosX = ownRect.origin.x;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_RIGHT:
		setPosX = ownRect.origin.x + ownRect.size.width;
		setPosY = ownRect.origin.y + (ownRect.size.height/2);
		break;
	}

	
	effectSpr->setPosition(setPosX, setPosY);
	auto WorldScene = GET_STAGE_MANAGER()->getWorldScene();
	WorldScene->getGameLayer()->addEffect(effectSpr);

	auto action = Repeat::create(Animate::create(m_MainAnimation), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}



void EffectManager::createEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 2.0f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	m_MainAnimation = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.1f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX);
	effectSpr->setScaleY(ratioY);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	effectSpr->runAction(Repeat::create(Animate::create(m_MainAnimation), effectPlayNum));


	return;
}



