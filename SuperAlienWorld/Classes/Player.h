#pragma once



#include "cocos2d.h"


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
	void initializeVariables();

	bool onContactEnemy(Node* node1, Node* node2);
	bool onContactTerrain(Node* node1, Node* node2);
	void jump();

public:
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onContactSeperate(cocos2d::PhysicsContact& contact);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(bool, _grounded, Grouned);
	CC_SYNTHESIZE(bool, _dead, Dead);
	Animations getCurrentAnimation(){ return _currentAnimation; };
	void setCurrentAnimation(Animations newAnimation);

public:
	virtual bool init() override;
	virtual void update(float dt) override;
	CREATE_FUNC(Player);
};

