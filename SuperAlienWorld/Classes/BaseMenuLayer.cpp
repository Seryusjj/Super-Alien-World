#include "BaseMenuLayer.h"


USING_NS_CC;

Scene* BaseMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BaseMenuLayer::create();
	scene->addChild(layer);
	return scene;
}

BaseMenuLayer::BaseMenuLayer()
{
}


BaseMenuLayer::~BaseMenuLayer()
{
	CC_SAFE_DELETE(_bg);
}
bool BaseMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainMenu.plist", "mainMenu.png");
	_gameBatchNode = SpriteBatchNode::create("mainMenu.png");
	addChild(_gameBatchNode);
	_visibleSize = Director::getInstance()->getVisibleSize();

	//bg
	_bg = new BackGround3Parts();
	_bg->setSpeed(30);
	_bg->setParent(_gameBatchNode);



	scheduleUpdate();
	return true;
}


void BaseMenuLayer::update(float dt){
	_bg->update(dt);
}



