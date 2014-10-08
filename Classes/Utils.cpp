#include "Utils.h"



cocos2d::Animation* UtilFunctions::createAnimation(const char* animationName, int startIdx, size_t frameNum, float delay)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(delay);

	for (size_t i = 0; i < frameNum; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("%s%d.png", animationName, i + startIdx));
		animation->addSpriteFrame(frame);
	}
	return animation;

}
