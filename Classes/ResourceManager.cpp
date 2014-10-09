#include "ResourceManager.h"

USING_NS_CC;

bool ResourceManager::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Robotopia.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ET_AimingMissile_Collision.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ozt.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ETLinearMissileCollision.plist");
	return true;
}

cocos2d::Animation* ResourceManager::createAnimation(const char* format, int startIdx, size_t frameNum, float delay)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(delay);

	for (size_t i = 0; i < frameNum; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format(format, i + startIdx));
		animation->addSpriteFrame(frame);
	}
	animation->retain();
	return animation;
}


cocos2d::Animation* ResourceManager::createAnimation(AnimationType type, float delay /*= -1*/)
{
	switch (type)
	{
	case AT_AIMINGMISSILE_FLYING:
		return createAnimation("AimingMissile%d.png", 1, 8, 0.1f);
	case AT_AIMINGMISSILE_COLLISION:
		return createAnimation("ET_AimingMissile_Collision%d.png", 1, 4, 0.1f);
	case AT_GATEWAY_ACT:
		return createAnimation("GatewayAct%d.png", 0, 5, 0.1f);
	case AT_LINEARMISSILE_FLYING:
		return createAnimation("LinearMissile%d.png", 0, 10, 0.1f);
	case AT_LINEARMISSILE_COLLISION:
		return createAnimation("ETLinearMissileCollision%d.png", 1, 9, 0.1f);
	case AT_PLAYER_STAND:
		return createAnimation("player_stand%d.png", 1, 4, 0.1f);
	case AT_PLAYER_WALK:
		return createAnimation("player_walk%d.png", 1, 8, 0.05f);
	case AT_PLAYER_JUMP:
		return createAnimation("player_jump%d.png", 1, 1, 0.1f);
	case AT_PLAYER_ATTACK:
		return createAnimation("player_attack%d.png", 1, 5, 0.05f);
	case AT_PLAYER_LANDING:
		return nullptr;
	case AT_RUSHMONSTER_STAND:
		return createAnimation("rushMonster_stand%d.png", 1, 4, 0.1f);
	case AT_RUSHMONSTER_MOVE:
		return createAnimation("rushMonster_move%d.png", 1, 4, 0.1f);
	case AT_RUSHMONSTER_RUSH:
		return createAnimation("rushMonster_rush%d.png", 1, 4, 0.1f);
	}
	return nullptr;
}

cocos2d::Sprite* ResourceManager::createSprite(const char* spriteName)
{
	auto sprite = Sprite::createWithSpriteFrameName(spriteName);
	return sprite;
}

cocos2d::Sprite* ResourceManager::createSprite(SpriteType type)
{
	switch (type)
	{
	case ST_AIMINGMISSILE_FLYING:
		return createSprite("AimingMissile1.png");
	case ST_AIMINGMISSILE_COLLISION:
		return createSprite("ET_AimingMissile_Collision1.png");
	case ST_GATEWAY_ACTIVE:
		return createSprite("GatewayActive.png");
	case ST_GATEWAY_UNACTIVE:
		return createSprite("GatewayUnactive.png");
	case ST_LINEARMISSILE_FLYING:
		return createSprite("LinearMissile1.png");
	case ST_LINEARMISSILE_COLLISION:
		return createSprite("ETLinearMissileCollision1.png");
	case ST_LOADING:
		return createSprite("Loading.png");
	}
	return nullptr;
}
