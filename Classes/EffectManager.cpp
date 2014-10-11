#include "EffectManager.h"
#include "GameManager.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;


bool EffectManager::init()
{
	m_IsOnBGM = false;
	SimpleAudioEngine::getInstance()->preloadEffect("MeleeMissile1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("SteamGet.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("jump.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM1.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM2.mp3");
	
	return true;
}

void EffectManager::removeSprAfterAni(Ref* sender)
{
	auto spr = (Sprite*)sender;
	spr->removeFromParent();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectManager::createEffect(EffectType selectedEffect, cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	switch (selectedEffect)
	{
	case ET_LINEAR_MISSILE_COLLISION:
		createEffectLinearMissileCollision( ownRect, collisionDir, effectPlayNum);
		break;
	case ET_AIMING_MISSILE_COLLISION:
		createEffectAimingMissileCollision( ownRect, collisionDir, effectPlayNum);
		break;
	case ET_MELEE_MISIILE_COLLSION:
		createEffectMeleeMissileCollision(ownRect, collisionDir, effectPlayNum);
		break;
	case ET_NEW_LINEAR_MISSILE_COLLISION:
		createEffectNewLinearMissileCollsion(ownRect, collisionDir, effectPlayNum);
		break;
	case ET_PLAYER_LANDING:
		createEffectPlayerLanding(ownRect, collisionDir, effectPlayNum);
		break;

	}
}


void EffectManager::createEffect(EffectType selectedEffect, Point ownPoint, Size ownSize, Directions collisionDir, int effectPlayNum)
{
	
	Rect ownRect(ownPoint.x, ownPoint.y, ownSize.width, ownSize.width);
	createEffect(selectedEffect, ownRect, collisionDir, effectPlayNum);
	return;
}

//EndLine////////////////////////////////////////////////

void EffectManager::createEffectSelectedSizeByUser(EffectType selectedEffect, Rect effectRect, int effectPlayNum)
{
	if (effectRect.size.width >= 0)
	{
		switch (selectedEffect)
		{
		case ET_LINEAR_MISSILE_COLLISION:
			createEffectLinearMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
			break;
		case ET_AIMING_MISSILE_COLLISION:
			createEffectAimingMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
			break;
		case ET_MELEE_MISIILE_COLLSION:
			createEffectMeleeMissileCollisionByUser(effectRect, effectPlayNum);
			break;
		case ET_NEW_LINEAR_MISSILE_COLLISION:
			createEffectNewLinearMissileCollsionByUser(effectRect, effectPlayNum);
			break;
		case ET_PLAYER_LANDING:
			createEffectPlayerLandingSizeByUser(effectRect, effectPlayNum);
		case ET_ROUND_SMOKE:
			createEffectRoundSmokeByUser(effectRect, effectPlayNum);

		}
	}
	else
	{
		switch (selectedEffect)
		{
		case ET_LINEAR_MISSILE_COLLISION:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION)->getContentSize();
			createEffectLinearMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
			break;
		case ET_AIMING_MISSILE_COLLISION:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_AIMINGMISSILE_COLLISION)->getContentSize();
			createEffectAimingMissileCollisionSelectedSizeByUser(effectRect, effectPlayNum);
			break;
		case ET_MELEE_MISIILE_COLLSION:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_MELEE_MISSILE_COLLISION)->getContentSize();
			createEffectMeleeMissileCollisionByUser(effectRect, effectPlayNum);
			break;
		case ET_NEW_LINEAR_MISSILE_COLLISION:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_NEW_LINEAR_MISSILE_COLLISION)->getContentSize();
			createEffectNewLinearMissileCollsionByUser(effectRect, effectPlayNum);
			break;
		case ET_PLAYER_LANDING:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_PLAYER_LANDING)->getContentSize();
			createEffectPlayerLandingSizeByUser(effectRect, effectPlayNum);
		case ET_ROUND_SMOKE:
			effectRect.size = GET_RESOURCE_MANAGER()->createSprite(ST_ROUND_SMOKE)->getContentSize();
			createEffectRoundSmokeByUser(effectRect, effectPlayNum);
		}
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


void EffectManager::createEffectLinearMissileCollision(Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 1.0f;
	
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.05f);
		

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
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}



void EffectManager::createEffectLinearMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 1.0f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_LINEARMISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_LINEARMISSILE_COLLISION, 0.1f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);

	auto WorldScene = GET_STAGE_MANAGER()->getWorldScene();
	WorldScene->getGameLayer()->addEffect(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));


	return;
}

void EffectManager::createEffectAimingMissileCollision(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 1.5f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_AIMINGMISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_AIMINGMISSILE_COLLISION, 0.2f);

	float ratioX = ownRect.size.width / effectSpr->getContentSize().width;
	float ratioY = ownRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);


	float setPosX = 0;
	float setPosY = 0;

	switch (collisionDir)
	{
	case DIR_UP:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_DOWN:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_LEFT:
		setPosX = ownRect.origin.x;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_RIGHT:
		setPosX = ownRect.origin.x + ownRect.size.width;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	}


	effectSpr->setPosition(setPosX, setPosY);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}

void EffectManager::createEffectAimingMissileCollisionSelectedSizeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{

	float needEffectScale = 1.0f;
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_AIMINGMISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_AIMINGMISSILE_COLLISION, 0.2f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));
}

