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
	//stage�� �����մϴ�.
	void								changeStage(size_t stageNum, cocos2d::Point nextPlayerPosition);
	//�湮�� ��Ҹ� �߰��մϴ�.
	void								addVisitedStage(int stage);
	//������Ʈ�� Ÿ�԰� ��ġ ���� �޾� ������Ʈ�� GameLayer�� �߰��մϴ�.
	InteractiveObject*					addObject( ObjectType type , cocos2d::Point position );
	InteractiveObject*					addObjectFromStageData( ObjectType type , int xIdx , int yIdx );
	InteractiveObject*					addObjectFromStageData( int xIdx , int yIdx );
	//����Ʈ�� GameLayer�� �߰��մϴ�.
	void								addEffectOnGameLayer(cocos2d::Sprite* effect);
	void								addEffectOnGameLayer( cocos2d::Sprite* effect, cocos2d::Point position, cocos2d::Point anchorPoint );

	//�������� �����͸� �����Ͽ� Ư�� ��ġ�� �ִ� ������Ʈ Ÿ���� �ҷ����ϴ�.
	ObjectType							getStageDataInPosition( cocos2d::Point position );
	ObjectType							getStageDataInPositionWithIdx( int xIdx , int yIdx );
	//�÷ξ� �����͸� �����Ͽ� ���ο� �ִ� �������� ��ȣ�� �ҷ��ɴϴ�.
	int									getFloorDataByIdx( int xIdx , int yIdx );
	std::vector<InteractiveObject*>		getObjectsByPosition( cocos2d::Point checkPosition ); //��ġ�� � ��ü�� �ִ����� ����
	std::vector<InteractiveObject*>		getObjectsByRect( cocos2d::Rect checkRect ); //Rect�� � ��ü�� �ִ����� ����
	
	WorldScene*							getWorldScene(){return m_WorldScene;}
	const Player*						getPlayer();
	const FloorData&					getFloorData(){return m_FloorData;};
	const StageData&					getStageDataByStageNum(int stageNum) { return m_CurrentFloorData[stageNum]; }
	const StageData&					getStageDatas(){return m_CurrentFloorData[m_CurrentStageNum];};
	int									getCurStageNum() {return m_CurrentStageNum; }
	const std::vector<int>&				getVisitedStageNums(){return m_VisitedStageNums;}

	cocos2d::Vec2						positionToIdxOfStage( cocos2d::Point position ); //��ġ���� �޾Ƽ� �ε��� ������ ����
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