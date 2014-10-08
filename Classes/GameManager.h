#include "cocos2d.h"

class GameManager
{
public:
	GameManager* getInstance();
	void releaseInstance();
private:
	static GameManager* m_pInstance;
	GameManager();
	~GameManager();
};