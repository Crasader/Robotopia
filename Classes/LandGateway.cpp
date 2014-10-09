#include "LandGateway.h"
#include "GameManager.h"
#include "GameLayer.h"

USING_NS_CC;

bool LandGateway::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayUnactive.png" );
	this->addChild( m_MainSprite );
	m_OpenAnimaion = GET_RESOURCE_MANAGER()->createAnimation( AT_GATEWAY_ACT , 0.5f );
	m_OpenAnimaion->retain();
	m_isOpen = false;
	m_IsActive = false;

	return true;
}

void LandGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( m_isOpen == false && enemy->getType() == OT_PLAYER )
	{
		m_isOpen = true;
		auto animate = Animate::create( m_OpenAnimaion );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandGateway::gotoNextLevel , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}

size_t LandGateway::findNextStageNum()
{
	size_t result = 0;
	Point curPos = this->getPosition();
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).y;
	

	int floorXIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).x;
	int floorYIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).y;
	

	return result;
}

void LandGateway::gotoNextLevel(Ref* sender)
{
	//���� ���� ������ �������ִ� �Լ�ȣ��
}

Direction LandGateway::findNeighborDir( Vec2 stageIdx )
{
	Direction result = DIR_NONE;

	return result;
}

