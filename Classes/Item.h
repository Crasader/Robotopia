#pragma once

#include "cocos2d.h"
#include "InteractiveObject.h"



class Item : public InteractiveObject
{
public:
	OVERRIDE bool init(); 
	

protected:
	float  m_RemainGroundTime; 
	long   m_CreateTimeInMilli;
};