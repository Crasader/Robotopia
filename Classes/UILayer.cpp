#include "UILayer.h"

#include "Minimap.h"
#include "WorldMenu.h"
#include "BarContainer.h"
#include "EquipmentWindow.h"
#include "Gear.h"
#include "StoreWindow.h"

#define DROPSPACE 15

USING_NS_CC;

bool UILayer::init()
{
	return true;
}


void UILayer::update(float dTime)
{
	m_BarContainer->update(dTime);
	m_EquipmentWindow->update(dTime);
	m_Minimap->update(dTime);
	m_WorldMenu->update(dTime);
	m_Gear->update(dTime);

	KeyState charWinKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER_UI);
	KeyState enterKey = GET_INPUT_MANAGER()->getKeyState(KC_RETURN);
	KeyState mapWinKey = GET_INPUT_MANAGER()->getKeyState(KC_MAP);
	KeyState escKey = GET_INPUT_MANAGER()->getKeyState(KC_MENU);
	KeyState downKey = GET_INPUT_MANAGER()->getKeyState(KC_DOWN);
	KeyState upKey = GET_INPUT_MANAGER()->getKeyState(KC_UP);

	if (m_StoreWindow->getStoreWindowOn() == true)
	{
		m_EquipmentWindow->showCharacterWindow();
	}

	if (charWinKey == KS_PRESS)
	{
		if (m_WorldMenu->getWorldMenuOn() == false && m_Minimap->getMinimapWinOn() == false)
		{
			if (m_EquipmentWindow->getCharWinOn() == false)
			{
				m_EquipmentWindow->showCharacterWindow();
			}
			else if (m_EquipmentWindow->getCharWinOn() == true)
			{
				m_EquipmentWindow->hideCharacterWindow();
			}
		}
	}
	
	if (enterKey == KS_PRESS)
	{

	}
	
	if (mapWinKey == KS_PRESS)
	{
		if (m_WorldMenu->getWorldMenuOn() == false)
		{
			if (m_Minimap->getMinimapWinOn() == false)
			{
				m_Minimap->showMinimapWin();
			}
			else if (m_Minimap->getMinimapWinOn() == true)
			{
				m_Minimap->hideMinimapWin();
			}
		}
	}

	if (escKey == KS_PRESS)
	{
		if (m_WorldMenu->getWorldMenuOn() == false)
		{
			if (m_Minimap->getMinimapWinOn() == true)
			{
				m_Minimap->hideMinimapWin();
			}
			else if (m_StoreWindow->getStoreWindowOn() == true)
			{
				m_StoreWindow->hideStore();
			}
			else if (m_EquipmentWindow->getCharWinOn() == true)
			{
				m_EquipmentWindow->hideCharacterWindow();
			}
			else
			{
				m_WorldMenu->showWorldMenu();
			}
		}
		else
		{
			m_WorldMenu->hideWorldMenu();
		}
	}
}

void UILayer::initializeRobotSetting()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp2, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown2, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove2, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	auto robotSettingSprite = Sprite::create("RobotSetting.png");
	robotSettingSprite->setAnchorPoint(Point(0, 0));
	robotSettingSprite->setPosition(Point(0, 0));
	this->addChild(robotSettingSprite);

	auto testItem1 = Sprite::create("TestItem1.png");
	testItem1->setAnchorPoint(Point(0, 1));
	testItem1->setPosition(Point(122, 212));
	testItem1->setOpacity(170);
	this->addChild(testItem1);

	auto testItem2 = Sprite::create("TestItem1.png");
	testItem2->setAnchorPoint(Point(0, 1));
	testItem2->setPosition(Point(547, 213));
	testItem2->setOpacity(170);
	this->addChild(testItem2);

	auto testItem3 = Sprite::create("TestItem2.png");
	testItem3->setAnchorPoint(Point(0, 1));
	testItem3->setPosition(Point(122, 275));
	testItem3->setOpacity(170);
	this->addChild(testItem3);

	auto testItem4 = Sprite::create("TestItem2.png");
	testItem4->setAnchorPoint(Point(0, 1));
	testItem4->setPosition(Point(612, 352));
	testItem4->setOpacity(170);
	this->addChild(testItem4);

	m_TestItem = Sprite::create("TestItem3.png");
	m_TestItem->setAnchorPoint(Point(0.5, 0.5));
	m_TestItem->setPosition(Point(142, 192));
	this->addChild(m_TestItem);

	m_DragOn = false;
}

