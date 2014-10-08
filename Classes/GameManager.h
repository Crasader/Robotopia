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
#include "EffectManager.h"
#include "StageManager.h"
#define GET_GAME_MANAGER() GameManager::getInstance()
#define GET_INPUT_MANAGER() GameManager::getInstance()->getInputManagerInstance()
#define GET_EFFECT_MANAGER() GameManager::getInstance()->getEffectManagerInstance()
#define GET_RESOURCE_MANAGER() GameManager::getInstance()->getResourceManagerInstance()
#define GET_STAGE_MANAGER() GameManager::getInstance()->getStageManagerInstance()

class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	InputManager* getInputManagerInstance();
	EffectManager* getEffectManagerInstance();
	ResourceManager* getResourceManagerInstance();
	StageManager* getStageManagerInstance();
private:
	static GameManager* m_pInstance;
	InputManager* m_pInputManager;
	EffectManager* m_pEffectManager;
	ResourceManager* m_pResourceManager;
	StageManager* m_pStageManager;
	GameManager();
	~GameManager();
};
