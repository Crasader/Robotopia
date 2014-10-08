#include "ResourceManager.h"

USING_NS_CC;

bool ResourceManager::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Robotopia.plist");
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
	return animation;

}

cocos2d::Animation* ResourceManager::createAnimation(AnimationType type, float delay /*= -1*/)
{
	switch (type)
	{
	case AT_PLAYER_STAND: //animation
		return createAnimation("player_stand%d.png", 1, 4, 0.1f);
	}
	return nullptr;
}

cocos2d::Sprite* ResourceManager::createSprite(const char* spriteName)
{
	auto sprite = Sprite::createWithSpriteFrameName(spriteName);

	return sprite;
}
