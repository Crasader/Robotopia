#include "LoadingScene.h"
#include "GameManager.h"
USING_NS_CC;

cocos2d::Scene* LoadingScene::createScene()
{
	LoadingScene* scene = LoadingScene::create();
	return scene;
}

bool LoadingScene::init()
{
	auto layer = Layer::create();
	this->addChild( layer );
	auto spr = GET_RESOURCE_MANAGER()->createSprite("Loading.png");
	auto winSize = Director::getInstance()->getWinSize();
	spr->setScaleX( winSize.width / spr->getContentSize().width );
	spr->setScaleY( winSize.height / spr->getContentSize().height );
	spr->setAnchorPoint( Point::ZERO );
	spr->setPosition( Point::ZERO );
	layer->addChild( spr );
	m_Mutex = true;
	GET_EFFECT_MANAGER()->createSound( SoundType::SO_SCENE1_BGM , true );
	this->scheduleOnce(schedule_selector(LoadingScene::initGame),0);
	return true;
}

//이걸 따로 안빼면 게임화면 뜰때까지 로딩화면, 노래먼저 안나옵니다.
void LoadingScene::initGame(float unused)
{
	GET_STAGE_MANAGER()->changeFloor( 1 );
}

