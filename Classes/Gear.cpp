#include "Gear.h"

USING_NS_CC;


bool Gear::init()
{
	m_Gear1 = Sprite::create("Gear1_Off.png");
	m_Gear1->setScale(0.4f);
	m_Gear1->setPosition(Point(50, 50));
	
	m_Gear2 = Sprite::create("Gear2_On.png");
	m_Gear2->setScale(0.4f);
	m_Gear2->setPosition(Point(50, 100));

	m_Gear3 = Sprite::create("Gear3_Off.png");
	m_Gear3->setScale(0.4f);
	m_Gear3->setPosition(Point(50, 150));

	this->addChild(m_Gear1);
	this->addChild(m_Gear2);
	this->addChild(m_Gear3);
	return true;
}

void Gear::update(float dTime)
{
	/*auto player = GET_STAGE_MANAGER()->getPlayer();
	if (player != nullptr)
	{
		auto playerInfo = player->getInfo();
		switch (playerInfo.gear)
		{
		case 1:
			m_Gear1->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear1_On.png"));
			m_Gear2->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear2_Off.png"));
			m_Gear3->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear3_Off.png"));
			break;
		case 2:
			m_Gear1->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear1_Off.png"));
			m_Gear2->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear2_On.png"));
			m_Gear3->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear3_Off.png"));
			break;
		case 3:
			m_Gear1->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear1_Off.png"));
			m_Gear2->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear2_Off.png"));
			m_Gear3->setTexture(Director::getInstance()->getTextureCache()->addImage("Gear3_On.png"));
			break;
		}
	}*/
}
