#include "SteamPack.h"
#include "GameManager.h"
#include <math.h>

USING_NS_CC;
bool SteamPack::init()
{
	if (!Item::init())
	{
		return false;
	}

	m_Type = OT_STEAM_PACK;


	m_MainSprite = Sprite::create();

	m_MainSprite->setScale(0.5);
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_STEAMPACK);
	m_MainSprite->runAction(RepeatForever::create(Animate::create(animation)));
	m_MainSprite->setScale(0.5f);
	this->addChild(m_MainSprite);

	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	m_CreateTimeInMilli = (tv.tv_usec / 1000) + tv.tv_sec * 1000;
	m_RemainGroundTime = 10;
	/////////////////
	m_SteamVolume = 3;
	////////////////

	return true;
}

void SteamPack::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	auto SteamPoint = this->getPosition();
	auto enemyPoint = enemy->getPosition();

	float distance = sqrt((SteamPoint.x - enemyPoint.x)*(SteamPoint.x - enemyPoint.x) + (SteamPoint.y - enemyPoint.y)*(SteamPoint.y - enemyPoint.y));
	
	if (distance < 50)
	{

		if (enemy->getType() == OT_PLAYER)
		{
			GET_STAGE_MANAGER()->getPlayer()->setSteam(m_SteamVolume, true);

			m_IsDestroyed = true;
		}
	}

	return;
}

void SteamPack::update(float dTime)
{

	//이거 되려나 
	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	long CurTimeInMilli = (tv.tv_usec / 1000) + tv.tv_sec * 1000;
	
	static bool firstFlag = false;
	static bool secondFlag = false;

	if (CurTimeInMilli - m_CreateTimeInMilli > 10000)
	{
		m_IsDestroyed = true;
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 7500)
	{
		if (secondFlag == false)
		{
			m_MainSprite->setOpacity(120);
			/*m_MainSprite->stopAllActions();
			auto action2 = FadeTo::create(0.2f, 70);
			auto action3 = FadeTo::create(0.2f, 150);
			auto sequence1 = Sequence::create(action2, action3, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence1));
			secondFlag = true;*/
		}
		
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 5000)
	{
		if (firstFlag == false)
		{
			m_MainSprite->setOpacity(180);
			/*m_MainSprite->stopAllActions();
			auto action0 = FadeTo::create(0.5f, 128);
			auto action1 = FadeTo::create(0.5f, 190);
			auto sequence0 = Sequence::create(action0, action1, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence0));
			firstFlag = true;*/
		}
	}


	return;
}

void SteamPack::setAttribute(float setSteamVolume)
{
	m_SteamVolume = setSteamVolume;
}

