#include "GameManager.h"
#include "WorldScene.h"

USING_NS_CC;

KeyState InputManager::getKeyState(KeyCode keyCode)
{
	return m_FinalKeyStates[(EventKeyboard::KeyCode)keyCode];
}

void InputManager::receiveKeyboardData(WorldScene* scene)
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

void InputManager::receiveInputData(WorldScene* scene)
{
	receiveKeyboardData(scene);
	receiveMouseData(scene);
}

void InputManager::receiveMouseData(WorldScene* scene)
{
	auto sentinel = MouseStateSentinel::create();

	scene->addChild(sentinel);
}

MouseState InputManager::getMouseState(MouseCode mouseCode)
{
	return m_FinalMouseStates[mouseCode];
}

float InputManager::getMouseWheelState()
{
	return m_MouseWheel;
}

cocos2d::Point InputManager::getMousePosition()
{
	return m_MousePos;
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

	this->scheduleUpdate();

	return true;
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

bool MouseStateSentinel::init()
{
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(MouseStateSentinel::onMouseMove, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(MouseStateSentinel::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(MouseStateSentinel::onMouseDown, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MouseStateSentinel::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->scheduleUpdate();

	return true;
}

void MouseStateSentinel::update(float dTime)
{
	MouseState prevState = GET_INPUT_MANAGER()->m_PrevMouseStates[MC_LEFT];
	MouseState nowState = GET_INPUT_MANAGER()->m_MouseStates[MC_LEFT];

	if (prevState == MS_NONE && nowState == MS_NONE)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_LEFT] = MS_NONE;
	}
	else if (prevState == MS_NONE && nowState == MS_PRESS)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_LEFT] = MS_PRESS;
	}
	else if (prevState == MS_PRESS && nowState == MS_NONE)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_LEFT] = MS_RELEASE;
	}
	else if (prevState == MS_PRESS && nowState == MS_PRESS)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_LEFT] = MS_HOLD;
	}

	prevState = GET_INPUT_MANAGER()->m_PrevMouseStates[MC_RIGHT];
	nowState = GET_INPUT_MANAGER()->m_MouseStates[MC_RIGHT];

	if (prevState == MS_NONE && nowState == MS_NONE)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_RIGHT] = MS_NONE;
	}
	else if (prevState == MS_NONE && nowState == MS_PRESS)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_RIGHT] = MS_PRESS;
	}
	else if (prevState == MS_PRESS && nowState == MS_NONE)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_RIGHT] = MS_RELEASE;
	}
	else if (prevState == MS_PRESS && nowState == MS_PRESS)
	{
		GET_INPUT_MANAGER()->m_FinalMouseStates[MC_RIGHT] = MS_HOLD;
	}
}

void MouseStateSentinel::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	int buttonType = e->getMouseButton();
	
	if (buttonType == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseStates[MC_LEFT] = MS_PRESS;
	}
	else if (buttonType == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseStates[MC_RIGHT] = MS_PRESS;
	}
}

void MouseStateSentinel::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	int buttonType = e->getMouseButton();

	if (buttonType == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseStates[MC_LEFT] = MS_RELEASE;
	}
	else if (buttonType == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseStates[MC_RIGHT] = MS_RELEASE;
	}
}

void MouseStateSentinel::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	GET_INPUT_MANAGER()->m_MousePos.x = e->getCursorX();
	GET_INPUT_MANAGER()->m_MousePos.y = e->getCursorY();
}

void MouseStateSentinel::onMouseScroll(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	GET_INPUT_MANAGER()->m_MouseWheel = e->getScrollY();
}
