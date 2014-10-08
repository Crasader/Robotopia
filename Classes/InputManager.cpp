#include "InputManager.h"

USING_NS_CC;

std::map<cocos2d::EventKeyboard::KeyCode, KeyState> InputManager::m_KeyStates;
std::map<cocos2d::EventKeyboard::KeyCode, KeyState> InputManager::m_PrevKeyStates;
std::map<cocos2d::EventKeyboard::KeyCode, KeyState> InputManager::m_FinalKeyStates;

KeyState InputManager::getKeyState(KeyCode keyCode)
{
	return m_FinalKeyStates[(EventKeyboard::KeyCode)keyCode];
}

void InputManager::receiveKeyboardData(cocos2d::Layer* layer)
{
	auto sentinel = KeyStateSentinel::create();

	layer->addChild(sentinel);
}

bool KeyStateSentinel::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(KeyStateSentinel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(KeyStateSentinel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);


	for (EventKeyboard::KeyCode i = EventKeyboard::KeyCode::KEY_NONE; i < EventKeyboard::KeyCode::KEY_PLAY; i = (EventKeyboard::KeyCode)((int)i + 1))
	{
		InputManager::m_PrevKeyStates[i] = KS_NONE;
		InputManager::m_KeyStates[i] = KS_NONE;
	}

	this->scheduleUpdate();

	return true;
}

void KeyStateSentinel::update(float dTime)
{
	for (auto state : InputManager::m_KeyStates)
	{
		KeyState prevState = InputManager::m_PrevKeyStates[state.first];
		KeyState nowState = InputManager::m_KeyStates[state.first];

		if (prevState == KS_NONE && nowState == KS_NONE)
		{
			InputManager::m_FinalKeyStates[state.first] = KS_NONE;
		}
		else if (prevState == KS_NONE && nowState == KS_PRESS)
		{
			InputManager::m_FinalKeyStates[state.first] = KS_PRESS;
		}
		else if (prevState == KS_PRESS && nowState == KS_NONE)
		{
			InputManager::m_FinalKeyStates[state.first] = KS_RELEASE;
		}
		else if (prevState == KS_PRESS && nowState == KS_PRESS)
		{
			InputManager::m_FinalKeyStates[state.first] = KS_HOLD;
		}

		InputManager::m_PrevKeyStates[state.first] = state.second;
	}
}

void KeyStateSentinel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	InputManager::m_KeyStates[keyCode] = KS_PRESS;
}

void KeyStateSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	InputManager::m_KeyStates[keyCode] = KS_NONE;
}