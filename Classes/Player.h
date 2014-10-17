//Player.h
//
//게임 주인공 캐릭터의 조작 및 충돌 처리등을 구현. 
//
//작성자 : 남현욱
//
#pragma once

#include "InteractiveObject.h"

struct PlayerInfo
{
	int			hp;
	int			steam;
	int			maxHp;
	int			maxSteam;
	int			speed;
	int			gear;
	float		attackSpeed;
	
	PlayerInfo()
	{
		maxHp = 100;
		hp = maxHp;
		maxSteam = 20000;
		steam = maxSteam;
		speed = 200;
		gear = 2;
		attackSpeed = 0.05f;
	}

	~PlayerInfo()
	{
	}
};

class Player : public InteractiveObject
{
public:
	OVERRIDE bool			init();
	CREATE_FUNC(Player);

	OVERRIDE void			collisionOccured(InteractiveObject* enemy, Directions dir);

	OVERRIDE cocos2d::Rect	getRect();

	void					update(float dTime);

	int						getHp() const { return m_Info.hp; }
	int						getSteam() const { return m_Info.steam; }
	int						getMaxHp() const { return m_Info.maxHp; }
	int						getMaxSteam() const { return m_Info.maxSteam; }
	int						getGear() const { return m_Info.gear; }
	bool					isInvincible() const{ return m_IsInvincible; }
	PlayerInfo				getInfo() const { return m_Info; }
	void					setHp(int hp, bool isRelative = false);
	void					setMaxHp(int maxHp, bool isRelative = false) { if (!isRelative) m_Info.maxHp = maxHp; else m_Info.maxHp += maxHp; }
	void					setSteam(int steam, bool isRelative = false);
	void					setMaxSteam(int maxSteam, bool isRelative = false){ if (!isRelative) m_Info.maxSteam = maxSteam; else m_Info.maxSteam += maxSteam; }
	void					setInfo(PlayerInfo info) { m_Info = info; }
	void					setSpeed(int speed, bool isRelative = false){ if (!isRelative)m_Info.speed = speed; else m_Info.speed += speed; }
	void					setGear(int gear){if (gear >= 1 && gear <= 3) m_Info.gear = gear;}

private:
	enum State
	{
		PS_STAND,
		PS_WALK,
		PS_JUMP,
		PS_ATTACK,
		PS_ATTACK2,
		PS_HIT,
		PS_STATE_NUM,
	};

	PlayerInfo m_Info;
	State		m_State;
	bool		m_IsRightDirection;
	int			m_AttackNum;
	bool		m_AttackEnd;
	bool		m_IsActiveFly;
	bool		m_IsInvincible;
	bool		m_IsCrashed;
	float		m_ActiveFlyingTime;
	float		m_HitTime;
	float		m_GearWeight[4];

	void		startInvincible();
	void		endInvincible(cocos2d::Ref* sender);
	void		changeState(State state);
	void		endAnimation(cocos2d::Ref* sender);
	void		act(float dTime);
	void		reset(float dTime);
};