#include "MainMenuLayer.h"

#include "SelectMenuLayer.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "Level2.h"
#include "Level3.h"




USING_NS_CC;
using namespace ui;
using namespace Menus;
using namespace Levels;

Scene* MainMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuLayer::create();
	scene->addChild(layer);
	return scene;
}


bool MainMenuLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}
	initFunctions(_functions);

	auto startButton = Button::create("start0", "start1", "start1", Widget::TextureResType::PLIST);
	startButton->setScale(3);
	startButton->setAnchorPoint(Point(1, 0.5));
	startButton->setPosition(Vec2(_visibleSize.width*0.5 -20*getScaleX(), _visibleSize.height *0.5));
	if (GameManager::getInstance()->getNextLevel() == NUM_LEVELS)
	{
		startButton->addClickEventListener(_functions.at(NUM_LEVELS - 1));
	}
	else
	{
		startButton->addClickEventListener(_functions.at(GameManager::getInstance()->getNextLevel()));
	}
	addChild(startButton);


	auto selectButton = Button::create("select0", "select1", "select1", Widget::TextureResType::PLIST);
	selectButton->setScale(3);
	selectButton->setAnchorPoint(Point(0, 0.5));
	selectButton->setPosition(Vec2(_visibleSize.width*0.5 +20*getScaleX(), _visibleSize.height *0.5));
	selectButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::selectMenuButton, this));
	addChild(selectButton);

	return true;
}



void MainMenuLayer::selectMenuButton(){
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, SelectMenuLayer::createScene()));
}





void MainMenuLayer::initFunctions(std::vector<std::function<void(Ref*)>>& functions){
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton1, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton2, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton3, this));

	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton4, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton5, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton6, this));
}

void MainMenuLayer::actionButton1(){ Director::getInstance()->replaceScene(Level1::createScene()); }
void MainMenuLayer::actionButton2(){ Director::getInstance()->replaceScene(Level2::createScene()); }
void MainMenuLayer::actionButton3(){ Director::getInstance()->replaceScene(Level3::createScene()); }

void MainMenuLayer::actionButton4(){ Director::getInstance()->replaceScene(Level1::createScene()); }
void MainMenuLayer::actionButton5(){ Director::getInstance()->replaceScene(Level2::createScene()); }
void MainMenuLayer::actionButton6(){ Director::getInstance()->replaceScene(Level3::createScene()); }

