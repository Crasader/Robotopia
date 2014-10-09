#pragma once

#include "cocos2d.h"
#include "WorldScene.h"
#include "Player.h"

class StageManager
{
public:
	struct PlayerInfo
	{
		int Hp;
		int Steam;
		int MaxHp;
		int MaxSteam;
	};
	bool								init();
	void								changeStage(size_t stageNum);

	InteractiveObject*					addObject( ObjectType type , cocos2d::Point position );
	InteractiveObject*					addObjectByIdx( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*					addObjectByIdx( int xIdx , int yIdx );
	
	void								addEffectOnGameLayer(cocos2d::Sprite* effect);

	ObjectType							getMapDataInPosition( cocos2d::Point position );
	ObjectType							getMapDataInPositionWithIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>		getObjectsByPosition( cocos2d::Point checkPosition ); //위치에 어떤 객체가 있는지를 리턴
	std::vector<InteractiveObject*>		getObjectsByRect( cocos2d::Rect checkRect ); //Rect에 어떤 객체가 있는지를 리턴
	
	WorldScene*							getWorldScene(){return m_WorldScene;}
	const Player*						getPlayer();

private:
	int									m_CurrentFloor;
	std::vector<StageData>				m_CurrentFloorData;
	FloorData							m_FloorData;
	WorldScene*							m_WorldScene;
	PlayerInfo							m_PlayerInfo;
};