#pragma once

#include "cocos2d.h"
#include "WorldScene.h"
#include "Player.h"

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
	//stage�� �����մϴ�.
	void								changeStage(int stageNum, cocos2d::Point nextPlayerPosition);
	//�湮�� ��Ҹ� �߰��մϴ�.
	void								addVisitedStage(int stage);
	//������Ʈ�� Ÿ�԰� ��ġ ���� �޾� ������Ʈ�� GameLayer�� �߰��մϴ�.
	InteractiveObject*					addObject( ObjectType type , cocos2d::Point position );
	//����Ʈ�� GameLayer�� �߰��մϴ�.
	void								addEffectOnGameLayer(cocos2d::Sprite* effect);
	void								addEffectOnGameLayer( cocos2d::Sprite* effect, cocos2d::Point position, cocos2d::Point anchorPoint );
	//�������� �����͸� �����Ͽ� Ư�� ��ġ�� �ִ� ������Ʈ Ÿ���� �ҷ����ϴ�.
	ObjectType							getStageDataInPosition( cocos2d::Point position );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx , int stageNum);
	//�÷ξ� �����͸� �����Ͽ� ���ο� �ִ� �������� ��ȣ�� �ҷ��ɴϴ�.
	int									getFloorDataByIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>		getObjectsByPosition( cocos2d::Point checkPosition ); //��ġ�� � ��ü�� �ִ����� ����
	std::vector<InteractiveObject*>		getObjectsByRect( cocos2d::Rect checkRect ); //Rect�� � ��ü�� �ִ����� ����
	
	//��������� ������ȸ
	WorldScene*							getWorldScene();
	Player*								getPlayer();
	const FloorData&					getFloorData(){return m_FloorData;};
	const StaticStageData&				getStageDataByStageNum( int stageNum );
	const StaticStageData&				getStageDatas();
	cocos2d::Rect						getStageRect();
	int									getCurStageNum() {return m_CurrentStageNum; }
	const std::vector<int>&				getVisitedStageNums(){return m_VisitedStageNums;}

	//���ӻ� ��ġ���� �޾Ƽ� �ε��� ������ ����
	cocos2d::Vec2						positionToIdxOfStage( cocos2d::Point position ); 
	cocos2d::Vec2						positionToIdxOfFloor( cocos2d::Point position );
	cocos2d::Point						idxOfStageDataToPosiion( cocos2d::Vec2 idx ); //�ε������� �޾Ƽ� ��ġ������ ����
	bool								accumultateTime( float dTime );
	Monster*							getLastMonster()

private:
	void								savePlayerInfo();
	void								loadPlayer( cocos2d::Point setPosition );
	void								makeStaticData();
	void								shakeFloor();

private:
	Monster*							m_LastHitMonster;
	static float						m_accTimeForShake;
	bool								m_IsAvailable;
	cocos2d::Size						m_BoxSize;
	std::vector<int>					m_VisitedStageNums;
	int									m_CurrentStageNum;
	int									m_CurrentFloorNum;
	std::vector<StageData>				m_CurrentFloorStagesData;
	FloorData							m_FloorData;
	//�����̽��� ���� �迭�� ������ ���� �����մϴ�.
	StaticStageData						m_StaticStageDatas[MAX_STAGE_NUM];
	std::map<int, WorldScene*>			m_WorldScenes;
	WorldScene*							m_CurrentWorldScene;
	PlayerInfo							m_PlayerInfo;
};