#pragma once

#include "Monster.h"

class Boss : public Monster
{
public:
	OVERRIDE bool			init();

	OVERRIDE void			collisionOccured(InteractiveObject* enemy, Directions dir);

	CREATE_FUNC(Boss);

	OVERRIDE cocos2d::Rect	getRect();
private:
	enum State
	{
		BO_STAND,
		BO_STATE_NUM,
	};

	void		changeState(State state);
	void		endAnimation(cocos2d::Ref* sender);
	void		update(float dTime);

	State		m_State;
};