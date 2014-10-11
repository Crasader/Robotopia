﻿#include "GameManager.h"
#include "WorldScene.h"

USING_NS_CC;

KeyState InputManager::getKeyState(KeyCode keyCode)
{
	return m_FinalKeyStates[(EventKeyboard::KeyCode)keyCode];
}

KeyStateSentinel* InputManager::receiveKeyboardData(WorldScene* scene)
{
	auto sentinel = KeyStateSentinel::create();

	scene->addChild(sentinel);
}

bool InputManager::init()
{
	for (EventKeyboard::KeyCode i = EventKeyboard::KeyCode::KEY_NONE; i < EventKeyboard::KeyCode::KEY_PLAY; i = (EventKeyboard::KeyCode)((int)i + 1))
	{
		m_PrevKeyStates[i] = KS_NONE;
		m_KeyStates[i] = KS_NONE;
	}

	m_PrevMouseStates[MC_LEFT] = MS_NONE;
	m_MouseStates[MC_RIGHT] = MS_NONE;
	m_MouseWheel = 0.0f;
	m_MousePos = Point::ZERO;

	return true;
}

KeyStateSentinel InputManager::receiveInputData(WorldScene* scene)
{
	return receiveKeyboardData(scene);
}

void KeyStateSentinel::update(float dTime)
{
	for (auto state : GET_INPUT_MANAGER()->m_KeyStates)
	{
		KeyState prevState = GET_INPUT_MANAGER()->m_PrevKeyStates[state.first];
		KeyState nowState = GET_INPUT_MANAGER()->m_KeyStates[state.first];

		if (prevState == KS_NONE && nowState == KS_NONE)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[state.first] = KS_NONE;
		}
		else if (prevState == KS_NONE && nowState == KS_PRESS)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[state.first] = KS_PRESS;
		}
		else if (prevState == KS_PRESS && nowState == KS_NONE)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[state.first] = KS_RELEASE;
		}
		else if (prevState == KS_PRESS && nowState == KS_PRESS)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[state.first] = KS_HOLD;
		}

		GET_INPUT_MANAGER()->m_PrevKeyStates[state.first] = state.second;
	}
}

void KeyStateSentinel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GET_INPUT_MANAGER()->m_KeyStates[keyCode] = KS_PRESS;
}

void KeyStateSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GET_INPUT_MANAGER()->m_KeyStates[keyCode] = KS_NONE;
}