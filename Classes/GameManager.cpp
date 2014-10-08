#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::m_pInstance = nullptr;

GameManager* GameManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameManager();
	}

	return m_pInstance;
}

void GameManager::releaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

GameManager::GameManager()
{
	m_pInputManager = new InputManager();

}

GameManager::~GameManager()
{
	if (m_pInputManager != nullptr)
	{
		delete m_pInputManager;
	}
}

InputManager* GameManager::getInputManagerInstance()
{
	return m_pInputManager;
}
