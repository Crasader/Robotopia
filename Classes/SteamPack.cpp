#include "SteamPack.h"
#include "GameManager.h"

USING_NS_CC;
bool SteamPack::init()
{
	if (!Item::init())
	{
		return false;
	}

	//m_Type = OT_STEAMPACK;


	//m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_STEAMPACK);
	m_MainSprite->setScale(0.5f);

	



	this->addChild(m_MainSprite);

	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	m_CreateTimeInMilli = (tv.tv_usec / 1000) + tv.tv_sec * 1000;
	m_RemainGroundTime = 10;
	m_SteamVolume = 3;


	this->scheduleUpdate();
	return true;
}

void SteamPack::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	if (enemy->getType() == OT_PLAYER)
	{
		float curPlayerSteam = GET_STAGE_MANAGER()->getPlayer()->getSteam();
		GET_STAGE_MANAGER()->getPlayer()->setSteam(curPlayerSteam + m_SteamVolume);
		m_IsDestroyed = true;
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

	if (CurTimeInMilli - m_CreateTimeInMilli > 10)
	{
		m_IsDestroyed = true;
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 7.5)
	{
		if (secondFlag == false)
		{
			m_MainSprite->stopAllActions();
			auto action2 = FadeTo::create(0.2f, 70);
			auto action3 = FadeTo::create(0.2f, 150);
			auto sequence1 = Sequence::create(action2, action3, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence1));
			secondFlag = true;
		}
		
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 5)
	{
		m_MainSprite->stopAllActions();
		if (firstFlag == false)
		{
			auto action0 = FadeTo::create(0.5f, 128);
			auto action1 = FadeTo::create(0.5f, 190);
			auto sequence0 = Sequence::create(action0, action1, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence0));
			firstFlag = true;
		}
	}


	return;
}

