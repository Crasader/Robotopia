#include "EquipmentWindow.h"
#include "GameManager.h"
#include "Utils.h"

USING_NS_CC;

bool EquipmentWindow::init()
{
	m_WindowOn = false;

	this->scheduleUpdate();
	return true;
}

void EquipmentWindow::update(float dTime)
{
	KeyState charKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER_UI);

	if (charKey == KS_PRESS)
	{
		if (m_WindowOn == false)
		{
			showCharacterWindow();
			m_WindowOn = true;
		}
		else if (m_WindowOn == true)
		{
			hideCharacterWindow();
			m_WindowOn = false;
		}
	}

}

void EquipmentWindow::showCharacterWindow()
{

}

void EquipmentWindow::hideCharacterWindow()
{

}
