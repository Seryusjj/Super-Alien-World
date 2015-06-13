#include "Player.h"
#include "Enemy.h"
#include "Tags.h"

USING_NS_CC;

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initializeVariables();
	createRunAnimation();
	createJumpAnimation();
	setCurrentAnimation(RUN);
	controlsSetUp();
	physicsSetUp();
	scheduleUpdate();
	return true;
}

void Player::initializeVariables(){
	_speed = 180;
	_winner = false;
	_visibleSize = Director::getInstance()->getVisibleSize();
	_grounded = false;
	_dead = false;
	setTag(PLAYER_TAG);
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("alienGreen_front"));
}

void Player::createRunAnimation()
{
	Animation* animation = animation = Animation::create();
	std::string name = "";
	for (int i = 1; i < 3; i++){
		name.append("alienGreen_walk");
		_ostr << i;
		name.append(_ostr.str());
		_ostr.str("");
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
		name = "";
	}
	animation->setDelayPerUnit(0.20f);
	auto animate = Animate::create(animation);
	_runAnimation = RepeatForever::create(animate);
	_runAnimation->setTag(Player::Animations::RUN);
	_runAnimation->retain();
}

void Player::createJumpAnimation(){
	_jumpAnimation = SpriteFrameCache::getInstance()->getSpriteFrameByName("alienGreen_jump");
	_jumpAnimation->retain();
}

void Player::setCurrentAnimation(Animations newAnimation)
{
	if (_currentAnimation == newAnimation)return;
	switch (newAnimation)
	{
	case Animations::RUN:
		runAction(_runAnimation);
		break;
	case Animations::JUMP:
		stopActionByTag(RUN);
		setSpriteFrame(_jumpAnimation);
		break;
	}
	_currentAnimation = newAnimation;
}

void Player::controlsSetUp()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Player::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touch){
		jump();
	}
	return true;
}



void Player::physicsSetUp()
{
	//listen to contacts
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(Player::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//physics body
	auto playerPhysicsBody = PhysicsBody::createBox(Size(getBoundingBox().size.width, getBoundingBox().size.height*0.3));

	playerPhysicsBody->setPositionOffset(Point(0, -getBoundingBox().size.height*0.3));
	playerPhysicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	playerPhysicsBody->setRotationEnable(false);
	setPhysicsBody(playerPhysicsBody);

}

void Player::onContactWall(Node* node1, Node* node2){
	if (node1->getTag() == PLAYER_TAG && node2->getTag() == WALL_TAG
		|| node2->getTag() == PLAYER_TAG && node1->getTag() == WALL_TAG){

		Player * player = nullptr;
		if (node1->getTag() == PLAYER_TAG){
			player = dynamic_cast<Player*>(node1);
		}
		else{
			player = dynamic_cast<Player*>(node2);
		}
		player->getPhysicsBody()->setVelocity(Point(-400, 800));
	}

}

bool Player::onContactTerrain(Node* node1, Node* node2){
	if (node1->getTag() == PLAYER_TAG && node2->getTag() == GROUND_TAG
		|| node2->getTag() == PLAYER_TAG && node1->getTag() == GROUND_TAG){

		Player * player = nullptr;
		if (node1->getTag() == PLAYER_TAG){
			player = dynamic_cast<Player*>(node1);
		}
		else{
			player = dynamic_cast<Player*>(node2);
		}
		if (player->_dead){
			return false;
		}
		if (player->_winner){
			player->_grounded = true;
			player->getPhysicsBody()->setGravityEnable(false);
			player->getPhysicsBody()->setVelocity(Point(0, 0));
			return true;
		}
		player->_grounded = true;
		player->getPhysicsBody()->setGravityEnable(false);
		player->setCurrentAnimation(RUN);
		player->getPhysicsBody()->setVelocity(Point(0, 0));
	}
	return true;
}

void Player::onContactWinningArea(Node* node1, Node* node2){
	if (node1->getTag() == PLAYER_TAG && node2->getTag() == WINNING_AREA
		|| node2->getTag() == PLAYER_TAG && node1->getTag() == WINNING_AREA){
		Player* player = nullptr;
		if (node1->getTag() == PLAYER_TAG){
			player = dynamic_cast<Player*>(node1);
		}
		else{
			player = dynamic_cast<Player*>(node2);
		}
		player->_winner=true;
	}
}

bool Player::onContactEnemy(Node* node1, Node* node2){
	if (node1->getTag() == PLAYER_TAG && node2->getTag() == ENEMY_TAG
		|| node2->getTag() == PLAYER_TAG && node1->getTag() == ENEMY_TAG){

		Player * player = nullptr;
		Enemy* enemy = nullptr;
		if (node1->getTag() == PLAYER_TAG){
			player = dynamic_cast<Player*>(node1);
			enemy = dynamic_cast<Enemy*>(node2);
		}
		else{
			player = dynamic_cast<Player*>(node2);
			enemy = dynamic_cast<Enemy*>(node1);
		}

		if (!player->_grounded && enemy->getCurrentAnimation() != Enemy::Animations::DEAD){
			//kill enemy
			enemy->setCurrentAnimation(Enemy::Animations::DEAD);
			player->getPhysicsBody()->setVelocity(Point(0, 500));
			enemy->getPhysicsBody()->setVelocity(Point(0, 400));
			enemy->setGrouned(false);
			enemy->getPhysicsBody()->setGravityEnable(true);
		}
		else if (!player->_grounded && enemy->getCurrentAnimation() == Enemy::Animations::DEAD){
			//no colisiones con el eenemigo, ya esta muerto.
			return false;
		}
		else if (enemy->getCurrentAnimation() != Enemy::Animations::DEAD){
			//kill player
			player->_dead = true;
			player->getPhysicsBody()->setVelocity(Point(0, 400));
			player->getPhysicsBody()->setGravityEnable(true);
			player->_grounded = false;
			//no colisiones con el enemigo, ya esta muerto el jugador.
			return false;
		}
	}
	return true;
}

bool Player::onContactBegin(PhysicsContact& contact){
	auto node1 = contact.getShapeA()->getBody()->getNode();
	auto node2 = contact.getShapeB()->getBody()->getNode();
	onContactWinningArea(node1, node2);
	onContactWall(node1, node2);
	return onContactEnemy(node1, node2) && onContactTerrain(node1, node2);
}

void Player::onContactSeperate(PhysicsContact& contact)
{
	auto node1 = contact.getShapeA()->getBody()->getNode();
	auto node2 = contact.getShapeB()->getBody()->getNode();
	if (node1->getTag() == PLAYER_TAG || node2->getTag() == PLAYER_TAG){
		Node * player = nullptr;
		if (node1->getTag() == PLAYER_TAG){
			player = node1;
		}
		else{
			player = node2;
		}
		player->getPhysicsBody()->setGravityEnable(true);
	}
}

void Player::update(float dt){
	if (!_dead){
		setPositionX(getPositionX() + dt*_speed);
		if (getPositionY() <= 100){
			_dead = true;
		}
	}
	if (_winner){
		stopAllActions();
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("alienGreen_front"));
		unscheduleUpdate();
	}
}

void Player::jump(){
	if (_grounded){
		auto body = getPhysicsBody();
		setCurrentAnimation(JUMP);
		body->setGravityEnable(true);
		body->setVelocity(Point(body->getVelocity().x, 800));
		_grounded = false;
	}

}
