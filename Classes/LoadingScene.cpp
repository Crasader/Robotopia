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
	//GET_EFFECT_MANAGER()->createSound( SoundType::SO_SAGA_BGM , false );
	this->scheduleUpdate();
	return true;
}

void LoadingScene::update(float dTime)
{
	if( m_Mutex )
	{
		m_Mutex = false;
		GET_STAGE_MANAGER()->changeStage( 1 , Point( 100 , 100 ) );
	}
}



