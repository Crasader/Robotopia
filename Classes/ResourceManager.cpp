#include "ResourceManager.h"

USING_NS_CC;

bool ResourceManager::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Robotopia.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ET_AimingMissile_Collision.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ET_PLAYER_LANDING.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ozt.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ETLinearMissileCollision.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("New_Linear_Missile.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("New_Linear_Missile_Collision.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Melee_Missile.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Melee_Missile_Collision.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Round_Smoke.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monsterBat.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SteamPack.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sweat.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ET_dust_for_shake.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Item_Leg.plist");
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
	if (delay == -1)
	{
		delay = 0.1f;
	}
	if (m_Animations.find(type) != m_Animations.end())
	{
		return m_Animations[type]->clone();
	}
	else
	{
		switch (type)
		{
		case AT_AIMINGMISSILE_FLYING:
			return createAnimation("AimingMissile%d.png", 1, 8, delay);
		case AT_AIMINGMISSILE_COLLISION:
			return createAnimation("ET_AimingMissile_Collision%d.png", 1, 4, delay);
		case AT_FLOORGATEWAY_OPEN:
			return createAnimation("FloorGateway%d.png", 0, 11, delay);
		case AT_GATEWAY_ACT:
			return createAnimation("GatewayAct%d.png", 0, 5, delay);
		case AT_LINEARMISSILE_FLYING:
			return createAnimation("LinearMissile%d.png", 0, 10, delay);
		case AT_LINEARMISSILE_COLLISION:
			return createAnimation("ETLinearMissileCollision%d.png", 1, 9, delay);
		case AT_MELEE_MISSILE_FLYING:
			return createAnimation("Melee_Missile%d.png", 1, 6, delay);
		case AT_MELEE_MISSILE_COLLISION:
			return createAnimation("Melee_Missile_Collision%d.png", 1, 6, delay);
		case AT_NEW_LINEAR_MISSILE_FLYING:
			return createAnimation("New_Linear_Missile%d.png", 1, 6, delay);
		case AT_NEW_LINEAR_MISSILE_COLLISION:
			return createAnimation("New_Linear_Missile_Collsion%d.png", 1, 6, delay);
		case AT_MONSTER_BAT:
			return createAnimation("monster_bat%d.png", 1, 8, delay);
		case AT_PLAYER_STAND:
			return createAnimation("player_stand%d.png", 1, 4, delay);
		case AT_PLAYER_WALK:
			return createAnimation("player_walk%d.png", 1, 8, delay);
		case AT_PLAYER_JUMP:
			return createAnimation("player_jump%d.png", 1, 1, delay);
		case AT_PLAYER_ATTACK:
			return createAnimation("player_attack%d.png", 1, 5, delay);
		case AT_PLAYER_LANDING:
			return createAnimation("ET_PLAYER_LANDING%d.png", 1, 4, delay);
		case AT_ROUND_SMOKE:
			return createAnimation("Round_Smoke%d.png", 1, 4, delay);
		case AT_RUSHMONSTER_STAND:
			return createAnimation("rushMonster_stand%d.png", 1, 4, delay);
		case AT_RUSHMONSTER_MOVE:
			return createAnimation("rushMonster_move%d.png", 1, 4, delay);
		case AT_RUSHMONSTER_RUSH:
			return createAnimation("rushMonster_rush%d.png", 1, 4, delay);
		case AT_STEAMPACK:
			return createAnimation("SteamPack%d.png", 1, 5, delay);
		case AT_SWEAT:
			return createAnimation("sweat%d.png", 1, 4, delay);
		case AT_DUST_FOR_SHAKE:
			return createAnimation("ET_dust_for_Shake%d.png", 1, 4, delay);
		case AT_TRAP_ACTIVATE:
			return createAnimation("trap%d.png", 0, 24, delay);
		}
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
		case ST_DUST_FOR_SHAKE:
			return createSprite("ET_dust_for_Shake1.png");
		case ST_FLOORGATEWAY:
			return createSprite("FloorGateway0.png");
		case ST_GATEWAY_ACTIVE:
			return createSprite("GatewayActive.png");
		case ST_GATEWAY_UNACTIVE:
			return createSprite("GatewayUnactive.png");
		case ST_ITEM_LEG:
			return createSprite("Item_Leg1.png");
		case ST_LINEARMISSILE_FLYING:
			return createSprite("LinearMissile1.png");
		case ST_LINEARMISSILE_COLLISION:
			return createSprite("ETLinearMissileCollision1.png");
		case ST_LOADING:
			return createSprite("Loading.png");
		case ST_MELEE_MISSILE_FLYING:
			return createSprite("Melee_Missile3.png");
		case ST_MELEE_MISSILE_COLLISION:
			return createSprite("Melee_Missile_Collision1.png");
		case ST_MONSTER_BAT:
			return createSprite("monster_bat1.png");
		case ST_NEW_LINEAR_MISSILE_FLYING:
			return createSprite("New_Linear_Missile1.png");
		case ST_NEW_LINEAR_MISSILE_COLLISION:
			return createSprite("New_Linear_Missile_Collsion1.png");
		case ST_PLAYER_LANDING:
			return createSprite("ET_PLAYER_LANDING1.png");
		case ST_ROUND_SMOKE:
			return createSprite("Round_Smoke1.png");
		case ST_STEAMPACK:
			return createSprite("SteamPack3.png");
		case ST_SWEAT:
			return createSprite("sweat4.png");
		case ST_TRAP:
			return createSprite("trap0.png");
		case ST_RUSH_MONSTER:
			return createSprite("rushMonster_stand1.png");
		}
	return nullptr;
}
