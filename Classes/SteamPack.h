#pragma once

#include "Item.h"

class SteamPack : public Item
{
public:
	OVERRIDE bool init();
	OVERRIDE void collisionOccured(InteractiveObject* enemy, Directions dir);
	void		  update(float dTime);
	CREATE_FUNC(SteamPack);
private:
	float m_SteamVolume;
};