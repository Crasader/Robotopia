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
	if (m_Player == nullptr)
	{
		return;
	}
}

void EquipmentWindow::showCharacterWindow()
{

}

void EquipmentWindow::hideCharacterWindow()
{

}
