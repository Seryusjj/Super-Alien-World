#include "Level3.h"


USING_NS_CC;
using namespace Levels;
using namespace Levels;

Scene* Level3::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, -2000));
	auto layer = Level3::create();
	scene->addChild(layer);
	return scene;
}

bool Level3::init(){
	if (!Level1::init()){
		return false;
	}
	return true;
}

void Level3::setLevel(){
	setTag(3);
	_levelName = "nivel3.tmx";
	_bgName = "colored_shroom.png";
}

void Level3::respawnButtonAction(){
	Director::getInstance()->replaceScene(Level3::createScene());
}