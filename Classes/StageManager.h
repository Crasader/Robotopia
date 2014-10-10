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
	//stage를 변경합니다.
	void								changeStage(size_t stageNum, cocos2d::Point nextPlayerPosition);
	//방문한 장소를 추가합니다.
	void								addVisitedStage(int stage);
	//오브젝트의 타입과 위치 값을 받아 오브젝트를 GameLayer에 추가합니다.
	InteractiveObject*					addObject( ObjectType type , cocos2d::Point position );
	InteractiveObject*					addObjectFromStageData( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*					addObjectFromStageData( int xIdx , int yIdx );
	//이펙트를 GameLayer에 추가합니다.
	void								addEffectOnGameLayer(cocos2d::Sprite* effect);
	void								addEffectOnGameLayer( cocos2d::Sprite* effect, cocos2d::Point position, cocos2d::Point anchorPoint );

	//스테이지 데이터를 참조하여 특정 위치에 있는 오브젝트 타입을 불러냅니다.
	ObjectType							getStageDataInPosition( cocos2d::Point position );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx );
	//플로어 데이터를 참조하여 색인에 있는 스테이지 번호를 불러옵니다.
	int									getFloorDataByIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>		getObjectsByPosition( cocos2d::Point checkPosition ); //위치에 어떤 객체가 있는지를 리턴
	std::vector<InteractiveObject*>		getObjectsByRect( cocos2d::Rect checkRect ); //Rect에 어떤 객체가 있는지를 리턴
	
	WorldScene*							getWorldScene(){return m_WorldScene;}
	const Player*						getPlayer();
	const FloorData&					getFloorData(){return m_FloorData;};
	const StageData&					getStageDataByStageNum(int stageNum) { return m_CurrentFloorData[stageNum]; }
	const StageData&					getStageDatas(){return m_CurrentFloorData[m_CurrentStageNum];};
	int									getCurStageNum() {return m_CurrentStageNum; }
	const std::vector<int>&				getVisitedStageNums(){return m_VisitedStageNums;}

	cocos2d::Vec2						positionToIdxOfStage( cocos2d::Point position ); //위치값을 받아서 인덱스 값으로 리턴
	cocos2d::Vec2						positionToIdxOfFloor( cocos2d::Point position );

private:
	std::vector<int>					m_VisitedStageNums;
	int									m_CurrentStageNum;
	int									m_CurrentFloor;
	std::vector<StageData>				m_CurrentFloorData;
	FloorData							m_FloorData;
	WorldScene*							m_WorldScene;
	PlayerInfo							m_PlayerInfo;
};