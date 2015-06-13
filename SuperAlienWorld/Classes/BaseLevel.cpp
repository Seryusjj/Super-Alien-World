#include "BaseLevel.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "Tags.h"
#include "GameManager.h"
#include "SelectMenuLayer.h"
#include "MainMenuLayer.h"


USING_NS_CC;


Scene* BaseLevel::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, -2000));
	auto layer = BaseLevel::create();
	scene->addChild(layer);
	return scene;
}


bool BaseLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setLevel();
	initVariables();
	createGround();
	createWall();
	createWinningArea();
	createEnemies();
	scheduleUpdate();
	createRespawnButton();
	createBackButton();
	return true;
}

void BaseLevel::createBackButton(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainMenu.plist", "mainMenu.png");
	_backBt = ui::Button::create("back0", "back1", "back1", ui::Widget::TextureResType::PLIST);
	_backBt->setAnchorPoint(Point(0, 0.5));
	_backBt->setVisible(false);
	_backBt->setEnabled(false);
	_backBt->setScale(2);
	_backBt->addClickEventListener(CC_CALLBACK_0(BaseLevel::actionButtonBack, this));
	addChild(_backBt);
}

void BaseLevel::actionButtonBack(){
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, MainMenuLayer::createScene()));
}

void BaseLevel::setLevel(){
	setTag(1);//level1
	
	_levelName = "nivel1.tmx";
	_bgName = "colored_grass.png";
}

void BaseLevel::initCamera(){
	_cameraTarget = Node::create();
	addChild(_cameraTarget);

	_cameraTarget->setPosition(Point(_visibleSize.width*0.5, _visibleSize.height*0.5));
	_camera = Follow::create(_cameraTarget, Rect::ZERO);

	runAction(_camera);
}

void BaseLevel::createBackground(){
	_map = TMXTiledMap::create(_levelName);
	_visibleSize = Director::getInstance()->getVisibleSize();
	int  numBg = ((_map->getMapSize().width * _map->getTileSize().width) / 1280) + 1;
	auto nextPos = 0.5;
	auto height = _visibleSize.height*0.5;
	for (int i = 0; i <= numBg; i++){
		auto bg = Sprite::create(_bgName);
		bg->setPosition(_visibleSize.width*nextPos, height);
		nextPos += 1;
		addChild(bg);
	}
	addChild(_map);
}

void BaseLevel::initVariables(){
	createBackground();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist", "player.png");
	auto _gameBatchNode = SpriteBatchNode::create("player.png");
	addChild(_gameBatchNode);

	_player = Player::create();
	_player->setPosition(_visibleSize.width*0.5, _visibleSize.height*0.3);
	_gameBatchNode->addChild(_player);

	initCamera();
}

void BaseLevel::createWall(){
	auto groundObjLayer = _map->getObjectGroup("wall");
	auto values = groundObjLayer->getObjects();
	for (int i = 0; i < values.size(); i++){
		ValueMap groundCollider = values.at(i).asValueMap();
		auto line = groundCollider["polylinePoints"].asValueVector();

		auto xOffset = groundCollider["x"].asFloat();
		auto yOffset = groundCollider["y"].asFloat();

		//auto lineDrawer = DrawNode::create();
		for (int i = 0; i < line.size() - 1; i++){
			auto originValue = line.at(i).asValueMap();
			auto destinationValue = line.at(i + 1).asValueMap();
			Point origin(xOffset + originValue["x"].asFloat(), (yOffset - originValue["y"].asFloat()));
			Point destination(xOffset + destinationValue["x"].asFloat(), (yOffset - destinationValue["y"].asFloat()));

			//fisica
			createPhysicsBodyFromPoints(origin, destination, WALL_TAG);

			//debug
			//lineDrawer->drawLine(origin, destination, Color4F::ORANGE);
		}
		//addChild(lineDrawer);
	}

}


void BaseLevel::createGround(){
	auto groundObjLayer = _map->getObjectGroup("ground");
	auto values = groundObjLayer->getObjects();
	for (int i = 0; i < values.size(); i++){
		ValueMap groundCollider = values.at(i).asValueMap();
		auto line = groundCollider["polylinePoints"].asValueVector();

		auto xOffset = groundCollider["x"].asFloat();
		auto yOffset = groundCollider["y"].asFloat();

		//auto lineDrawer = DrawNode::create();
		for (int i = 0; i < line.size() - 1; i++){
			auto originValue = line.at(i).asValueMap();
			auto destinationValue = line.at(i + 1).asValueMap();
			Point origin(xOffset + originValue["x"].asFloat(), (yOffset - originValue["y"].asFloat()));
			Point destination(xOffset + destinationValue["x"].asFloat(), (yOffset - destinationValue["y"].asFloat()));

			//fisica
			createPhysicsBodyFromPoints(origin, destination, GROUND_TAG);

			//debug
			//lineDrawer->drawLine(origin, destination, Color4F::ORANGE);
		}
		//addChild(lineDrawer);
	}
}

