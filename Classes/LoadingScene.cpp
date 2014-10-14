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

//�̰� ���� �Ȼ��� ����ȭ�� �㶧���� �ε�ȭ��, �뷡���� �ȳ��ɴϴ�.
void LoadingScene::initGame(float unused)
{
	GET_STAGE_MANAGER()->changeFloor( 1 );
}

