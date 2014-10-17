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
		BO_ATTACK,
		BO_MOVE,
		BO_JUMP,
		BO_STATE_NUM,
	};

	enum AIState
	{
		BA_WAIT,
		BA_ATTACK,
		BA_RUSH,
		BA_STATE_NUM,
	};

	void				changeState(State state);
	void				endAnimation(cocos2d::Ref* sender);
	void				update(float dTime);
	
	State				m_State;
	AIState				m_AIState;
	bool				m_IsRightDirection;
	bool				m_IsGotoBottom;
	bool				m_IsAttackEnd;
	bool				m_IsRushing;
	float				m_WaitTime;
	float				m_RushTime;
	float				m_RushTargetTime;
	cocos2d::Point		m_StartPos;
	int					m_AttackNum;
	int					m_RushNum;
};