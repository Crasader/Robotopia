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
	m_Type = OT_GATEWAY;
	m_OpenAnimaion = GET_RESOURCE_MANAGER()->createAnimation( AT_GATEWAY_ACT , 0.5f );
	m_OpenAnimaion->retain();
	m_isOpen = false;
	m_CurStageNum = GET_STAGE_MANAGER()->getCurStageNum();
	m_LinkingPoint = Point( 90 , 90 );
	return true;
}

void LandGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( !m_isOpen && enemy->getType() == OT_PLAYER && m_IsActive &&GET_INPUT_MANAGER()->getKeyState(KC_UP))
	{
		CCLOG( "%d\n" , m_NextFloorNum );
		m_isOpen = true;
		auto animate = Animate::create( m_OpenAnimaion );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandGateway::gotoNextLevel , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}
//���� ����Ʈ���̰� ���� ����Ǿ��ִ����� üũ�ϰ� ������ �����ϴ� �Լ�
void LandGateway::findNextStage()
{
	Point curPos = this->getPosition();
	//���� ��ġ�� ���� ���������� �ε������� ã���ϴ�.
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).y;
	m_NextDirection = findCentinelNeighborDir( Vec2( stageXIdx , stageYIdx ) );
	if( m_NextDirection == DIR_UP )
	{
		int x = 0;
	}
	//�ε��������� ����� ������ ��Ƽ�������� üũ�Ͽ� ���� �̵��� ���� ������ ã���ϴ�.
	int floorXIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).x;
	int floorYIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).y;
	m_NextFloorIdx = findNeighbor( Vec2( floorXIdx , floorYIdx ) , m_NextDirection );
	m_NextFloorNum = GET_STAGE_MANAGER()->getFloorDataByIdx( m_NextFloorIdx.x , m_NextFloorIdx.y );

	//���� �̵��� ���� floor��ǥ�� �� ��ǥ���� �־��� �������� �̵��Ͽ� ã���ϴ�.
	//���� ���� floor��ǥ�� ����Ͽ� ���� �̵��� ���� ��ȣ�� ã���ϴ�.

	if( m_NextFloorNum == 0 )
	{
		this->removeChild( m_MainSprite );
		m_IsActive = false;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayUnactive.png" );
		this->addChild( m_MainSprite );
		//���º�ȭ �κ��� ���߿� ���ϸ��̼����� �ٲ���� �մϴ�.
	}
	else
	{
		this->removeChild( m_MainSprite );
		m_IsActive = true;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayActive.png" );
		this->addChild( m_MainSprite );
		m_LinkingPoint = findNextPosition();
	}
}

//���� ������ �̵��Ҷ� �Ҹ��� �ݹ��Լ�.
void LandGateway::gotoNextLevel(Ref* sender)
{
	//���� ���� ������ �������ִ� �Լ�ȣ��
	GET_STAGE_MANAGER()->changeStage( m_NextFloorNum, m_LinkingPoint );
}

//���� ��ġ���� ��Ƽ���� �ִ� ������ �������ݴϴ�.
Direction LandGateway::findCentinelNeighborDir( Vec2 stageIdx )
{
	return findCentinelNeighborDir( stageIdx , m_CurStageNum );
}

Direction LandGateway::findCentinelNeighborDir( Vec2 stageIdx ,int stageNum )
{
	int result = 1;
	while( result < 16 )
	{
		int xIdx = findNeighbor( stageIdx , ( Direction )result ).x;
		int yIdx = findNeighbor( stageIdx , ( Direction )result ).y;
		if( GET_STAGE_MANAGER()->getStageDataInPositionWithIdx( xIdx , yIdx, stageNum ) == OT_SENTINEL )
		{
			break;
		}
		//dir�� ��Ʈ ������ �Ǿ��־ *2�մϴ�.
		result *= 2;
	}
	return ( Direction )result;
}


//������ġ���� �־��� �������� �̵������� ������ ���Ͱ��� �����մϴ�.
Vec2 LandGateway::findNeighbor( cocos2d::Vec2 Idx , Direction dir )
{
	int x = Idx.x;
	int y = Idx.y;

	switch( dir )
	{
		case DIR_LEFT:
			x--;
			break;
		case DIR_RIGHT:
			x++;
			break;
		case DIR_UP:
			y++;
			break;
		case DIR_DOWN:
			y--;
			break;
		default:
			break;
	}
	return Vec2( x , y );
}


Direction LandGateway::findReverseDirection( Direction dir )
{
	Direction resultDir = DIR_NONE;
	switch( dir )
	{
		case DIR_LEFT:
			resultDir = DIR_RIGHT;
			break;
		case DIR_UP:
			resultDir = DIR_DOWN;
			break;
		case DIR_RIGHT:
			resultDir = DIR_LEFT;
			break;
		case DIR_DOWN:
			resultDir = DIR_UP;
			break;
		default:
			break;
	}
	return resultDir;
}

Point LandGateway::findNextPosition()
{
	StageData nextStageData = GET_STAGE_MANAGER()->getStageDataByStageNum( m_NextFloorNum );
	
	int transedStageXIdx = (m_NextFloorIdx.x - nextStageData.x)*MODULE_BASE_WIDTH; //FloorIdx������ �߸� ��ġ���� �������� Idx�� �����´�.
	int transedStageYIdx = ( m_NextFloorIdx.y - nextStageData.y )*MODULE_BASE_HEIGHT;
	Vec2 nextGatewayIdx = Vec2::ZERO;

	Direction setDirection = findReverseDirection( m_NextDirection );

	for( int xIdx = transedStageXIdx; xIdx < nextStageData.width; ++xIdx )
	{
		for( int yIdx = transedStageYIdx; yIdx < nextStageData.height; ++yIdx )
		{
			if( nextStageData.data[yIdx*nextStageData.width + xIdx] == OT_GATEWAY &&
				findCentinelNeighborDir( Vec2( xIdx , yIdx ) , m_NextFloorNum ) == setDirection )
			{
				nextGatewayIdx.x = xIdx;
				nextGatewayIdx.y = yIdx;
				break;
			}
		}
	}
	Point nextSettingPosition = adjustSettingPosition( nextGatewayIdx , m_NextDirection );
	return nextSettingPosition;
}

cocos2d::Point LandGateway::adjustSettingPosition( cocos2d::Vec2 Idx , Direction dir )
{
	switch( dir )
	{
		case DIR_LEFT:
			Idx.x -= 1.5f;
			break;
		case DIR_UP:
			Idx.y += 1.5f;
			break;
		case DIR_RIGHT:
			Idx.x += 1.5f;
			break;
		case DIR_DOWN:
			Idx.y -= 1.5f;
			break;
		default:
			break;
	}
	return GET_STAGE_MANAGER()->idxOfStageDataToPosiion( Idx );
}
