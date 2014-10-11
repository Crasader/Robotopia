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

	m_MainSprite = Sprite::create();
	//auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_STEAMPACK, 0.5f);
	//m_Animations[0] = animation;
	m_MainSprite->setScale(0.5f);
	//m_MainSprite->runAction(RepeatForever::create(Animate::create(m_Animations[0])));

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
	if (CurTimeInMilli - m_CreateTimeInMilli > 10)
	{
		m_IsDestroyed = true;
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 7.5)
	{
		m_MainSprite->setOpacity(120);
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 5)
	{
		m_MainSprite->setOpacity(190);
	}


	return;
}

