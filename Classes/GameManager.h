// 
// GameManager.h
//
// 작성자 : 남현욱
//
//게임의 모든 매니저 클래스를 포함하고 있는 클래스.
//매니저 필요하면 얘 하나만 인클루드하면 다 됨.
#pragma once
#include "cocos2d.h"
#include "InputManager.h"
#include "ResourceManager.h"


class GameManager
{
public:
	GameManager* getInstance();
	void releaseInstance();
private:
	static GameManager* m_pInstance;
	static InputManager* m_pInputManager;
	GameManager();
	~GameManager();
};