void EffectManager::createEffectPlayerLanding(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 1.2f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_PLAYER_LANDING);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_LANDING, 0.05f);

	float ratioX = ownRect.size.width / effectSpr->getContentSize().width;
	float ratioY = ownRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);


	float setPosX = 0;
	float setPosY = 0;

	switch (collisionDir)
	{
	case DIR_NONE :
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_UP:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_DOWN:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height/ 5);
		break;
	case DIR_LEFT:
		setPosX = ownRect.origin.x;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_RIGHT:
		setPosX = ownRect.origin.x + ownRect.size.width;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	}


	effectSpr->setPosition(setPosX, setPosY);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}

void EffectManager::createEffectPlayerLandingSizeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 1.0f;
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_PLAYER_LANDING);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_PLAYER_LANDING, 0.2f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX);
	effectSpr->setScaleY(ratioY);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));
}

void EffectManager::createEffectMeleeMissileCollision(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 0.85f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_MELEE_MISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_MELEE_MISSILE_COLLISION, 0.01f);

	float ratioX = ownRect.size.width / effectSpr->getContentSize().width;
	float ratioY = ownRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);


	float setPosX = 0;
	float setPosY = 0;

	switch (collisionDir)
	{
	case DIR_NONE:
		//이부분에 대한 생각 필요 
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_UP:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_DOWN:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 4);
		break;
	case DIR_LEFT:
		setPosX = ownRect.origin.x;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_RIGHT:
		setPosX = ownRect.origin.x + ownRect.size.width;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	}


	effectSpr->setPosition(setPosX, setPosY);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}

void EffectManager::createEffectMeleeMissileCollisionByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 1.0f;
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_MELEE_MISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_MELEE_MISSILE_COLLISION, 0.01f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));
}

void EffectManager::createEffectNewLinearMissileCollsion(cocos2d::Rect ownRect, Directions collisionDir, int effectPlayNum)
{
	float needEffectScale = 0.7f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_NEW_LINEAR_MISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_NEW_LINEAR_MISSILE_COLLISION, 0.2f);

	float ratioX = ownRect.size.width / effectSpr->getContentSize().width;
	float ratioY = ownRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);


	float setPosX = 0;
	float setPosY = 0;

	switch (collisionDir)
	{
	case DIR_NONE:
		//이부분에 대한 생각 필요 
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_UP:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_DOWN:
		setPosX = ownRect.origin.x + (ownRect.size.width / 2);
		setPosY = ownRect.origin.y;
		break;
	case DIR_LEFT:
		setPosX = ownRect.origin.x;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	case DIR_RIGHT:
		setPosX = ownRect.origin.x + ownRect.size.width;
		setPosY = ownRect.origin.y + (ownRect.size.height / 2);
		break;
	}


	effectSpr->setPosition(setPosX, setPosY);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));

	return;
}

void EffectManager::createEffectNewLinearMissileCollsionByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 1.0f;
	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_NEW_LINEAR_MISSILE_COLLISION);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_NEW_LINEAR_MISSILE_COLLISION, 0.2f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action, callback, NULL));
}

void EffectManager::createEffectRoundSmokeByUser(cocos2d::Rect effectRect, int effectPlayNum)
{
	float needEffectScale = 1.0f;

	auto effectSpr = GET_RESOURCE_MANAGER()->createSprite(ST_ROUND_SMOKE);
	auto effectAni = GET_RESOURCE_MANAGER()->createAnimation(AT_ROUND_SMOKE, 0.05f);

	float ratioX = effectRect.size.width / effectSpr->getContentSize().width;
	float ratioY = effectRect.size.height / effectSpr->getContentSize().height;

	effectSpr->setScaleX(ratioX * needEffectScale);
	effectSpr->setScaleY(ratioY * needEffectScale);

	effectSpr->setPosition(effectRect.origin.x, effectRect.origin.y);
	GET_STAGE_MANAGER()->addEffectOnGameLayer(effectSpr);

	auto action = Repeat::create(Animate::create(effectAni), effectPlayNum);
	auto fadeTo = FadeTo::create(0.3f, 80);
	auto callback = CallFuncN::create(CC_CALLBACK_1(EffectManager::removeSprAfterAni, this));
	effectSpr->runAction(Sequence::create(action,fadeTo, callback, NULL));
}

void EffectManager::createSound(SoundType selectedSound, bool isRepeated)
{
	switch (selectedSound)
	{
	case SO_SCENE1_BGM:
	
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM1.mp3", isRepeated);
		break;
	case SO_SCENE2_BGM:
	
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM2.mp3", isRepeated);
		break;
	case SO_MELEE_MISSILE:
		SimpleAudioEngine::getInstance()->playEffect("MeleeMissile1.wav");
		break;
	case SO_SAGA_BGM:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("saga.mp3", isRepeated);
		break;
	case SO_JUMP:
		SimpleAudioEngine::getInstance()->playEffect("jump.wav");
		break;
	case SO_STEAM_GET:
		SimpleAudioEngine::getInstance()->playEffect("SteamGet.wav");
		break;
	case SO_AIMING_MISSILE_EXPLOSION:
		SimpleAudioEngine::getInstance()->playEffect("AimingMissileExplosion.wav");
		break;
		
	}
}



