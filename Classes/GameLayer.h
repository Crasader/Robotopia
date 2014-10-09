#pragma once
#include "cocos2d.h"
#include "Utils.h"
#include "Player.h"

class InteractiveObject;
class GameLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene*			createScene();
	OVERRIDE bool					init();  
	OVERRIDE void					update(float dTime);
	bool							initWorldFromData( cocos2d::Vec2 boxNum , cocos2d::Size boxSize , 
													   std::map<int , ObjectType> MapData , char* BGpath);
	void							addEffect( cocos2d::Sprite* sprite );
	InteractiveObject*				addObject( ObjectType type , cocos2d::Point position );
	InteractiveObject*				addObjectByMapdata( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*				addObjectByMapdata( int xIdx , int yIdx );
	void							addMovingBackground(char* BGpath);

	void							collisionCheck(float dTime);
	void							collisionCheckbyHash(InteractiveObject* subject, float dTime);
	void							removeObject();
	void							makeHash();

	const Player*					getPlayer() {return m_Player; }
	ObjectType						getMapDataInPosition( cocos2d::Point position );
	ObjectType						getMapDataInPositionWithIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>	getObjectsByPosition( cocos2d::Point checkPosition ); //위치에 어떤 객체가 있는지를 리턴
	std::vector<InteractiveObject*>	getObjectsByRect( cocos2d::Rect checkRect ); //Rect에 어떤 객체가 있는지를 리턴
	cocos2d::Vec2					positionToIdxOfMapData( cocos2d::Point position ); //위치값을 받아서 인덱스 값으로 리턴

	cocos2d::Rect					getMapRect() {return m_MapRect; }

	CREATE_FUNC( GameLayer );

private:
	enum ZOrder
	{
		BACKGROUND,
		LAND_OBJECT,
		GAME_OBJECT,
		EFFECT,
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

	cocos2d::Rect									m_MapRect;
	cocos2d::Size									m_BoxSize;
	int												m_BoxWidthNum , m_BoxHeightNum;
	Player*											m_Player;
	std::vector<CollisionInformation>				m_CollisionInformations;
	std::map<int , ObjectType>						m_MapData;
	std::vector<InteractiveObject*>					m_InteractiveObjects; 
	std::map<int, std::vector<InteractiveObject*>>	m_ObjectPositionsHash;
};

