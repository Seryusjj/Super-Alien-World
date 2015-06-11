#pragma once
#define PLAYER_CONTACT_MASK 0xFFFFFFFF
#define PLAYER_TAG 1

#include "cocos2d.h"
#include "Enemy.h"

class Player : public cocos2d::Sprite
{
public:
	enum Animations { JUMP, RUN };

private:
	std::ostringstream _ostr;
	Animations _currentAnimation;

private:
	cocos2d::Size _visibleSize;
	cocos2d::Action* _runAnimation;
	cocos2d::SpriteFrame* _jumpAnimation;

private:
	void createRunAnimation();
	void createJumpAnimation();
	void physicsSetUp();
	void controlsSetUp();

	void onContactEnemy(Node* node1, Node* node2);
	void onContactTerrain(Node* node1, Node* node2);
	void jump();

public:
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onContactSeperate(cocos2d::PhysicsContact& contact);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(bool, _grounded, Grouned);
	Animations getCurrentAnimation(){ return _currentAnimation; };
	void setCurrentAnimation(Animations newAnimation);

public:
	virtual bool init() override;
	virtual void update(float dt) override;
	CREATE_FUNC(Player);
};