void BaseLevel::createWinningArea(){
	auto winningLayer = _map->getObjectGroup("winning");
	ValueMap door = winningLayer->getObject("door");
	auto line = door["polylinePoints"].asValueVector();

	auto xOffset = door["x"].asFloat();
	auto yOffset = door["y"].asFloat();

	//auto lineDrawer = DrawNode::create();
	for (int i = 0; i < line.size() - 1; i++){
		auto originValue = line.at(i).asValueMap();
		auto destinationValue = line.at(i + 1).asValueMap();
		Point origin(xOffset + originValue["x"].asFloat(), (yOffset - originValue["y"].asFloat()));
		Point destination(xOffset + destinationValue["x"].asFloat(), (yOffset - destinationValue["y"].asFloat()));
		//fisica
		createPhysicsBodyFromPoints(origin, destination, WINNING_AREA);
		//debug
		//lineDrawer->drawLine(origin, destination, Color4F::ORANGE);
	}
	//addChild(lineDrawer);
}

void BaseLevel::createPhysicsBodyFromPoints(cocos2d::Point& origin, cocos2d::Point& destination, int tag){
	auto physicsBody = PhysicsBody::createEdgeSegment(origin, destination);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);

	auto node = Node::create();
	node->setTag(tag);
	node->setPhysicsBody(physicsBody);
	addChild(node);
}




void BaseLevel::createEnemies(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies.plist", "enemies.png");
	auto _gameBatchNode1 = SpriteBatchNode::create("enemies.png");
	addChild(_gameBatchNode1);
	auto enemyLayer = _map->getLayer("enemies");
	auto layerSize = enemyLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++){
		for (int j = 0; j < layerSize.height; j++){
			auto GID = enemyLayer->getTileGIDAt(Point(i, j));
			if (GID != 0) {
				auto enemy = EnemyFactory::getInstance()->getEnemy(GID);
				enemy->setPosition(tileCoordinateToCocosPosition(layerSize, Point(i, j)));
				_gameBatchNode1->addChild(enemy);
			}
		}
	}
	//discard the tile layer
	enemyLayer->getParent()->removeChild(enemyLayer);
}

Point BaseLevel::tileCoordinateToCocosPosition(Size layerSize, Point tileCoordinate){
	//anchor point (0.5 0.5) -> layerSize.width / 2
	float x = floor(layerSize.width / 2 * getScaleX() + tileCoordinate.x * _map->getTileSize().width * getScaleX());
	//recuerda que el eje Y esta invertido
	float y = floor(layerSize.height / 2 * getScaleY() + (layerSize.height-tileCoordinate.y) * _map->getTileSize().height * getScaleY());
	//return a cocos 2d position
	return Point(x, y);
}



void BaseLevel::update(float dt)
{
	_cameraTarget->setPositionX(_player->getPositionX());
	if (_player->_winner){
		levelCompleteActions();
		unscheduleUpdate();
	}
	else if (_player->_dead){
		//launch respawn button
		_respawnButton->setPosition(Point(_player->getPositionX(), _visibleSize.height*0.5));
		_respawnButton->setVisible(true);
		_respawnButton->setEnabled(true);
		_backBt->setPosition(Point(_player->getPositionX() - _visibleSize.width*0.45, 50 * getScaleY()));
		_backBt->setEnabled(true);
		_backBt->setVisible(true);
	}
}

void BaseLevel::createRespawnButton()
{
	_respawnButton = ui::Button::create("respawn0.png", "respawn1.png", "respawn1.png");
	_respawnButton->setScale(0.5);
	_respawnButton->setPosition(Point(_player->getPositionX(), _visibleSize.height*0.5));
	_respawnButton->setVisible(false);
	_respawnButton->setEnabled(false);
	_respawnButton->addClickEventListener(CC_CALLBACK_0(BaseLevel::respawnButtonAction, this));
	addChild(_respawnButton);
}

void BaseLevel::respawnButtonAction(){
	Director::getInstance()->replaceScene(BaseLevel::createScene());
}


void BaseLevel::levelCompleteActions(){
		float aniTime = 2.0f;
		auto winnerLabel = Label::createWithTTF("Level completed", "fonts/arial.ttf", 100);
		winnerLabel->setTextColor(Color4B::ORANGE);
		winnerLabel->setPosition(Point(_player->getPositionX(), _visibleSize.height - 100 * getScaleY()));
		addChild(winnerLabel);
		GameManager::getInstance()->saveGame(getTag());

		auto moveTo = MoveTo::create(aniTime, Point(_player->getPositionX(), _visibleSize.height *0.5));
		winnerLabel->runAction(moveTo);

		CallFunc *loadMenu = CallFunc::create(CC_CALLBACK_0(BaseLevel::levelCompleteActionsHelper, this));
		DelayTime *delayAction = DelayTime::create(aniTime);
		auto sequence = Sequence::create(delayAction, loadMenu, NULL);
		runAction(sequence);
}

void BaseLevel::levelCompleteActionsHelper(){
	Director::getInstance()->replaceScene(SelectMenuLayer::createScene());
}