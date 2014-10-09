#pragma once

#include "cocos2d.h"

enum AnimationType
{
	AT_AIMINGMISSILE_FLYING,
	AT_AIMINGMISSILE_COLLISION,
	AT_LINEARMISSILE_FLYING,
	AT_LINEARMISSILE_COLLISION,
	AT_PLAYER_STAND,
	AT_PLAYER_ATTACK,
	AT_PLAYER_JUMP,
	AT_PLAYER_WALK,
	AT_PLAYER_LANDING,
	AT_RUSHMONSTER_STAND,
	AT_RUSHMONSTER_MOVE,
	AT_RUSHMONSTER_RUSH,

	AT_GATEWAY_OPEN,

};

enum SpriteType
{

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
};
