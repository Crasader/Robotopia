#pragma once

#include "cocos2d.h"
#include "WorldScene.h"
#include "Player.h"
#include "Monster.h"

#define MAX_STAGE_NUM 10
#define MAX_STAGE_SIZE 5000

struct StaticStageData
{
	int x , y;
	int width , height;
	ObjectType data[MAX_STAGE_SIZE];
};

class StageManager
{
public:
	bool								init();
	bool								initFloor(int floorNum);
	//stage를 변경합니다.
	void								changeStage(int stageNum, cocos2d::Point nextPlayerPosition);
	void								changeFloor(int floorNum);
	//방문한 장소를 추가합니다.
	void								addVisitedStage(int stage);
	//오브젝트의 타입과 위치 값을 받아 오브젝트를 GameLayer에 추가합니다.
	InteractiveObject*					addObject( ObjectType type , cocos2d::Point position );
	//이펙트를 GameLayer에 추가합니다.
	void								addEffectOnGameLayer(cocos2d::Sprite* effect);
	void								addEffectOnGameLayer( cocos2d::Sprite* effect, cocos2d::Point position, cocos2d::Point anchorPoint );
	//스테이지 데이터를 참조하여 특정 위치에 있는 오브젝트 타입을 불러냅니다.
	ObjectType							getStageDataInPosition( cocos2d::Point position );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx , int stageNum);
	//플로어 데이터를 참조하여 색인에 있는 스테이지 번호를 불러옵니다.
	int									getFloorDataByIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>		getObjectsByPosition( cocos2d::Point checkPosition ); //위치에 어떤 객체가 있는지를 리턴
	std::vector<InteractiveObject*>		getObjectsByRect( cocos2d::Rect checkRect ); //Rect에 어떤 객체가 있는지를 리턴
	
	//멤버변수들 정보조회
	WorldScene*							getWorldScene();
	Player*								getPlayer();
	const FloorData&					getFloorData(){return m_FloorData;};
	const StaticStageData&				getStageDataByStageNum( int stageNum );
	const StaticStageData&				getStageDatas();
	cocos2d::Rect						getStageRect();
	int									getCurrentFloorNum() {return m_CurrentFloorNum; }
	int									getCurStageNum() {return m_CurrentStageNum; }
	const std::vector<int>&				getVisitedStageNums(){return m_VisitedStageNums;}

	//게임상 위치값을 받아서 인덱스 값으로 리턴
	cocos2d::Vec2						positionToIdxOfStage( cocos2d::Point position ); 
	cocos2d::Vec2						positionToIdxOfFloor( cocos2d::Point position );
	cocos2d::Point						idxOfStageDataToPosiion( cocos2d::Vec2 idx ); //인덱스값을 받아서 위치값으로 리턴
	bool								isVisited( int stageNum );
	bool								isVisited();

	bool								accumultateTime( float dTime );
	void								initLastMonster( float dTime );
	Monster*							getLastMonster() {return m_LastHitMonster; }
	void								setLastMonster(Monster* monster) {m_LastHitMonster = monster;}
	void								savePlayerInfo();
	void								showStore();
	void								hideStore();

private:
	void								initData();
	void								loadPlayer( cocos2d::Point setPosition );
	void								makeStaticData();
	void								shakeFloor();

private:
	Monster*							m_LastHitMonster;
	static float						m_accTimeForShake;
	//플레이어 세이브 로드하는 과정에 잘못된 플레이어 참조를 막기위한 플래그
	bool								m_IsAvailable;
	cocos2d::Size						m_BoxSize;
	std::vector<int>					m_VisitedStageNums;
	int									m_CurrentStageNum;
	int									m_CurrentFloorNum;
	std::vector<StageData>				m_CurrentFloorStagesData;
	FloorData							m_FloorData;
	//성능이슈로 정적 배열로 데이터 따로 관리합니다.
	StaticStageData						m_StaticStageDatas[MAX_STAGE_NUM];
	std::map<int, WorldScene*>			m_WorldScenes;
	WorldScene*							m_CurrentWorldScene;
	PlayerInfo							m_PlayerInfo;
};