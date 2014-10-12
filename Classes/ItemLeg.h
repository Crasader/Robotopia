#pragma once
#include "cocos2d.h"
#include "Item.h"

class ItemLeg : public Item
{
public:
	OVERRIDE bool init();
	OVERRIDE void collisionOccured(InteractiveObject* enemy, Directions dir);
	void		  update(float dTime);
	void		  setAttribute(float setAddSpped);

	CREATE_FUNC(ItemLeg);
private:
	float m_AddSpeed;
};

