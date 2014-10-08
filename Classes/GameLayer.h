#pragma once
#include "cocos2d.h"
#include "Utils.h"
#include "Player.h"

#define MAX_DATA_SIZE 1024*10 

class InteractiveObject;
class GameLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene*			createScene();
	OVERRIDE bool					init();  
	OVERRIDE void					update(float dTime);
	bool							initWorldFromData();
	void							gotoNextWorld();

	InteractiveObject*				addObject( ObjectType type , cocos2d::Point position );
	InteractiveObject*				addObjectByMapdata( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*				addObjectByMapdata( int xIdx , int yIdx );
	void							addMovingBackground();

	void							collisionCheck(float dTime);
	void							removeObject();

	const Player*					getPlayer() {return m_Player; }
	ObjectType						getMapData( cocos2d::Point position );
	ObjectType						getMapData( int xIdx , int yIdx );
	std::vector<InteractiveObject*>	getObjectsByPosition( cocos2d::Point checkPosition ); //��ġ�� � ��ü�� �ִ����� ����
	std::vector<InteractiveObject*>	getObjectsByRect( cocos2d::Rect checkRect ); //Rect�� � ��ü�� �ִ����� ����
	cocos2d::Vec2					positionToIdxOfMapData( cocos2d::Point position ); //��ġ���� �޾Ƽ� �ε��� ������ ����

	cocos2d::Rect					getMapRect() {return m_MapRect; }
	cocos2d::Rect					getWinRect() {return m_WinRect; }

	CREATE_FUNC( GameLayer );

private:
	enum ZOrder
	{
		BACKGROUND,
		LAND_OBJECT,
		GAME_OBJECT,
	};

	struct CollisionInformation
	{
		CollisionInformation( InteractiveObject* sub , InteractiveObject* obj , Directions dirs )
		{
			subject = sub;
			object = obj;
			directions = dirs;
		}
		InteractiveObject*	subject;
		InteractiveObject*	object;
		Directions			directions;
	};

	cocos2d::Rect					m_WinRect;
	cocos2d::Rect					m_MapRect;
	cocos2d::Size					m_BoxSize;

	int								m_BoxWidthNum , m_BoxHeightNum;
	Player*							m_Player;
	std::string						m_MapRawData;
	std::map<int , ObjectType>		m_MapData;
	std::vector<InteractiveObject*> m_InteractiveObjects; 
};