void UILayer::initializeUILayer()
{
	auto winSize = Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(UILayer::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	m_BarContainer = BarContainer::create();
	m_EquipmentWindow = EquipmentWindow::create();
	m_Minimap = Minimap::create();
	m_WorldMenu = WorldMenu::create();
	m_Gear = Gear::create();
	m_StoreWindow = StoreWindow::create();

	this->addChild( m_Gear );
	this->addChild( m_BarContainer );
	this->addChild( m_EquipmentWindow );
	this->addChild( m_Minimap );
	this->addChild( m_WorldMenu );
	this->addChild( m_StoreWindow );
}

void UILayer::onMouseDown(Event *event)
{
	m_IsMouseDown = true;
}

void UILayer::onMouseUp(Event *event)
{
	auto ev = static_cast<EventMouse*>(event);
	
	auto button = ev->getMouseButton();
	Point clickPoint;
	clickPoint.x = ev->getCursorX();
	clickPoint.y = m_WinHeight + ev->getCursorY();


	switch (button)
	{
		case MOUSE_BUTTON_LEFT:
		{
			if (m_Minimap->getMinimapWinOn() == false)
			{
				Rect openRect = m_Minimap->getWinOpenRect();
				if (openRect.containsPoint(clickPoint))
				{
					m_Minimap->showMinimapWin();
				}
			}
			else if (m_Minimap->getMinimapWinOn() == true)
			{
				Rect closeRect = m_Minimap->getWinCloseRect();
				if (closeRect.containsPoint(clickPoint))
				{
					m_Minimap->hideMinimapWin();
				}
			}
			if (m_EquipmentWindow->getCharWinOn() == false && m_Minimap->getMinimapWinOn() == false)
			{
				Rect triggerRect = m_EquipmentWindow->getTriggerRect();
				if (triggerRect.containsPoint(clickPoint))
				{
					m_EquipmentWindow->showCharacterWindow();
				}
			}
			break;
		}
		case MOUSE_BUTTON_RIGHT:
		{
			if (m_Minimap->getMinimapWinOn() == true)
			{
				m_Minimap->hideMinimapWin();
			}
			else if (m_EquipmentWindow->getCharWinOn() == true)
			{
				m_EquipmentWindow->hideCharacterWindow();
			}
			break;
		}
	}
	m_IsMouseDown = false;
}

void UILayer::onMouseMove(Event *event)
{

}

void UILayer::onMouseScroll(Event *event)
{

}

void UILayer::showStore()
{
	m_StoreWindow->showStore();
	m_EquipmentWindow->showCharacterWindow();
}

void UILayer::hideStore()
{

}

void UILayer::onMouseDown2(cocos2d::Event *event)
{
	auto ev = static_cast<EventMouse*>(event);

	auto button = ev->getMouseButton();
	Point clickPoint;
	clickPoint.x = ev->getCursorX();
	clickPoint.y = m_WinHeight + ev->getCursorY();
	
	switch (button)
	{
		case MOUSE_BUTTON_LEFT:
		{
			Point currentPosition = m_TestItem->getPosition();
			if (clickPoint.x >= currentPosition.x - 20 && clickPoint.x <= currentPosition.x + 20 && clickPoint.y >= currentPosition.y - 20 && clickPoint.y <= currentPosition.y + 20)
			{
				m_prevPoint = Point(142, 192);
				m_DragOn = true;
			}
		}
	}
}

void UILayer::onMouseMove2(cocos2d::Event *event)
{
	auto ev = static_cast<EventMouse*>(event);

	Point mousePosition;
	mousePosition.x = ev->getCursorX();
	mousePosition.y = m_WinHeight + ev->getCursorY();
	
	if (m_DragOn == true)
	{
		if (mousePosition.x < m_WinWidth && mousePosition.x > 0 && mousePosition.y > 0 && mousePosition.y < m_WinHeight)
		{
			m_TestItem->setPosition(Point(mousePosition.x, mousePosition.y));
		}
	}
}

void UILayer::onMouseUp2(cocos2d::Event *event)
{
	auto ev = static_cast<EventMouse*>(event);

	auto button = ev->getMouseButton();
	Point clickPoint;
	clickPoint.x = ev->getCursorX();
	clickPoint.y = m_WinHeight + ev->getCursorY();

	if (m_DragOn == true)
	{
		if (clickPoint.x >= 547 - DROPSPACE && clickPoint.x <= 587 + DROPSPACE && clickPoint.y >= 173 - DROPSPACE && clickPoint.y <= 213 + DROPSPACE)
		{
			m_TestItem->setPosition(Point(567, 193));
		}
		else
		{
			m_TestItem->setPosition(m_prevPoint);
		}
	}

	switch (button)
	{
		case MOUSE_BUTTON_LEFT:
		{
			auto confirmButton = Rect(m_WinWidth - 120, 0, 120, 80);
			if (confirmButton.containsPoint(clickPoint))
			{
				GET_STAGE_MANAGER()->loadingGame();
			}
		}
	}
	m_DragOn = false;
}