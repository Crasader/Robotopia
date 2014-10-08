#pragma once

#include "cocos2d.h"

class ResourceManager
{
public:
	bool init();

	cocos2d::Animation* createAnimation(const char* format, int startIdx, size_t frameNum, float delay);
	cocos2d::Sprite* createSprite(const char* spriteName);
private:
};