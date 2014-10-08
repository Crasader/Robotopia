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
	m_pInputManager = nullptr;
	m_pEffectManager = nullptr;
	m_pResourceManager = nullptr;
	m_pStageManager = nullptr;
}

GameManager::~GameManager()
{
	if (m_pInputManager != nullptr)
	{
		delete m_pInputManager;
		m_pInputManager = nullptr;
	}

	if (m_pEffectManager != nullptr)
	{
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}

	if (m_pResourceManager != nullptr)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pStageManager != nullptr)
	{
		delete m_pStageManager;
		m_pStageManager = nullptr;
	}
}

InputManager* GameManager::getInputManagerInstance()
{
	if (m_pInputManager == nullptr)
	{
		m_pInputManager = new InputManager();
	}

	m_pInputManager->init();
	return m_pInputManager;
}

EffectManager* GameManager::getEffectManagerInstance()
{
	if (m_pEffectManager == nullptr)
	{
		m_pEffectManager = new EffectManager();
	}
	m_pEffectManager->init();
	return m_pEffectManager;
}

ResourceManager* GameManager::getResourceManagerInstance()
{
	if (m_pResourceManager == nullptr)
	{
		m_pResourceManager = new ResourceManager();
	}
	m_pResourceManager->init();
	return m_pResourceManager;
}

StageManager* GameManager::getStageManagerInstance()
{
	if (m_pStageManager == nullptr)
	{
		m_pStageManager = new StageManager();
	}
	m_pStageManager->init();
	return m_pStageManager; 
}
