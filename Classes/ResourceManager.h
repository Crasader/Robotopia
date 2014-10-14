﻿//ResourceManager.h
//
//Resource Sprite 및 Animation을 추가할 때 언제든지 얘기해주세요!
//
//작성자 : 우재우
//

#pragma once

#include "cocos2d.h"

enum AnimationType
{
	AT_AIMINGMISSILE_FLYING,
	AT_AIMINGMISSILE_COLLISION,
	AT_DUST_FOR_SHAKE,
	AT_FLOORGATEWAY_OPEN,
	AT_GATEWAY_ACT,
	AT_LINEARMISSILE_FLYING,
	AT_LINEARMISSILE_COLLISION,
	AT_MELEE_MISSILE_FLYING,
	AT_MELEE_MISSILE_COLLISION,
	AT_MONSTER_BAT,
	AT_NEW_LINEAR_MISSILE_FLYING,
	AT_NEW_LINEAR_MISSILE_COLLISION,
	AT_PLAYER_STAND,
	AT_PLAYER_ATTACK,
	AT_PLAYER_JUMP,
	AT_PLAYER_WALK,
	AT_PLAYER_LANDING,
	AT_ROUND_SMOKE,
	AT_RUSHMONSTER_STAND,
	AT_RUSHMONSTER_MOVE,
	AT_RUSHMONSTER_RUSH,
	AT_STEAMPACK,
	AT_SWEAT,
	AT_TRAP_ACTIVATE,
};

enum SpriteType
{
	ST_AIMINGMISSILE_FLYING,
	ST_AIMINGMISSILE_COLLISION,
	ST_DUST_FOR_SHAKE,
	ST_FLOORGATEWAY,
	ST_GATEWAY_ACTIVE,
	ST_GATEWAY_UNACTIVE,
	ST_ITEM_LEG,
	ST_LINEARMISSILE_FLYING,
	ST_LINEARMISSILE_COLLISION,
	ST_LOADING,
	ST_MELEE_MISSILE_FLYING,
	ST_MELEE_MISSILE_COLLISION,
	ST_MONSTER_BAT,
	ST_NEW_LINEAR_MISSILE_FLYING,
	ST_NEW_LINEAR_MISSILE_COLLISION,
	ST_PLAYER_LANDING,
	ST_ROUND_SMOKE,
	ST_STEAMPACK,
	ST_SWEAT,
	ST_TRAP,
	ST_RUSH_MONSTER,
};


class ResourceManager
{
public:
	bool init();

	cocos2d::Animation* createAnimation(const char* format, int startIdx, size_t frameNum, float delay);
	cocos2d::Animation* createAnimation(AnimationType type, float delay = -1);
	cocos2d::Sprite* createSprite(const char* spriteName);
	cocos2d::Sprite* createSprite(SpriteType type);
	
private:
	std::map <AnimationType, cocos2d::Animation*> m_Animations;
};
