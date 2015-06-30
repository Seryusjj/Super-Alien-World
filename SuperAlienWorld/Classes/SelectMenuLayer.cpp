#include "SelectMenuLayer.h"
#include "GameManager.h"
#include "MainMenuLayer.h"


USING_NS_CC;
using namespace ui;
using namespace Menus;
using namespace Levels;

Scene* SelectMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMenuLayer::create();
	scene->addChild(layer);
	return scene;
}


bool SelectMenuLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}

	std::vector<std::function<void(Ref*)>> functions;
	cocos2d::Vector<Button*> buttons;

	initFunctions(functions);
	//incorpora los botones a la escena
	initButtons(buttons, functions);

	//desbloquea los niveles que se deba
	for (int i = 0; i < NUM_LEVELS; i++){
		if (i>GameManager::getInstance()->getNextLevel()) break;
		//activa el boton
		buttons.at(i)->setEnabled(true);
		//imagen de boton activo
		buttons.at(i)->setBright(true);
	}

	//create back button
	auto backBt = Button::create("back0", "back1", "back1", Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Point(0, 0.5));
	backBt->setScale(2);
	backBt->addClickEventListener(CC_CALLBACK_0(SelectMenuLayer::actionButtonBack, this));
	backBt->setPosition(Point(42.5* getScaleX(), 50 * getScaleY()));
	addChild(backBt); 

	return true;
}

void SelectMenuLayer::initButtons(cocos2d::Vector<Button*>& buttons, std::vector<std::function<void(Ref*)>>& functions){
	int tag = 1;
	int sizeY = 0;
	int sizeX = 0;
	int marginX = 200* getScaleX();
	int marginY = _visibleSize.height *0.6;
	Size last;
	for (int j = 0; j < 2; j++){
		for (int i = 0; i < NUM_LEVELS / 2; i++){
			auto bt = Button::create("level_unlock0", "level_unlock1", "level_lock", Widget::TextureResType::PLIST);
			//deshabilitado
			bt->setEnabled(false);
			//muestra la imagen de boton deshabilitado
			bt->setBright(false);
			//configuracion del resto del boton
			bt->setScale(3);
			bt->addClickEventListener(functions.at(tag - 1));
			bt->setTag(tag); _ostr << tag; tag++;
			bt->setTitleText(_ostr.str()); _ostr.str("");
			bt->setTitleFontSize(18);
			bt->setAnchorPoint(Point(0, 0.5));
			bt->setPosition(Point(marginX, marginY));
			sizeX = bt->getBoundingBox().size.width;
			marginX += bt->getBoundingBox().size.width * 2;
			buttons.pushBack(bt);
			addChild(bt);
			marginX += 42.5* getScaleX();
			last = bt->getBoundingBox().size;

		}
		marginX = 200 * getScaleX();
		marginY -= (last.height + 42.5* getScaleX());
	}
}




void SelectMenuLayer::actionButtonBack()
{
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, MainMenuLayer::createScene()));
}


