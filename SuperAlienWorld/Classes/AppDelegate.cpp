#include "AppDelegate.h"
#include "MainMenuLayer.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


void AppDelegate::initGLContextAttrs()
{

    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}


static int register_all_packages()
{
    return 0; 
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Super alien world");
		
        director->setOpenGLView(glview);
    }
	
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(854, 480);//sony xeria u
#endif
	glview->setDesignResolutionSize(128 * 10, 128 * 7, ResolutionPolicy::EXACT_FIT);

    register_all_packages();

	
	auto scene = MainMenuLayer::createScene();
    director->runWithScene(scene);

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
