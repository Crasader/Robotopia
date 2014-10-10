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

	return true;
}

void LandGateway::collisionOccured( InteractiveObject* enemy , Directions dir )
{
	if( !m_isOpen && enemy->getType() == OT_PLAYER && m_IsActive )
	{
		m_isOpen = true;
		auto animate = Animate::create( m_OpenAnimaion );
		auto callfunc = CallFuncN::create( CC_CALLBACK_1( LandGateway::gotoNextLevel , this ) );
		auto action = Sequence::create( animate , callfunc , NULL );
		m_MainSprite->runAction( action );
	}
}
//현재 게이트웨이가 어디와 연결되어있는지를 체크하고 정보를 저장하는 함수
void LandGateway::findNextStage()
{
	auto floorData = GET_STAGE_MANAGER()->getFloorData();
	auto stageData = GET_STAGE_MANAGER()->getStageDatas();

	int floorDataSheet[50][50] = { 0 , };
	int stageDataSheet[50][50] = { 0 , };

	for( int x = 0; x < floorData.width; ++x )
	{
		for( int y = 0; y < floorData.height; ++y )
		{
			floorDataSheet[floorData.height - y - 1][x] = floorData.data[y*floorData.width + x];
		}
	}

	for( int x = 0; x < stageData.width; ++x )
	{
		for( int y = 0; y < stageData.height; ++y )
		{
			stageDataSheet[stageData.height - y - 1][x] = stageData.data[y*stageData.width + x];
		}
	}
	
	Point curPos = this->getPosition();
	//현재 위치로 부터 스테이지의 인덱스값을 찾습니다.
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( curPos ).y;
	Direction sentinelDir = findCentinelNeighborDir( Vec2( stageXIdx , stageYIdx ) );

	//인덱스값으로 어느쪽 방향이 센티넬인지를 체크하여 다음 이동할 방의 방향을 찾습니다.
	int floorXIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).x;
	int floorYIdx = GET_STAGE_MANAGER()->positionToIdxOfFloor( curPos ).y;
	m_NextFloorIdx = findNeighbor( Vec2( floorXIdx , floorYIdx ) , sentinelDir );
	m_NextFloorNum = GET_STAGE_MANAGER()->getFloorDataByIdx( m_NextFloorIdx.x , m_NextFloorIdx.y );

	//다음 이동할 방의 floor좌표를 현 좌표에서 주어진 방향으로 이동하여 찾습니다.
	//다음 방의 floor좌표를 사용하여 다음 이동할 방의 번호를 찾습니다.

	if( m_NextFloorNum != 0 )//다음 이동할 방이 없다면 unactive상태입니다.
	{
		//상태변화 부분을 나중에 에니메이션으로 바꿔줘야 합니다.
		this->removeChild( m_MainSprite );
		m_IsActive = true;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayActive.png" );
		this->addChild( m_MainSprite );
	}
	else
	{
		this->removeChild( m_MainSprite );
		m_IsActive = false;
		m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "GatewayUnactive.png" );
		this->addChild( m_MainSprite );
	}
}

//다음 레벨로 이동할때 불리는 콜백함수.
void LandGateway::gotoNextLevel(Ref* sender)
{
	//다음 월드 씬으로 변경해주는 함수호출
	GET_STAGE_MANAGER()->changeStage( m_NextFloorNum );

}

//현재 위치에서 센티넬이 있는 방향을 리턴해줍니다.
Direction LandGateway::findCentinelNeighborDir( Vec2 stageIdx )
{
	int result = 1;
	while( result < 16 )
	{
		int xIdx = findNeighbor( stageIdx , ( Direction )result ).x;
		int yIdx = findNeighbor( stageIdx , ( Direction )result ).y;
		if( GET_STAGE_MANAGER()->getStageDataInPositionWithIdx(xIdx, yIdx) == OT_SENTINEL )
		{
			break;
		}
		//dir이 비트 단위로 되어있어서 *2합니다.
		result *= 2;
	}
	return ( Direction )result;
}

//현재위치에서 주어진 방향으로 이동헀을때 나오는 벡터값을 리턴합니다.
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

