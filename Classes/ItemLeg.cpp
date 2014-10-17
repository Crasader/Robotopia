#include "ItemLeg.h"
#include "GameManager.h"


USING_NS_CC;

bool ItemLeg::init()
{
	if (!Item::init())
	{
		return false;
	}

	m_Type = OT_ITEM_LEG;

	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite(ST_ITEM_LEG);
	m_MainSprite->setScale(0.5);
	
	this->addChild(m_MainSprite);

	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	m_CreateTimeInMilli = (tv.tv_usec / 1000) + tv.tv_sec * 1000;
	m_RemainGroundTime = 10;

	m_AddSpeed = 100;

	return true;
}

void ItemLeg::collisionOccured(InteractiveObject* enemy, Directions dir)
{
	auto ItemPos = this->getPosition();
	auto enemyPoint = enemy->getPosition();

	float distance = sqrt((ItemPos.x - enemyPoint.x)*(ItemPos.x - enemyPoint.x) + (ItemPos.y - enemyPoint.y)*(ItemPos.y - enemyPoint.y));

	/*if (distance < 50)
	{*/

		if (enemy->getType() == OT_PLAYER && !m_IsDestroyed)
		{
			int type = rand() % 3;
			switch (type)
			{
			case 0:
				GET_STAGE_MANAGER()->getPlayer()->setSpeed(m_AddSpeed, true);
				break;
			case 1:
				GET_STAGE_MANAGER()->getPlayer()->setMaxHp(10, true);
				GET_STAGE_MANAGER()->getPlayer()->setHp(10, true);
				break;
			case 2:
				GET_STAGE_MANAGER()->getPlayer()->setMaxSteam(1000, true);
				GET_STAGE_MANAGER()->getPlayer()->setSteam(1000, true);
				break;
			}
			
			GET_EFFECT_MANAGER()->createSound(SO_STEAM_GET, false);
			m_IsDestroyed = true;
		}
	//}
}

void ItemLeg::setAttribute(float setAddSpped)
{
	
	m_AddSpeed = setAddSpped;
}

void ItemLeg::update(float dTime)
{
	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	long CurTimeInMilli = (tv.tv_usec / 1000) + tv.tv_sec * 1000;

	static bool firstFlag = false;
	static bool secondFlag = false;
	static bool thirdFlag = false;
	

	if (CurTimeInMilli - m_CreateTimeInMilli > 100000)
	{
		if (thirdFlag == false)
		{
			thirdFlag = true;
			m_MainSprite->setOpacity(65);
			auto action = Blink::create(5.0f, 20);
			m_MainSprite->runAction(RepeatForever::create(action));
		}

	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 75000)
	{
		if (secondFlag == false)
		{
			m_MainSprite->setOpacity(120);
			m_MainSprite->stopAllActions();
			/*m_MainSprite->stopAllActions();
			auto action2 = FadeTo::create(0.2f, 70);
			auto action3 = FadeTo::create(0.2f, 150);
			auto sequence1 = Sequence::create(action2, action3, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence1));*/
			secondFlag = true;

			auto action = Blink::create(5.0f, 20);
			m_MainSprite->runAction(RepeatForever::create(action));
		}
		
	}
	else if (CurTimeInMilli - m_CreateTimeInMilli > 50000)
	{
		if (firstFlag == false)
		{
			m_MainSprite->setOpacity(180);
			m_MainSprite->stopAllActions();
			/*m_MainSprite->stopAllActions();
			auto action0 = FadeTo::create(0.5f, 128);
			auto action1 = FadeTo::create(0.5f, 190);
			auto sequence0 = Sequence::create(action0, action1, NULL);
			m_MainSprite->runAction(RepeatForever::create(sequence0));*/
			firstFlag = true;
			auto action = Blink::create(5.0f, 10);
			m_MainSprite->runAction(RepeatForever::create(action));
		}
	}
}


