#include "Enemy.h"
#include "Tags.h"



USING_NS_CC;


bool Enemy::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setEnemyType();
	initializeVariables();
	createRunAnimation();
	createDeadAnimation();
	setCurrentAnimation(RUN);
	physicsSetUp();
	return true;
}
void Enemy::initializeVariables(){
	setTag(ENEMY_TAG);
	_speed = 180;
	_visibleSize = Director::getInstance()->getVisibleSize();
	_grounded = false;
	_behaviourInitialized = false;
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_baseSpriteName));
}

void Enemy::setEnemyType(){
	_baseSpriteName = "wormPink";
}

void Enemy::createRunAnimation()
{
	Animation* animation = animation = Animation::create();

	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_baseSpriteName));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_baseSpriteName + "_move"));
	animation->setDelayPerUnit(0.20f);
	auto animate = Animate::create(animation);
	_runAnimation = RepeatForever::create(animate);
	_runAnimation->setTag(Enemy::Animations::RUN);
	_runAnimation->retain();
}

void Enemy::createDeadAnimation(){
	_deadAnimation = SpriteFrameCache::getInstance()->getSpriteFrameByName(_baseSpriteName + "_dead");
	_deadAnimation->retain();
}

void Enemy::setCurrentAnimation(Animations newAnimation)
{
	if (_currentAnimation == newAnimation) return;
	switch (newAnimation)
	{
	case Animations::RUN:
		runAction(_runAnimation);
		break;
	case Animations::DEAD:
		stopActionByTag(RUN);
		stopActionByTag(RUN_BEHAVIOUR);
		setSpriteFrame(_deadAnimation);
		break;
	}
	_currentAnimation = newAnimation;
}



void Enemy::physicsSetUp()
{
	//listen to contacts
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Enemy::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//physics body
	auto enemyPhysicsBody = PhysicsBody::createBox(getBoundingBox().size);
	enemyPhysicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	enemyPhysicsBody->setRotationEnable(false);
	setPhysicsBody(enemyPhysicsBody);
}


bool Enemy::onContactBegin(PhysicsContact& contact){
	auto node1 = contact.getShapeA()->getBody()->getNode();
	auto node2 = contact.getShapeB()->getBody()->getNode();
	if (node1->getTag() == ENEMY_TAG && node2->getTag() == GROUND_TAG
		|| node2->getTag() == ENEMY_TAG && node1->getTag() == GROUND_TAG)
	{
		Enemy * enemy = nullptr;
		if (node1->getTag() == ENEMY_TAG)
		{
			enemy = dynamic_cast<Enemy*>(node1);
		}
		else
		{
			enemy = dynamic_cast<Enemy*>(node2);
		}

		enemy->_grounded = true;
		enemy->getPhysicsBody()->setVelocity(Point(0, 0));
		enemy->getPhysicsBody()->setGravityEnable(false);
		if (!enemy->_behaviourInitialized){
			enemy->createBehaviour();
			enemy->_behaviourInitialized = true;
		}
	}
	return true;
}





void Enemy::createBehaviour(){
	auto moveLeft = MoveTo::create(1.5f, Point(getPositionX() - 100, getPositionY()));
	CallFunc *flip1 = CallFunc::create(CC_CALLBACK_0(Enemy::setScaleX, this, getScaleX()*-1));
	auto moveRight = MoveTo::create(1.5f, Point(getPositionX() + 100, getPositionY()));
	CallFunc *flip2 = CallFunc::create(CC_CALLBACK_0(Enemy::setScaleX, this, getScaleX()));
	auto sequence = RepeatForever::create(Sequence::create(moveLeft, flip1, moveRight, flip2, NULL));
	sequence->setTag(RUN_BEHAVIOUR);
	runAction(sequence);
}




