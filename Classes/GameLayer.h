#pragma once
#include "cocos2d.h"
#include "Utils.h"
#include "Player.h"

#define MAX_POSITION_NUM 1024*10
#define	MAX_ACTIVE_BOX_NUM 1024*10

class LandGateway;
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
	void							removeObject(InteractiveObject* deleteObject);
	void							initGateways();

	Player*							getPlayer() {return m_Player; }
	std::vector<InteractiveObject*>	getObjectsByPosition( cocos2d::Point checkPosition ); //위치에 어떤 객체가 있는지를 리턴
	std::vector<InteractiveObject*>	getObjectsByRect( cocos2d::Rect checkRect ); //Rect에 어떤 객체가 있는지를 리턴
	cocos2d::Rect					getMapRect(){return m_MapRect; }

	bool							isOutOfStageMap(cocos2d::Point checkPosition);
	cocos2d::Vec2					positionToIdxOfStageData( cocos2d::Point position );
	void							isItShake(bool shakeOrNot) {m_IsShaking = shakeOrNot; }
	void							setIsVisited(bool isVisited) {m_IsVisited = isVisited; }
	bool							getIsVisited() {return m_IsVisited; }
	
	CREATE_FUNC( GameLayer );
private:
	void							addMovingBackground( char* BGpath );
	InteractiveObject*				addObjectByMapdata( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*				addObjectByMapdata( int xIdx , int yIdx );

	void							findActiveObjects();
	void							makeCollisionHashTable();
	void							checkActive();
	void							removeObjects();

	void							collisionCheck( float dTime );
	void							collisionCheckbyHash( InteractiveObject* subject , float dTime );
	void							collisionProc( float dTime );
	
	cocos2d::Rect					getCurWinRect();
	cocos2d::Rect					getCurWinRectByIdx();

	bool							isVisible(cocos2d::Vec2 position);
	bool							isVisibleByIdx( int xIdx , int yIdx );

	void							addToObjectHash();
	void							addToActiveObjects();

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

	bool											m_IsVisited;
	bool											m_IsShaking;
	bool											m_IsInit;
	cocos2d::Rect									m_MapRect;
	cocos2d::Size									m_BoxSize;
	int												m_BoxWidthNum , m_BoxHeightNum;
	Player*											m_Player;

	std::vector<InteractiveObject*>					m_Objects;
	std::vector<LandGateway*>						m_Gateways;
	std::vector<CollisionInformation>				m_CollisionInformations;
	ObjectType										m_MapData[MAX_POSITION_NUM];
	std::list<InteractiveObject*>					m_ActiveObjects; 
	std::vector<InteractiveObject*>					m_AddObjects;
	std::vector<InteractiveObject*>					m_PassiveObjectsHash[MAX_POSITION_NUM];
	std::vector<InteractiveObject*>					m_CollisionCheckHash[MAX_ACTIVE_BOX_NUM];
};

