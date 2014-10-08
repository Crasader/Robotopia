#pragma once

#include "cocos2d.h"

enum AnimationType
{
	AT_PLAYER_STAND,
	AT_PLAYER_ATTACK,
	AT_PLAYER_JUMP,
	AT_PLAYER_WALK,
};


class ResourceManager
{
public:
	bool init();

	cocos2d::Animation* createAnimation(const char* format, int startIdx, size_t frameNum, float delay);
	cocos2d::Animation* createAnimation(AnimationType type, float delay = -1);
	cocos2d::Sprite* createSprite(const char* spriteName);
	
private:
};