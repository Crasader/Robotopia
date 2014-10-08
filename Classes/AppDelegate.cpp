#include "AppDelegate.h"
#include "WorldScene.h"
#include "GameManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	GET_GAME_MANAGER()->releaseInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::createWithRect( "robotopiaPrototype" ,
										 Rect( 0 , 0 , 800 , 600 ));
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false);

    director->setAnimationInterval(1.0 / 60);

	auto scene = WorldScene::create();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}
