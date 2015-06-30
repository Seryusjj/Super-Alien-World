#include "Level2.h"

USING_NS_CC;
using namespace Levels;
using namespace Levels;

Scene* Level2::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, -2000));
	auto layer = Level2::create();
	scene->addChild(layer);
	return scene;
}

bool Level2::init(){
	if (!Level1::init()){
		return false;
	}
	return true;
}

void Level2::setLevel(){
	setTag(2);
	_levelName = "nivel2.tmx";
	_bgName = "colored_desert.png";
}

void Level2::respawnButtonAction(){
	Director::getInstance()->replaceScene(Level2::createScene());
}