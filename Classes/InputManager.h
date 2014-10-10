#pragma once

#include "cocos2d.h"
#include "Utils.h"
#include "WorldScene.h"

enum KeyCode
{
	KC_UP = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
	KC_RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
	KC_DOWN = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
	KC_LEFT = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW,
	KC_FLY = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT,
	KC_ATTACK = cocos2d::EventKeyboard::KeyCode::KEY_A,
	KC_JUMP = cocos2d::EventKeyboard::KeyCode::KEY_SPACE,
	KC_TEST1 = cocos2d::EventKeyboard::KeyCode::KEY_F1,
	KC_TEST2 = cocos2d::EventKeyboard::KeyCode::KEY_F2,
	KC_MENU = cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE,
	KC_CHARACTER_UI = cocos2d::EventKeyboard::KeyCode::KEY_C,
	KC_RETURN = cocos2d::EventKeyboard::KeyCode::KEY_ENTER,
};

enum KeyState
{
	KS_NONE, // 뗀 상태
	KS_PRESS, //딱 누름
	KS_HOLD, //꾹 누르는 중
	KS_RELEASE, // 딱 뗌
};

enum MouseState
{
	MS_NONE = KS_NONE,
	MS_PRESS = KS_PRESS,
	MS_HOLD = KS_HOLD,
	MS_RELEASE = KS_RELEASE,
};

enum MouseCode
{
	MC_LEFT,
	MC_RIGHT,
};

class InputManager
{
	friend class KeyStateSentinel;
	friend class MouseStateSentinel;

public:	
	bool													init();
	KeyState												getKeyState(KeyCode keyCode);
	void													receiveInputData(WorldScene* scene);	//호출하면 모든 인풋 정보가 자동으로 업데이트됨.
	void													receiveKeyboardData(WorldScene* scene); //호출하면 키보드 정보가 자동으로 업데이트됨.
	void													receiveMouseData(WorldScene* scene); //호출하면 마우스 정보가 자동으로 업데이트됨.
	MouseState												getMouseState(MouseCode mouseCode);
	float													getMouseWheelState();
	cocos2d::Point											getMousePosition();
private:
	std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_KeyStates;
	std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_PrevKeyStates;
	std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_FinalKeyStates;
	std::map<MouseCode, MouseState>							m_MouseStates;
	std::map<MouseCode, MouseState>							m_PrevMouseStates;
	std::map<MouseCode, MouseState>							m_FinalMouseStates;
	float													m_MouseWheel;
	cocos2d::Point											m_MousePos;
};

class KeyStateSentinel : public cocos2d::Node
{
	friend class InputManager;

public:
	OVERRIDE bool	init();

	void			onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void			onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void			update(float dTime);

	CREATE_FUNC(KeyStateSentinel);
private:
};

class MouseStateSentinel : public cocos2d::Node
{
	friend class InputManager;
	
public:
	OVERRIDE bool init();

	void onMouseDown(cocos2d::Event *event);
	void onMouseUp(cocos2d::Event *event);
	void onMouseMove(cocos2d::Event *event);
	void onMouseScroll(cocos2d::Event *event);

	void update(float dTime);

	CREATE_FUNC(MouseStateSentinel);
private:
};