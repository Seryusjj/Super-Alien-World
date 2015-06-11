#include "HelloWorldScene.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;
#define PLAYER_TAG 10

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, -2000));
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int numBg = (48 * 128) / 1280;
	auto nextPos = 0.5;
	auto height = visibleSize.height*0.5;
	for (int i = 0;i <= numBg; i++){
		auto bg= Sprite::create("colored_grass.png");
		bg->setPosition(visibleSize.width*nextPos, height);
		nextPos += 1;
		addChild(bg);
	}


	//1 spritesheet por capa o solo renderizo uno de ellos ... basura
	map = TMXTiledMap::create("nivel1.tmx");
	addChild(map);

	auto groundObjLayer = map->getObjectGroup("ground");
	ValueMap groundCollider = groundObjLayer->getObject("groundCollider");
	auto line = groundCollider["polylinePoints"].asValueVector();

	auto xOffset = groundCollider["x"].asFloat();
	auto yOffset = groundCollider["y"].asFloat();

	auto lineDrawer = DrawNode::create();
	for (int i = 0; i < line.size() - 1; i++){
		auto originValue = line.at(i).asValueMap();
		auto destinationValue = line.at(i+1).asValueMap();
		Point origin(xOffset + originValue["x"].asFloat(), (yOffset - originValue["y"].asFloat()));
		Point destination(xOffset + destinationValue["x"].asFloat(), (yOffset - destinationValue["y"].asFloat()));
		//fisica
		auto physicsBody = PhysicsBody::createEdgeSegment(origin, destination);
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
		

		auto node = Node::create();
		node->setTag(GROUND_TAG);
		node->setPhysicsBody(physicsBody);
		addChild(node);

		//debug
		lineDrawer->drawLine(origin, destination, Color4F::ORANGE);
	}
	addChild(lineDrawer);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist", "player.png");
	auto _gameBatchNode = SpriteBatchNode::create("player.png");
	addChild(_gameBatchNode);

	

	_player = Player::create();
	_player->setPosition(visibleSize.width*0.5, visibleSize.height*0.3);
	_gameBatchNode->addChild(_player);

	_cameraTarget = Node::create();
	addChild(_cameraTarget);


	_cameraTarget->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.5));
	_camera = Follow::create(_cameraTarget, Rect::ZERO);

	runAction(_camera);

	scheduleUpdate();


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies.plist", "enemies.png");
	auto _gameBatchNode1 = SpriteBatchNode::create("enemies.png");
	addChild(_gameBatchNode1);
	auto enemy = Enemy::create();
	enemy->setPosition(visibleSize.width*1.5, visibleSize.height*0.6);
	_gameBatchNode1->addChild(enemy);

	auto enemy1 = Enemy::create();
	enemy1->setPosition(visibleSize.width, visibleSize.height*0.3);
	_gameBatchNode1->addChild(enemy1);

    return true;
}

void HelloWorld::update(float dt)
{

	_cameraTarget->setPositionX(_player->getPositionX());
}





