#include "Monster.h"


class BatMonster : public Monster
{
public:
	OVERRIDE	bool init();

	OVERRIDE	void collisionOccured(InteractiveObject* enemy, Directions dir);
	OVERRIDE	cocos2d::Rect getRect();
	void		update(float dTime);

	bool	m_IsRightDirection;
	float	m_AttackTime;

	CREATE_FUNC(BatMonster);
private:
	enum State
	{
		BM_FIND,
		BM_ATTACK,
		BM_STATE_NUM,
	};

	State m_State;

	void changeState(State state);

	void endAnimation(Ref* sender);
};