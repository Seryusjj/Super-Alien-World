#pragma once

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{

public:
	enum Animations { DEAD, RUN,RUN_BEHAVIOUR };

protected:
	std::string _baseSpriteName;
	virtual void setEnemyType();

private:
	
	bool _behaviourInitialized;
	Animations _currentAnimation;
	cocos2d::Size _visibleSize;
	cocos2d::Action* _runAnimation;
	cocos2d::SpriteFrame* _deadAnimation;

private:
	void initializeVariables();
	void createRunAnimation();
	void createDeadAnimation();
	void createBehaviour();
	void physicsSetUp();

public:
	bool onContactBegin(cocos2d::PhysicsContact& contact);


public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(bool, _grounded, Grouned);
	Animations getCurrentAnimation(){ return _currentAnimation; };
	void setCurrentAnimation(Animations newAnimation);

public:
	virtual bool init() override;
	CREATE_FUNC(Enemy);
};

