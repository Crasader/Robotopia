//StoreWindow.h
//
//惑痢 UI 备己
//
//累己磊 : 快犁快
//

#pragma once
#include "cocos2d.h"
#include "GameManager.h"

class StoreWindow : public cocos2d::Node
{
public:
	virtual bool		init();
	void				update(float dTime);

	CREATE_FUNC(StoreWindow);

	void				showStore();
	void				hideStore();
	bool				getStoreWindowOn() { return m_StoreWindowOn };

private:
	bool				m_StoreWindowOn;
	
	cocos2d::Sprite*	m_StoreWindowSpr;

};