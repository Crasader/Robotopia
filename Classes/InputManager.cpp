#include "GameManager.h"
#include "WorldScene.h"

USING_NS_CC;

KeyState InputManager::getKeyState(KeyCode keyCode)
{
	return m_FinalKeyStates[(int)keyCode];
}

KeyStateSentinel* InputManager::receiveKeyboardData(WorldScene* scene)
{
	auto sentinel = KeyStateSentinel::create();

	scene->addChild(sentinel);

	return sentinel;
}

bool InputManager::init()
{
	for (EventKeyboard::KeyCode i = EventKeyboard::KeyCode::KEY_NONE; i < EventKeyboard::KeyCode::KEY_PLAY; i = (EventKeyboard::KeyCode)((int)i + 1))
	{
		m_PrevKeyStates[(int)i] = KS_NONE;
		m_KeyStates[(int)i] = KS_NONE;
	}

	return true;
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

	return true;
}

KeyStateSentinel* InputManager::receiveInputData(WorldScene* scene)
{
	return receiveKeyboardData(scene);
}

void KeyStateSentinel::update(float dTime)
{

	for (int i = 0; i < 162; i++)
	{
		KeyState prevState = GET_INPUT_MANAGER()->m_PrevKeyStates[i];
		KeyState nowState = GET_INPUT_MANAGER()->m_KeyStates[i];

		if (prevState == KS_NONE && nowState == KS_NONE)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[i] = KS_NONE;
		}
		else if (prevState == KS_NONE && nowState == KS_PRESS)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[i] = KS_PRESS;
		}
		else if (prevState == KS_PRESS && nowState == KS_NONE)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[i] = KS_RELEASE;
		}
		else if (prevState == KS_PRESS && nowState == KS_PRESS)
		{
			GET_INPUT_MANAGER()->m_FinalKeyStates[i] = KS_HOLD;
		}

		GET_INPUT_MANAGER()->m_PrevKeyStates[i] = nowState;
	}
}

void KeyStateSentinel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_PRESS;
}

void KeyStateSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_NONE;
}