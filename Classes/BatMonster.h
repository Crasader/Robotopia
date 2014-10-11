#include "Monster.h"


class BatMonster : public Monster
{
public:
	OVERRIDE bool init();

	OVERRIDE void collisionOccured(InteractiveObject* enemy, Directions dir);

	void update(float dTime);

	CREATE_FUNC(BatMonster);
private:
	enum State
	{
		BM_FIND,
		BM_ATTACK,
		BM_STATE_NUM,
	};
};